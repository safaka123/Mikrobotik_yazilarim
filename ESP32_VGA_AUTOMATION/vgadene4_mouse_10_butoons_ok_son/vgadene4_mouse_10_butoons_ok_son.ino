#include "fabgl.h"

// Sürücü Tanımlamaları
fabgl::VGAController DisplayController;
fabgl::PS2Controller PS2Controller;

// HC-05 Bluetooth UART2 Pinleri
#define HC05_RX_PIN 16
#define HC05_TX_PIN 17

// Menü Koordinatları
const int menuX = 60, menuY = 70, menuW = 280, menuH = 150;
bool menuAcikMi = false;

// Mouse Koordinatları
volatile int mouseX = 200; 
volatile int mouseY = 150; 

const float SCALE_X = 0.5; // İsteğinize göre yavaşlatılmış hassas katsayı
const float SCALE_Y = 0.5; 

const int MIN_X = 0;
const int MAX_X = 390; 
const int MIN_Y = 0;
const int MAX_Y = 285; 

// STATUS LOG HAFIZASI (100 SATIR DİNAMİK/DAİRESEL TAMPON)
const int MAX_LOGS = 100;
String statusLogs[MAX_LOGS];
int logHead = 0;      
int totalLogs = 0;    
int scrollOffset = 0; 

// MAKİNE DURUMU (0: IDLE/Yeşil, 1: BUSY/Sarı, 2: ERR/Kırmızı)
int machineStatus = 0; 

// BAĞIMSIZ DURUM BAYRAKLARI
bool arduinoIsReady = false;   // Arduino açılışta READY verdi mi?
bool isProgramRunning = false; // Sadece aktif bir G-Code/Program çalışırken true

// PROGRAM LİSTESİ VE SEÇİM DEĞİŞKENLERİ
String programList[10]; 
int totalProgramCount = 0;
int hoveredProgIndex = 0;   
String selectedProgram = ""; 

// EKRAN ODAKLANMA (FOCUS) SİSTEMİ
int focusedElement = -1; 
const int TOTAL_FOCUS_ELEMENTS = 16; 

// DİNAMİK EKSEN SEÇİMİ HAFIZASI (0: X, 1: Y, 2: Z)
int activeAxis = 0; // Varsayılan olarak X ekseni seçili gelir

// =========================================================================
// FABGL ARAYÜZ VE UYGULAMA SINIFI
// =========================================================================
class MakinePaneliApp : public fabgl::uiApp {
public:
  void addLog(String newLog) {
    statusLogs[logHead] = newLog;
    logHead = (logHead + 1) % MAX_LOGS;
    if (totalLogs < MAX_LOGS) {
      totalLogs++;
    }
    scrollOffset = 0; 
  }

  String getLogAt(int indexFromLast) {
    if (indexFromLast < 0 || indexFromLast >= totalLogs) return "";
    int idx = (logHead - 1 - indexFromLast + MAX_LOGS) % MAX_LOGS;
    return statusLogs[idx];
  }

  void parseProgramList(String lstLine) {
    totalProgramCount = 0;
    int firstComma = lstLine.indexOf(',');
    if (firstComma == -1) return;

    String data = lstLine.substring(firstComma + 1);
    while (data.length() > 0 && totalProgramCount < 10) {
      int commaIndex = data.indexOf(',');
      if (commaIndex != -1) {
        programList[totalProgramCount++] = data.substring(0, commaIndex);
        data = data.substring(commaIndex + 1);
      } else {
        programList[totalProgramCount++] = data;
        break;
      }
    }
  }

