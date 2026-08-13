#include <SPI.h>
#include <SD.h>

// --- PIN TANIMLARI ---
const int X_CLK = 18; // X Ekseni Adım (Step) pini
const int X_DIR = 19; // X Ekseni Yön (Direction) pini

const int Y_CLK = 9;  // Y Ekseni Adım (Step) pini
const int Y_DIR = 8;  // Y Ekseni Yön (Direction) pini

const int Z_CLK = 7;  // Z Ekseni Adım (Step) pini
const int Z_DIR = 6;  // Z Ekseni Yön (Direction) pini

// Switchler (HOME Switch A3 pini = Dijital 17)
const int XS = 4;  // X Limit Switch pini
const int YS = 3;  // Y Limit Switch pini
const int ZS = 2;  // Z Limit Switch pini
const int HS = 17; // HOME / Sıfırlama Switch pini

// Sensörler ve SD Kart
const int LM35_PIN = A0; // LM35 Sıcaklık Sensör pini
const int SD_CS = 5;     // SD Kart Chip Select (CS) pini

// --- SİSTEM DURUM BAYRAKLARI ---
bool isHomed = false;       // Sıfırlama (Home) yapıldı mı kontrolü
bool isControlOK = false;   // Sensör ve güvenlik kontrolü onaylı mı
bool isBusy = false;        // Sistem şu an bir program çalıştırıyor mu
bool isPaused = false;      // Program duraklatıldı mı
bool isStopState = false;   // Program yarım kesilip durduruldu mu

// --- KOORDİNAT VE ZAMANLAMA ---
long currentX = 0, currentY = 0, currentZ = 0;
int minDelayMs = 30;  // Motorların en yüksek çalışma hızı (düşük değer = hızlı)
int maxDelayMs = 60;  // Kalkış ve duruş esnasındaki ivme hızı
int homeDelayMs = 70; // Home arama anındaki güvenli motor hızı

// --- SD KART VE DOSYA YÖNETİMİ ---
File activeFile;
char currentProgramName[13] = "PROG1.PRG"; 
char previousProgramName[13] = "";
int currentLineNumber = 0;

// Seri iletişim okuma tamponu
char rxBuffer[48];
byte rxIndex = 0;

// Park pozisyon değerleri
long parkX = 0;
long parkY = 0;
long parkZ = 0;
bool hasDynamicPark = false;

// -----------------------------------------------------------------------------
// Kart ilk açıldığında çalışan, pinleri çıkış/giriş olarak ayarlayan,
// seri iletişimi ve SD kartı başlatan kurulum fonksiyonudur.
// -----------------------------------------------------------------------------
void setup() {
  pinMode(X_CLK, OUTPUT); digitalWrite(X_CLK, LOW);
  pinMode(X_DIR, OUTPUT); digitalWrite(X_DIR, LOW);

  pinMode(Y_CLK, OUTPUT); digitalWrite(Y_CLK, LOW);
  pinMode(Y_DIR, OUTPUT); digitalWrite(Y_DIR, LOW);

  pinMode(Z_CLK, OUTPUT); digitalWrite(Z_CLK, LOW);
  pinMode(Z_DIR, OUTPUT); digitalWrite(Z_DIR, LOW);

  delay(50);

  pinMode(XS, INPUT_PULLUP);
  pinMode(YS, INPUT_PULLUP);
  pinMode(ZS, INPUT_PULLUP);
  pinMode(HS, INPUT_PULLUP); 

  Serial.begin(9600);
  Serial.println(F("STAT,IDLE,0,0,0"));

  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  delay(50);

  if (!SD.begin(SPI_HALF_SPEED, SD_CS)) {
    Serial.println(F("ERR,SD_INIT_FAIL,0,0,0"));
  } else {
    Serial.println(F("INF,ARDUINO,READY,0,0"));
  }
}

