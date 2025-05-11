#include "RFID.h"


// Simulated Database
String uidsCadastrados[] = {
  "DE AD BE EF",
  "11 22 33 44",
  "C3 BC 97 5F"
};

// Função para ler UID do cartão e retornar como string
String ReadUID(MFRC522 rfid) {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return "";
  }

  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidStr += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uidStr += " ";
  }
  rfid.PICC_HaltA();
  uidStr.toUpperCase();
  return uidStr;
}

// Verifica se UID está no banco
bool CheckUID(String uid) {
  for (String cadastrado : uidsCadastrados) {
    if (uid.equalsIgnoreCase(cadastrado)) {
      return true;
    }
  }
  return false;
}

