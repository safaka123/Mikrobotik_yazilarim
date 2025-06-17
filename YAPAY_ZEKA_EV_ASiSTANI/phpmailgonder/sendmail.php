<?php
// send.php

// PHPMailer sınıflarını dahil et
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;
use PHPMailer\PHPMailer\SMTP; 

// PHPMailer'ı Composer ile yüklediyseniz:
//require 'vendor/autoload.php';

// PHPMailer'ı manuel yüklediyseniz (bu satırları kullanın ve yolunu ayarlayın):
require 'PHPMailer/src/Exception.php';
require 'PHPMailer/src/PHPMailer.php';
require 'PHPMailer/src/SMTP.php';

// Güvenli config.php dosyasını dahil et
// Buradaki yol, sizin config.php dosyasının konumuna göre ayarlanmalıdır.
// Eğer config.php, send.php'nin bulunduğu klasörün BİR ÜST KLASÖRÜNDEYSE:
require_once '/home/mikrobot/php/docs/config.php';  //************  bu dizini kendi dosyanızın dizinine göre değiştirin. 
// Eğer config.php, send.php'nin bulunduğu klasörle aynı seviyede ve erişilemeyen bir dizindeyse,
// Örneğin 'private_includes' gibi bir klasörde:
// require_once '/home/kullaniciadi/private_includes/config.php'; // Kendi hosting yolunuzu girin

// --- Parametreleri alma (örneğin GET veya POST ile) ---
// Bu kısım, e-postaya eklemek istediğiniz dinamik bilgileri almanızı sağlar.
// Örnek olarak bir 'alarm' parametresi alalım:
$alarm_bilgisi = "ev otomasyonunda problem var."; // Varsayılan değer
//if (isset($_GET['alarm']) && !empty($_GET['alarm'])) {
//    $alarm_bilgisi = htmlspecialchars($_GET['alarm']);
//} elseif (isset($_POST['alarm']) && !empty($_POST['alarm'])) {
//    $alarm_bilgisi = htmlspecialchars($_POST['alarm']);
//}

// ---- PHPMailer ile E-posta Gönderme İşlemi ----
$mail = new PHPMailer(true); // 'true' ile istisna yakalamayı etkinleştirin

try {
    // SMTP Sunucusu Ayarları
    $mail->isSMTP();                                            // SMTP kullan
    $mail->Host       = 'smtp.gmail.com';                       // Gmail SMTP sunucusu
    $mail->SMTPAuth   = true;                                   // SMTP kimlik doğrulaması gerekli
    $mail->Username   = GMAIL_USERNAME;                         // config.php'den al
    $mail->Password   = GMAIL_APP_PASSWORD;                     // config.php'den al
    $mail->SMTPSecure = PHPMailer::ENCRYPTION_STARTTLS;         // TLS şifreleme kullan (Gmail için)
    $mail->Port       = 587;                                    // TLS için SMTP portu

    // Gönderen Ayarları
    $mail->setFrom(MAIL_FROM_EMAIL, MAIL_FROM_NAME); // config.php'den al

    // Alıcı Ayarları (config.php'den veya dinamik olarak)
    $recipients = explode(',', DEFAULT_MAIL_TO); // Virgülle ayrılmış alıcıları diziye çevir
    foreach ($recipients as $recipient) {
        $mail->addAddress(trim($recipient));
    }

    // CC Alıcıları (config.php'den, boş değilse)
    if (!empty(DEFAULT_MAIL_CC)) {
        $cc_recipients = explode(',', DEFAULT_MAIL_CC);
        foreach ($cc_recipients as $cc_recipient) {
            $mail->addCC(trim($cc_recipient));
        }
    }

    // E-posta İçeriği Ayarları
    $mail->isHTML(true); // E-postayı HTML olarak ayarla
    $mail->CharSet = 'UTF-8'; // Türkçe karakterler için

    $mail->Subject = "Ev Otomasyonu Bilgisi: " . $alarm_bilgisi; // Konuya alarm bilgisini ekle

    $message_body = "
        <html>
        <head>
        <title>Ev Otomasyonu Bildirimi</title>
        </head>
        <body>
        <p>Merhaba,</p>
        <p>Ev otomasyon sisteminizden yeni bir bildirim var:</p>
        <p><strong>Bilgi:</strong> " . $alarm_bilgisi . "</p>
        <p>Detaylı bilgiler için kontrol paneline bakabilirsiniz.</p>
        <table>
        <tr>
        <th>Parametre</th>
        <th>Değer</th>
        </tr>
        <tr>
        <td>Zaman</td>
        <td>" . date('Y-m-d H:i:s') . "</td>
        </tr>
        <tr>
        <td>Kaynak IP</td>
        <td>" . ($_SERVER['REMOTE_ADDR'] ?? 'Bilinmiyor') . "</td>
        </tr>
        </table>
        <p>İyi günler dileriz.</p>
        </body>
        </html>
    ";

    $mail->Body = $message_body;
    $mail->AltBody = "Ev Otomasyonu Bildirimi: " . $alarm_bilgisi . "\n\nDetaylı bilgiler için kontrol paneline bakabilirsiniz.";

    $mail->send();
    echo 'E-posta başarıyla gönderildi.';
} catch (Exception $e) {
    echo "E-posta gönderilemedi. Hata: {$mail->ErrorInfo}";
    // Hata ayıklama için detaylı bilgi:
    // echo "<br>PHPMailer Hatası: " . $mail->ErrorInfo;
}
?>