// -----------------------------------------------------------------------------
// Sürekli çalışan ana döngüdür. Seri porttan gelen komutları dinler ve
// çalışır durumda bir program varsa SD karttan satır satır komut okur.
// -----------------------------------------------------------------------------
void loop() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();
    if (inChar == '\n' || inChar == '\r') {
      if (rxIndex > 0) {
        rxBuffer[rxIndex] = '\0';
        processPacket(rxBuffer);
        rxIndex = 0;
      }
    } else {
      if (rxIndex < sizeof(rxBuffer) - 1) {
        rxBuffer[rxIndex++] = inChar;
      }
    }
  }

  if (isBusy && !isPaused) {
    runNextProgramLineFromSD();
  }
}

// -----------------------------------------------------------------------------
// SD kart içerisindeki dosyaları tarar ve sadece uzantısı .PRG olan
// işlenebilir program dosyalarının isimlerini seri porttan ekrana gönderir.
// -----------------------------------------------------------------------------
void sendProgramList() {
  File root = SD.open("/");
  if (!root) {
    Serial.println(F("ERR,SD_OPEN_FAILED,0,0,0"));
    return;
  }

  String lstOutput = "LST";
  bool foundAny = false;

  while (true) {
    File entry = root.openNextFile();
    if (!entry) {
      break;
    }

    if (!entry.isDirectory()) {
      String fileName = entry.name();
      String upperName = fileName;
      upperName.toUpperCase();

      if (upperName.endsWith(".PRG")) {
        lstOutput += ",";
        lstOutput += fileName;
        foundAny = true;
      }
    }
    entry.close();
  }
  root.close();

  if (foundAny) {
    Serial.println(lstOutput);
  } else {
    Serial.println(F("ERR,NO_FILES_FOUND,0,0,0"));
  }
}

// -----------------------------------------------------------------------------
// LM35 sensöründen analog veriyi okur ve bunu derece (°C) cinsinden
// sıcaklık değerine dönüştürerek geriye döndürür.
// -----------------------------------------------------------------------------
float readTemperature() {
  int rawADC = analogRead(LM35_PIN);
  float voltage = (rawADC * 5.0 / 1024.0); 
  return voltage * 100.0; 
}

// -----------------------------------------------------------------------------
// Program bittiğinde veya durdurulduğunda motorları güvenli olan
// park pozisyonu koordinatlarına geri götüren fonksiyondur.
// -----------------------------------------------------------------------------
void executePark() {
  int returnX = parkX - currentX;
  int returnY = parkY - currentY;
  int returnZ = parkZ - currentZ;

  executeMoveRamped(returnX, returnY, returnZ);

  Serial.print(F("INF,PARKED,"));
  Serial.print(currentX); Serial.print(F(","));
  Serial.print(currentY); Serial.print(F(","));
  Serial.println(currentZ); 

  Serial.println(F("INF,READY,0,0,0"));
}