  // MOUSE L-BUTTON TIKLAMA MANTIĞI
  void processMouseClick(int x, int y) {
    // A) SADECE KUTULAR -> Focus Alır VE Aktif Ekseni Günceller
    if (x >= 25 && x <= 65 && y >= 58 && y <= 80)        { focusedElement = 0; activeAxis = 0; } // X Eksen
    else if (x >= 80 && x <= 120 && y >= 58 && y <= 80)  { focusedElement = 1; activeAxis = 1; } // Y Eksen
    else if (x >= 135 && x <= 175 && y >= 58 && y <= 80) { focusedElement = 2; activeAxis = 2; } // Z Eksen
    else if (x >= 20 && x <= 150 && y >= 108 && y <= 245) {                                       // Program Listesi Kutusu
      focusedElement = 3;
      if (totalProgramCount > 0) {
        int clickedIdx = (y - 113) / 15;
        if (clickedIdx >= 0 && clickedIdx < totalProgramCount) {
          hoveredProgIndex = clickedIdx;
          selectedProgram = programList[hoveredProgIndex];
        }
      }
    }
    else if (x >= 230 && x <= 385 && y >= 180 && y <= 250) { focusedElement = 13; } // Status Log Kutusu

    // B) BUTONLAR -> Doğrudan Aktif Eksen Üzerinden JOG veya İşlem Tetikler!
    else if (x >= 185 && x <= 215 && y >= 50 && y <= 65)   { executeButtonAction(14); } // UP (Yukarı)
    else if (x >= 185 && x <= 215 && y >= 68 && y <= 83)   { executeButtonAction(15); } // DOWN (Aşağı)
    else if (x >= 160 && x <= 220 && y >= 108 && y <= 130) { executeButtonAction(4); }  // SD OKU
    else if (x >= 250 && x <= 310 && y >= 35 && y <= 55)   { executeButtonAction(5); }  // HOME
    else if (x >= 325 && x <= 385 && y >= 35 && y <= 55)   { executeButtonAction(6); }  // START
    else if (x >= 250 && x <= 310 && y >= 65 && y <= 85)   { executeButtonAction(7); }  // PAUSE
    else if (x >= 325 && x <= 385 && y >= 65 && y <= 85)   { executeButtonAction(8); }  // STOP
    else if (x >= 250 && x <= 310 && y >= 95 && y <= 115)  { executeButtonAction(9); }  // RESUME
    else if (x >= 325 && x <= 385 && y >= 95 && y <= 115)  { executeButtonAction(10); } // KONTROL
    else if (x >= 60 && x <= 160 && y >= 260 && y <= 282)  { executeButtonAction(11); } // EDIT (F2)
    else if (x >= 220 && x <= 320 && y >= 260 && y <= 282) { executeButtonAction(12); } // YEDEK (F3)

    rootWindow()->repaint();
  }

