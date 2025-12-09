#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

// RFID
#define SS_PIN 5
#define RST_PIN 22

// Komponen lain
#define BUZZER_PIN 4
#define SERVO_PIN 25
#define GREEN_LED 2
#define RED_LED 17

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n=== RFID + Servo System ===");
  
  // Alokasi timer
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  // Init servo
  myServo. setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2500);
  myServo.write(0);
  delay(1000);
  
  Serial.println("Servo initialized");
  
  // Init SPI & RFID
  SPI. begin();
  delay(100);
  
  rfid.PCD_Init();
  delay(100);
  
  // Init komponen lain
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // Cek RFID
  byte version = rfid. PCD_ReadRegister(rfid. VersionReg);
  Serial.print("RFID Firmware:  0x");
  Serial.println(version, HEX);
  
  if (version == 0x00 || version == 0xFF) {
    Serial.println("ERROR: RFID tidak terdeteksi!");
  } else {
    Serial.println("RFID OK!");
  }
  
  Serial.println("\nTempelkan kartu...\n");
}

void moveServo(int targetAngle) {
  // Disable RFID
  rfid.PCD_AntennaOff();
  delay(100);
  
  // Detach dan reattach servo
  myServo.detach();
  delay(50);
  
  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2500);
  delay(50);
  
  // Gerakkan servo
  myServo.write(targetAngle);
  
  // Hold position
  for (int i = 0; i < 20; i++) {
    myServo.write(targetAngle);
    delay(100);
  }
  
  // Re-enable RFID
  delay(100);
  rfid.PCD_AntennaOn();
  delay(100);
}

void loop() {
  // Cek kartu
  digitalWrite(RED_LED, HIGH);

  if (!rfid.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  
  Serial.println(">>> Kartu terdeteksi!");
  
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Gagal baca kartu");
    delay(50);
    return;
  }
  
  // Tampilkan UID
  Serial. print("UID:  ");
  for (byte i = 0; i < rfid. uid.size; i++) {
    Serial.print(rfid. uid.uidByte[i] < 0x10 ?  " 0" : " ");
    Serial.print(rfid. uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Halt RFID
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(200);
  
  // Buzzer & LED
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  tone(BUZZER_PIN, 1000, 200);
  delay(300);
  
  // Buka pintu
  Serial. println("Membuka pintu...");
  moveServo(90);
  
  Serial.println("Pintu terbuka!  Tunggu 5 detik...");
  delay(5000);
  
  // Tutup pintu
  Serial.println("Menutup pintu.. .");
  moveServo(0);
  
  digitalWrite(GREEN_LED, LOW);
  Serial.println("Pintu tertutup!\n");
  
  delay(1000);
}   