// -----------------------------------------------------------------------------
// Seri porttan gelen komut paketlerini ayrıştırır; Başlat, Durdur,
// Duraklat, Jog (manuel hareket) veya Sıfırlama komutlarını çalıştırır.
// -----------------------------------------------------------------------------
void processPacket(char* packet) {
  int len = strlen(packet);
  while (len > 0 && (packet[len - 1] == '\r' || packet[len - 1] == '\n' || packet[len - 1] == ' ')) {
    packet[--len] = '\0';
  }

  if (strcmp(packet, "GETFILES") == 0) {
    sendProgramList();
    return;
  }

  char p1[10] = {0}, p2[10] = {0}, p3[13] = {0};
  int count = sscanf(packet, "%9[^,],%9[^,],%12[^,]", p1, p2, p3);
  if (count < 1) return;

  if (strcmp(p1, "CMD") == 0) {
    if (strcmp(p2, "HOME") == 0) {
      executeHome();
    } 
    else if (strcmp(p2, "KONTROL") == 0) {
      executeCheckSensors();
    }
    else if (strcmp(p2, "PAUSE") == 0) {
      if (isBusy) {
        isPaused = true;
        Serial.println(F("INF,DURAKLATILDI,0,0,0"));
      }
    }
    else if (strcmp(p2, "RESUME") == 0) {
      if (isBusy && isPaused) {
        isPaused = false;
        Serial.println(F("INF,DEVAM,0,0,0"));
      }
    }
    else if (strcmp(p2, "START") == 0) {
      if (isBusy) {
        Serial.println(F("CALISIRKEN START BUTONUNA BASTINIZ"));
        return;
      }

      if (strlen(p3) == 0) {
        Serial.println(F("ERR,PROGRAM_NAME_MISSING,0,0"));
        return;
      }
      strncpy(currentProgramName, p3, sizeof(currentProgramName) - 1);
      currentProgramName[sizeof(currentProgramName) - 1] = '\0';

      if (strlen(previousProgramName) > 0 && strcmp(currentProgramName, previousProgramName) != 0) {
        isHomed = false;
        Serial.println(F("ERR,HOME,PROGRAM_CHANGED_REQUIRES_HOME,0,0"));
        previousProgramName[0] = '\0';
        return;
      }

      if (!isControlOK) {
        Serial.println(F("ERR,SENS,NOT_CHECKED,0,0"));
        return;
      }
      if (!isHomed) {
        Serial.println(F("ERR,HOME,NOT_HOMED,0,0"));
        return;
      }

      if (!SD.exists(currentProgramName)) {
        Serial.print(F("ERR,SD_NO_FILE,"));
        Serial.println(currentProgramName);
        return;
      }

      if (isStopState && (currentX != 0 || currentY != 0 || currentZ != 0)) {
        executePark();
        isStopState = false;
      }

      activeFile = SD.open(currentProgramName, FILE_READ);
      if (!activeFile) {
        Serial.println(F("ERR,SD_OPEN_FAIL,0,0"));
        return;
      }

      isBusy = true;
      isPaused = false;
      isStopState = false;
      currentLineNumber = 0;
      strncpy(previousProgramName, currentProgramName, sizeof(previousProgramName) - 1);
      Serial.println(F("STAT,BUSY,0,0,1"));
    }
    else if (strcmp(p2, "STOP") == 0) {
      isBusy = false;
      isPaused = false;
      isStopState = true;
      
      if (activeFile) activeFile.close();
      tumCLKPinleriniSifirla();
      
      Serial.println(F("INF,PROGRAM_DURDURULDU,0,0,0"));
      
      Serial.print(F("STAT,IDLE,"));
      Serial.print(currentX); Serial.print(F(","));
      Serial.print(currentY); Serial.print(F(","));
      Serial.println(currentZ);
    }
  }
  else if (strcmp(p1, "JOG") == 0) {
    char pX[8] = {0}, pY[8] = {0}, pZ[8] = {0};
    sscanf(packet, "%*[^,],%7[^,],%7[^,],%7s", pX, pY, pZ);
    int dx = atoi(pX); int dy = atoi(pY); int dz = atoi(pZ);
    isHomed = false; 
    executeMoveRamped(dx, dy, dz);
    Serial.print(F("STAT,IDLE,"));
    Serial.print(currentX); Serial.print(F(","));
    Serial.print(currentY); Serial.print(F(","));
    Serial.println(currentZ);
  }
}

// -----------------------------------------------------------------------------
// Limit switch'lerin ve sıcaklık sensörünün çalışma aralığında olup
// olmadığını kontrol eder, sistemin çalışmaya uygunluğunu onaylar.
// -----------------------------------------------------------------------------
void executeCheckSensors() {
  bool xOk = (digitalRead(XS) == HIGH);
  bool yOk = (digitalRead(YS) == HIGH);
  bool zOk = (digitalRead(ZS) == HIGH);
  bool hOk = (digitalRead(HS) == HIGH);
  float currentTemp = readTemperature();
  bool tempOk = (currentTemp >= 20.0 && currentTemp <= 30.0);

  if (xOk && yOk && zOk && hOk && tempOk) {
    isControlOK = true;
    Serial.println(F("INF,CHECK_OK,0,0,0"));
  } else {
    isControlOK = false;
    if (!xOk) Serial.println(F("ERR,SENS,X_LIMIT_ACTIVE,0,0"));
    else if (!yOk) Serial.println(F("ERR,SENS,Y_LIMIT_ACTIVE,0,0"));
    else if (!zOk) Serial.println(F("ERR,SENS,Z_LIMIT_ACTIVE,0,0"));
    else if (!hOk) Serial.println(F("ERR,SENS,HOME_SW_ACTIVE,0,0"));
    else if (!tempOk) {
      Serial.print(F("ERR,SENS,TEMP_OUT_OF_RANGE,"));
      Serial.println(currentTemp);
    }
  }
}