  void init() override {
    rootWindow()->frameStyle().backgroundColor = RGB888(75, 107, 148);

    rootWindow()->onPaint = [&]() {
      auto cv = canvas();
      cv->selectFont(&fabgl::FONT_5x8);

      // 1. ÜST BAŞLIK BARI
      cv->setPenColor(RGB888(0, 0, 0));
      cv->setBrushColor(RGB888(255, 255, 255));
      cv->fillRectangle(15, 5, 385, 25);
      cv->drawRectangle(15, 5, 385, 25);
      cv->drawText(65, 12, "STEP MOTORLU 3 EKSEN MAKINE KONTROLU");

      // 2. MANUAL KONTROL
      cv->setPenColor(RGB888(255, 255, 255));
      cv->drawText(25, 35, "MANUAL KONTROL");

      // 3. EKSEN KUTULARI
      cv->drawText(25, 48, "X EKSEN");
      cv->setBrushColor(focusedElement == 0 ? RGB888(255, 255, 150) : RGB888(255, 255, 255));
      cv->fillRectangle(25, 58, 65, 80);
      cv->setPenColor(focusedElement == 0 ? RGB888(255, 0, 0) : RGB888(0, 0, 0));
      cv->drawRectangle(25, 58, 65, 80);

      cv->setPenColor(RGB888(255, 255, 255));
      cv->drawText(80, 48, "Y EKSEN");
      cv->setBrushColor(focusedElement == 1 ? RGB888(255, 255, 150) : RGB888(255, 255, 255));
      cv->fillRectangle(80, 58, 120, 80);
      cv->setPenColor(focusedElement == 1 ? RGB888(255, 0, 0) : RGB888(0, 0, 0));
      cv->drawRectangle(80, 58, 120, 80);

      cv->setPenColor(RGB888(255, 255, 255));
      cv->drawText(135, 48, "Z EKSEN");
      cv->setBrushColor(focusedElement == 2 ? RGB888(255, 255, 150) : RGB888(255, 255, 255));
      cv->fillRectangle(135, 58, 175, 80);
      cv->setPenColor(focusedElement == 2 ? RGB888(255, 0, 0) : RGB888(0, 0, 0));
      cv->drawRectangle(135, 58, 175, 80);

      // AKTİF EKSEN UP/DOWN BUTONLARI (Focus: 14 ve 15)
      drawGraphicButton(185, 50, 30, 15, "  ^", focusedElement == 14);
      drawGraphicButton(185, 68, 30, 15, "  v", focusedElement == 15);

      // 5. PROGRAM LİSTESİ PENCERESİ (Focus: 3)
      cv->setPenColor(RGB888(255, 255, 255));
      cv->drawText(20, 95, "PROGRAM LISTESI");

      cv->setBrushColor(focusedElement == 3 ? RGB888(240, 240, 255) : RGB888(255, 255, 255));
      cv->fillRectangle(20, 108, 150, 245);
      cv->setPenColor(focusedElement == 3 ? RGB888(255, 0, 0) : RGB888(0, 0, 0));
      cv->drawRectangle(20, 108, 150, 245);

      for (int i = 0; i < totalProgramCount; i++) {
        int itemY = 115 + (i * 15);
        if (focusedElement == 3 && hoveredProgIndex == i) {
          cv->setBrushColor(RGB888(0, 120, 215));
          cv->fillRectangle(22, itemY - 2, 148, itemY + 10);
          cv->setPenColor(RGB888(255, 255, 255));
        } else {
          cv->setPenColor(RGB888(0, 0, 0));
        }
        String lineStr = String(i + 1) + ". " + programList[i];
        cv->drawText(25, itemY, lineStr.c_str());
      }

      // SD CARD OKU Butonu (Focus: 4)
      drawGraphicButton(160, 108, 60, 22, "SD OKU", focusedElement == 4);

      // SEÇİLEN PROGRAM KUTUSU
      cv->setPenColor(RGB888(255, 255, 255));
      cv->drawText(160, 138, "SECILEN:");
      cv->setBrushColor(RGB888(230, 230, 230));
      cv->fillRectangle(160, 148, 225, 170);
      cv->setPenColor(RGB888(0, 0, 0));
      cv->drawRectangle(160, 148, 225, 170);
      
      if (selectedProgram.length() > 0) {
        cv->drawText(163, 156, selectedProgram.c_str());
      } else {
        cv->setPenColor(RGB888(150, 0, 0));
        cv->drawText(163, 156, "[SECILMEDI]");
      }

      // 6. SAĞ KONTROL BUTONLARI
      drawGraphicButton(250, 35, 60, 20, "HOME",     focusedElement == 5);
      drawGraphicButton(325, 35, 60, 20, "START",    focusedElement == 6);
      drawGraphicButton(250, 65, 60, 20, "DURAKLAT", focusedElement == 7);
      drawGraphicButton(325, 65, 60, 20, "DURDUR",   focusedElement == 8);
      drawGraphicButton(250, 95, 60, 20, "DEVAM",    focusedElement == 9);
      drawGraphicButton(325, 95, 60, 20, "KONTROL",  focusedElement == 10);

      // 7. DURUM İKAZ YUVARLAĞI (LED Circle)
      if (machineStatus == 0)      cv->setBrushColor(RGB888(0, 220, 0));   // Yeşil (IDLE)
      else if (machineStatus == 1) cv->setBrushColor(RGB888(240, 200, 0)); // Sarı (BUSY / HOMING)
      else                         cv->setBrushColor(RGB888(220, 0, 0));   // Kırmızı (ERR)
      
      cv->setPenColor(RGB888(0, 0, 0));
      cv->fillEllipse(275, 143, 27, 27);
      cv->drawEllipse(275, 143, 27, 27);

      // 8. STATUS LOG EKRANI
      cv->setBrushColor(focusedElement == 13 ? RGB888(245, 245, 200) : RGB888(255, 255, 255));
      cv->fillRectangle(230, 180, 385, 250);
      cv->setPenColor(focusedElement == 13 ? RGB888(255, 0, 0) : RGB888(0, 0, 0));
      cv->drawRectangle(230, 180, 385, 250);
      
      cv->setPenColor(RGB888(0, 0, 0));
      cv->drawText(235, 183, "STATUS EKRANI:");

      for (int i = 0; i < 4; i++) {
        int fetchIdx = scrollOffset + (3 - i);
        String logLine = getLogAt(fetchIdx);

        if (logLine.length() > 0) {
          if (logLine.startsWith("ERR")) cv->setPenColor(RGB888(200, 0, 0));
          else if (logLine.startsWith("INF")) cv->setPenColor(RGB888(0, 100, 0));
          else cv->setPenColor(RGB888(0, 0, 0));

          cv->drawText(235, 195 + (i * 12), logLine.c_str());
        }
      }

      if (totalLogs > 4) {
        cv->setPenColor(RGB888(180, 180, 180));
        cv->drawRectangle(380, 195, 383, 245);
        int thumbH = max(6, (4 * 50) / totalLogs);
        int maxScroll = totalLogs - 4;
        int thumbY = 245 - thumbH - ((scrollOffset * (50 - thumbH)) / maxScroll);
        cv->setBrushColor(RGB888(100, 100, 100));
        cv->fillRectangle(380, thumbY, 383, thumbY + thumbH);
      }

      // 9. ALT KISAYOL TUŞLARI
      drawGraphicButton(60, 260, 100, 22, "EDIT (F2)", focusedElement == 11);
      drawGraphicButton(220, 260, 100, 22, "YEDEK (F3)", focusedElement == 12);
    };

    // KLAVYE KONTROL DİNLEYİCİSİ
    rootWindow()->onKeyDown = [&](fabgl::uiKeyEventInfo const & key) {
      if (key.VK == fabgl::VirtualKey::VK_TAB) {
        if (key.SHIFT) {
          if (focusedElement <= 0) focusedElement = TOTAL_FOCUS_ELEMENTS - 1;
          else focusedElement--;
        } else {
          focusedElement = (focusedElement + 1) % TOTAL_FOCUS_ELEMENTS;
        }

        // TAB ile X, Y, Z kutularına gelindiğinde aktif ekseni güncelle
        if (focusedElement >= 0 && focusedElement <= 2) {
          activeAxis = focusedElement;
        }

        rootWindow()->repaint();
        return;
      }

      if (key.VK == fabgl::VirtualKey::VK_m && !menuAcikMi) { menuAc(); return; }
      else if (key.VK == fabgl::VirtualKey::VK_ESCAPE && menuAcikMi) { menuKapat(); return; }

      if (focusedElement == -1 || menuAcikMi) return; 

      if (focusedElement == 13 && totalLogs > 4) {
        if (key.VK == fabgl::VirtualKey::VK_UP) {
          if (scrollOffset < totalLogs - 4) {
            scrollOffset++;
            rootWindow()->repaint();
          }
          return;
        }
        if (key.VK == fabgl::VirtualKey::VK_DOWN) {
          if (scrollOffset > 0) {
            scrollOffset--;
            rootWindow()->repaint();
          }
          return;
        }
      }

      // X, Y, Z Kutularındayken VEYA UP/DOWN Butonlarındayken Ok Tuşlarıyla JOG
      if ((focusedElement >= 0 && focusedElement <= 2) || focusedElement == 14 || focusedElement == 15) {
        if (key.VK == fabgl::VirtualKey::VK_UP)   { triggerJog(activeAxis, 1); return; } 
        if (key.VK == fabgl::VirtualKey::VK_DOWN) { triggerJog(activeAxis, -1); return; }
      }

      if (focusedElement == 3 && totalProgramCount > 0) {
        if (key.VK == fabgl::VirtualKey::VK_UP) {
          if (hoveredProgIndex > 0) hoveredProgIndex--;
          rootWindow()->repaint();
          return;
        }
        else if (key.VK == fabgl::VirtualKey::VK_DOWN) {
          if (hoveredProgIndex < totalProgramCount - 1) hoveredProgIndex++;
          rootWindow()->repaint();
          return;
        }
        else if (key.VK == fabgl::VirtualKey::VK_RETURN) {
          selectedProgram = programList[hoveredProgIndex];
          rootWindow()->repaint();
          return;
        }
      }

      if (key.VK == fabgl::VirtualKey::VK_RETURN) {
        executeButtonAction(focusedElement);
        return;
      }
    };
  }

