#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10    // SS for RFID RC522
#define RST_PIN 9    // Reset pin for RFID RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Predefined UIDs and Names
struct User {
    byte uid[4];      // 4-byte UID
    const char* name;
};

User users[] = {
    {{0x12, 0x34, 0x56, 0x78}, "Alice"},
    {{0x20, 0xBB, 0x47, 0x2F}, "Teckpix"},
    {{0xC3, 0xBC, 0x97, 0x5F}, "Rafa"}
};
const int numUsers = sizeof(users) / sizeof(users[0]);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("RFID Scanner Ready...");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    Serial.print("Card UID: ");
    byte readUID[4];
    for (byte i = 0; i < 4; i++) {
        readUID[i] = mfrc522.uid.uidByte[i];
        Serial.print(readUID[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    const char* name = "Unknown";  // Default if UID not found

    for (int i = 0; i < numUsers; i++) {
        if (memcmp(readUID, users[i].uid, 4) == 0) {
            name = users[i].name;
            break;
        }
    }

    Serial.print("Name: ");
    Serial.println(name);

    logToComputer(readUID, name);
    delay(2000); // Delay to prevent multiple reads

    mfrc522.PICC_HaltA();
}

void logToComputer(byte uid[], const char* name) {
    Serial.print("Logging: UID ");
    for (int i = 0; i < 4; i++) {
        Serial.print(uid[i], HEX);
        Serial.print(" ");
    }
    Serial.print(" | Name: ");
    Serial.println(name);
}