// -----------------------------------------------------------------------------
// Tüm eksenleri eksi (-) yönde hareket ettirerek Home switch'ine kadar
// sürer, switch basıldığı an durup makine koordinatlarını sıfırlar.
// -----------------------------------------------------------------------------
void executeHome() {
  previousProgramName[0] = '\0';
  if (!isControlOK) {
    Serial.println(F("ERR,SENS,RUN_KONTROL_FIRST,0,0"));
    return;
  }
  
  Serial.println(F("STAT,HOMING,0,0,0"));
  
  digitalWrite(X_DIR, LOW);
  digitalWrite(Y_DIR, LOW);
  digitalWrite(Z_DIR, LOW);
  delay(10);

  unsigned long startTime = millis();
  bool success = false;

  while (millis() - startTime < 35000) {
    if (digitalRead(HS) == LOW) { 
      success = true; 
      break; 
    }
    
    digitalWrite(X_CLK, HIGH); 
    digitalWrite(Y_CLK, HIGH); 
    digitalWrite(Z_CLK, HIGH); 
    
    delayMicroseconds(500);

    digitalWrite(X_CLK, LOW); 
    digitalWrite(Y_CLK, LOW); 
    digitalWrite(Z_CLK, LOW); 
    
    delay(homeDelayMs);
  }

  if (success) {
    currentX = 0; 
    currentY = 0; 
    currentZ = 0;
    isHomed = true;
    isStopState = false;
    Serial.println(F("INF,HOMED,0,0,0"));
    parkX = 0;
    parkY = 0;
    parkZ = 0;
  } else {
    isHomed = false;
    Serial.println(F("ERR,HOME_TIMEOUT,0,0,0"));
  }
}

// -----------------------------------------------------------------------------
// Z eksenini (yukarı/aşağı) diğer eksenlerden bağımsız olarak güvenli
// bir şekilde tek başına belirtilen adım kadar hareket ettirir.
// -----------------------------------------------------------------------------
void executeZSafeMove(int dz) {
  if (dz == 0) return;
  
  digitalWrite(Z_DIR, (dz >= 0) ? HIGH : LOW);
  delayMicroseconds(100);

  int steps = abs(dz);
  for (int i = 0; i < steps; i++) {
    digitalWrite(Z_CLK, HIGH);
    delayMicroseconds(500);
    digitalWrite(Z_CLK, LOW);
    delay(50); 
    currentZ += (dz > 0) ? 1 : -1;
  }
}