  void triggerJog(int axis, int dir) {
    int valX = (axis == 0) ? dir : 0;
    int valY = (axis == 1) ? dir : 0;
    int valZ = (axis == 2) ? dir : 0;
    Serial.printf("JOG,%d,%d,%d,0\r", valX, valY, valZ); 
  }

  void executeButtonAction(int elementId) {
    switch(elementId) {
      case 4: 
        Serial.print("GETFILES\r"); 
        break;

      case 5: // HOME BUTONU
        isProgramRunning = false;
        if (machineStatus == 2) machineStatus = 0;
        Serial.print("CMD,HOME,0,0,0\r"); 
        break;

      case 6: // START BUTON KONTROLÜ
        if (isProgramRunning) { 
          addLog("ERR: PROGRAM CALISIYOR!");
          machineStatus = 2;
          rootWindow()->repaint();
        }
        else if (machineStatus == 1) { 
          addLog("ERR: MAKINE MESGUL!");
          machineStatus = 2;
          rootWindow()->repaint();
        }
        else if (selectedProgram.length() == 0) { 
          addLog("ERR: PROG SECILMEDI!");
          machineStatus = 2;
          rootWindow()->repaint();
        } 
        else if (!arduinoIsReady) { 
          addLog("ERR: ARDUINO HAZIR DEGIL!");
          machineStatus = 2;
          rootWindow()->repaint();
        } 
        else {
          isProgramRunning = true; 
          machineStatus = 1; 
          
          String cmd = "CMD,START," + selectedProgram + ",0,0\r";
          Serial.print(cmd);
          rootWindow()->repaint();
        }
        break;

      case 7:  Serial.print("CMD,PAUSE,0,0,0\r"); break;

      case 8:  // DURDUR / RESET
        isProgramRunning = false; 
        machineStatus = 0; 
        Serial.print("CMD,STOP,0,0,0\r");  
        rootWindow()->repaint();
        break;

      case 9:  Serial.print("CMD,RESUME,0,0,0\r"); break;

      case 10: // KONTROL BUTONU
        isProgramRunning = false; 
        if (machineStatus == 2) machineStatus = 0; 
        Serial.print("CMD,KONTROL,0,0,0\r"); 
        break;
      
      case 11: // EDIT (F2) BUTONU
        addLog("INF: EDIT MODUNA GECILIYOR");
        rootWindow()->repaint();
        break;

      case 12: // YEDEK (F3) BUTONU
        addLog("INF: YEDEK MODU");
        rootWindow()->repaint();
        break;

      case 14: // YUKARI (UP ^) BUTONU -> Aktif eksende +1 JOG
        triggerJog(activeAxis, 1); 
        break;

      case 15: // AŞAĞI (DOWN v) BUTONU -> Aktif eksende -1 JOG
        triggerJog(activeAxis, -1); 
        break;
    }
  }

  void drawGraphicButton(int x, int y, int w, int h, const char* label, bool isFocused) {
    auto cv = canvas();
    cv->setBrushColor(isFocused ? RGB888(255, 255, 150) : RGB888(210, 210, 210));
    cv->fillRectangle(x, y, x + w, y + h);
    cv->setPenColor(isFocused ? RGB888(255, 0, 0) : RGB888(255, 255, 255)); 
    cv->drawLine(x, y, x + w, y);
    cv->drawLine(x, y, x, y + h);
    cv->setPenColor(isFocused ? RGB888(200, 0, 0) : RGB888(100, 100, 100)); 
    cv->drawLine(x, y + h, x + w, y + h);
    cv->drawLine(x + w, y, x + w, y + h);
    cv->setPenColor(RGB888(0, 0, 0));
    cv->drawText(x + 5, y + (h / 4), label);
  }

  void menuAc() {
    if (menuAcikMi) return;
    auto cv = canvas();
    cv->copyRect(menuX, menuY, menuW, menuH, 110, 0);
    cv->setPenColor(RGB888(0, 0, 0)); 
    cv->setBrushColor(RGB888(255, 255, 255)); 
    cv->fillRectangle(menuX, menuY, menuX + menuW, menuY + menuH);
    cv->setBrushColor(RGB888(0, 0, 255));
    cv->fillRectangle(menuX + 2, menuY + 2, menuX + menuW - 2, menuY + 20);
    cv->setPenColor(RGB888(255, 255, 255)); 
    cv->drawText(menuX + 10, menuY + 6, "AYARLAR VE PARAMETRELER");
    cv->setPenColor(RGB888(0, 0, 0)); 
    cv->drawText(menuX + 15, menuY + 35, "1- Motor Hiz Ayari (Hz)");
    cv->drawText(menuX + 15, menuY + 55, "2- Paralel Bus Kalibrasyonu");
    cv->drawText(menuX + 15, menuY + 75, "3- I/O Register Eslestirme");
    cv->setPenColor(RGB888(255, 0, 0)); 
    cv->drawText(menuX + 15, menuY + 115, "Kapatmak icin [ESC] basiniz.");
    menuAcikMi = true;
  }

  void menuKapat() {
    if (!menuAcikMi) return;
    auto cv = canvas();
    cv->copyRect(110, 0, menuW, menuH, menuX, menuY);
    menuAcikMi = false;
  }
};