// -----------------------------------------------------------------------------
// X, Y ve Z eksenlerini yumuşak kalkış ve duruş (rampa) yaparak
// senkronize bir şekilde verilen hedef adımlara doğru sürer.
// -----------------------------------------------------------------------------
void executeMoveRamped(int dx, int dy, int dz) {
  digitalWrite(X_DIR, (dx >= 0) ? HIGH : LOW);
  digitalWrite(Y_DIR, (dy >= 0) ? HIGH : LOW);
  digitalWrite(Z_DIR, (dz >= 0) ? HIGH : LOW);
  delay(5);

  long absX = abs((long)dx); 
  long absY = abs((long)dy); 
  long absZ = abs((long)dz);
  long maxSteps = max(absX, max(absY, absZ));
  if (maxSteps == 0) return;

  long countX = 0; 
  long countY = 0; 
  long countZ = 0;
  long accelSteps = maxSteps / 4; 

  for (long i = 0; i < maxSteps; i++) {
    int currentDelay = minDelayMs;
    if (maxSteps >= 8 && accelSteps > 0) {
      if (i < accelSteps) currentDelay = maxDelayMs - ((maxDelayMs - minDelayMs) * i / accelSteps);
      else if (i >= maxSteps - accelSteps) currentDelay = maxDelayMs - ((maxDelayMs - minDelayMs) * (maxSteps - 1 - i) / accelSteps);
    }

    bool stepX = false; bool stepY = false; bool stepZ = false;
    
    countX += absX;
    if (countX >= maxSteps) {
      stepX = true;
      countX -= maxSteps;
      currentX += (dx > 0) ? 1 : -1;
    }

    countY += absY;
    if (countY >= maxSteps) {
      stepY = true;
      countY -= maxSteps;
      currentY += (dy > 0) ? 1 : -1;
    }

    countZ += absZ;
    if (countZ >= maxSteps) {
      stepZ = true;
      countZ -= maxSteps;
      currentZ += (dz > 0) ? 1 : -1;
    }

    if (stepX) digitalWrite(X_CLK, HIGH);
    if (stepY) digitalWrite(Y_CLK, HIGH);
    if (stepZ) digitalWrite(Z_CLK, HIGH);
    delayMicroseconds(500);
    digitalWrite(X_CLK, LOW); digitalWrite(Y_CLK, LOW); digitalWrite(Z_CLK, LOW);
    delay(currentDelay); 
  }
}

// -----------------------------------------------------------------------------
// SD karttaki aktif dosyadan sıradaki komut satırını okur, modunu
// (Çalıştır/Atla/Park) belirler, ortam sıcaklığını denetleyerek motorları sürer.
// -----------------------------------------------------------------------------
void runNextProgramLineFromSD() {
  long pX = 0;
  long pY = 0;
  long pZ = 0;
  float currentTemp = readTemperature();
  if (currentTemp < 20.0 || currentTemp > 30.0) {
    isBusy = false;
    isPaused = false;
    if (activeFile) activeFile.close();
    tumCLKPinleriniSifirla();
    Serial.print(F("ERR,TEMP_FAULT,"));
    Serial.println(currentTemp);
    return;
  }

  if (activeFile && activeFile.available()) {
    String line = activeFile.readStringUntil('\n');
    line.trim();
    
    if (line.length() > 0) {
      currentLineNumber++;
      int dx = 0, dy = 0, dz = 0;
      char mode = 'C';
      
      int parsed = sscanf(line.c_str(), "%d,%d,%d,%c", &dx, &dy, &dz, &mode);

      if (currentLineNumber == 1) {
        pX = dx;
        pY = dy;
        pZ = dz;
        dx = dx - parkX;
        dy = dy - parkY;
        dz = dz - parkZ;
      }
      
      if (parsed >= 4) {
        if (mode == 'B') {
          Serial.print(F("INF,BYPASSED_LINE,"));
          Serial.println(currentLineNumber);
        } 
        else if (mode == 'C') {
          executeMoveRamped(dx, dy, dz);
          Serial.print(F("STAT,BUSY,"));
          Serial.print(currentX); Serial.print(F(","));
          Serial.print(currentY); Serial.print(F(","));
          Serial.print(currentZ); Serial.print(F(","));
          Serial.println(currentLineNumber);
        } 
        else if (mode == 'P') {
          executePark();
        }
      }

      if (currentLineNumber == 1) {
        parkX = pX;
        parkY = pY;
        parkZ = 0;
        hasDynamicPark = true;
      }
    }
    delay(200);
  } else {
    isBusy = false;
    isPaused = false;
    isStopState = false;
    if (activeFile) activeFile.close();
    Serial.println(F("INF,DONE,0,0,0"));
  }
}

// -----------------------------------------------------------------------------
// Tüm motorların adım (clock) pinlerini sıfıra (LOW) çekerek
// motorların durmasını ve sinyallerin temizlenmesini sağlar.
// -----------------------------------------------------------------------------
void tumCLKPinleriniSifirla() {
  digitalWrite(X_CLK, LOW);
  digitalWrite(Y_CLK, LOW);
  digitalWrite(Z_CLK, LOW);
}