MakinePaneliApp panelApp;

// =========================================================================
// CORE 0 TASK: SERIAL0 (Arduino) VE SERIAL2 (HC-05) AYRIŞTIRMA
// =========================================================================
void Core0SerialTask(void * pvParameters) {
  char bufArduino[128];
  int idxArduino = 0;

  char bufHC05[64];
  int idxHC05 = 0;

  Serial2.begin(9600, SERIAL_8N1, HC05_RX_PIN, HC05_TX_PIN);

  for (;;) {
    
    // 1. KANAL: SERIAL0 (USB / ARDUINO GERİ BİLDİRİMLERİ)
    while (Serial.available() > 0) {
      char c = Serial.read();

      if (c == '\n' || c == '\r') {
        if (idxArduino > 0) {
          bufArduino[idxArduino] = '\0';
          String line = String(bufArduino);
          line.trim();

          if (line.startsWith("INF")) {
            panelApp.addLog(line);
            if (line.indexOf("READY") != -1) {
              arduinoIsReady = true;    
              isProgramRunning = false; 
              machineStatus = 0;         
            }
            else if (line.indexOf("HOMED") != -1 || line.indexOf("PARKED") != -1) {
              machineStatus = 0;         
              isProgramRunning = false;  
            }
          }
          else if (line.startsWith("ERR")) {
            panelApp.addLog(line);
            machineStatus = 2;           
            isProgramRunning = false;    
          }
          else if (line.startsWith("LST")) {
            panelApp.parseProgramList(line);
          }
          else if (line.startsWith("STAT")) {
            if (line.indexOf("HOMING") != -1 || line.indexOf("BUSY") != -1) {
              machineStatus = 1;         
            } else if (line.indexOf("IDLE") != -1) {
              isProgramRunning = false;  
              if (machineStatus != 2) machineStatus = 0; 
            }
          }

          panelApp.rootWindow()->repaint();
          idxArduino = 0;
        }
      } else {
        if (idxArduino < sizeof(bufArduino) - 1) {
          bufArduino[idxArduino++] = c;
        }
      }
    }

    // 2. KANAL: SERIAL2 (HC-05 BLUETOOTH / MOUSE KOORDİNATLARI VE BUTONLAR)
    while (Serial2.available() > 0) {
      char c = Serial2.read();

      if (c == '\n' || c == '\r') {
        if (idxHC05 > 0) {
          bufHC05[idxHC05] = '\0';
          String bluetoothData = String(bufHC05);
          bluetoothData.trim();

          // A) MOUSE KOORDİNAT HAREKETİ
          float raw_dx = 0.0, raw_dy = 0.0;
          if (sscanf(bufHC05, "TOPLAM,%f,%f", &raw_dx, &raw_dy) == 2) {
            mouseX = constrain(mouseX + round(raw_dx * SCALE_X), MIN_X, MAX_X);
            mouseY = constrain(mouseY + round(raw_dy * SCALE_Y), MIN_Y, MAX_Y);
            
            DisplayController.setMouseCursorPos((int)mouseX, (int)mouseY);
          }
          // B) MOUSE BUTON TIKLAMALARI (Doğrudan Çağrılır)
          else if (bluetoothData.startsWith("BUTTONS")) {
            if (bluetoothData.indexOf("L-BUTTON") != -1) {
              panelApp.processMouseClick((int)mouseX, (int)mouseY);
            }
          }

          idxHC05 = 0;
        }
      } else {
        if (idxHC05 < sizeof(bufHC05) - 1) {
          bufHC05[idxHC05++] = c;
        }
      }
    }

    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
}

void setup() {
  disableCore0WDT();
  disableCore1WDT();

  Serial.begin(9600);
  delay(500);

  PS2Controller.begin(fabgl::PS2Preset::KeyboardPort1, fabgl::KbdMode::CreateVirtualKeysQueue);
  DisplayController.begin();
  DisplayController.setResolution(VGA_400x300_60Hz);

  DisplayController.setMouseCursor(fabgl::CursorPointer);
  DisplayController.setMouseCursorPos((int)mouseX, (int)mouseY);

  xTaskCreatePinnedToCore(
    Core0SerialTask,   
    "SerialTask",      
    4096,              
    NULL,              
    1,                 
    NULL,              
    0                  
  );
}

void loop() {
  panelApp.run(&DisplayController);
}
