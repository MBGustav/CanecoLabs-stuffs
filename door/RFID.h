#ifndef RFID_H
#define RFID_H

#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>



String ReadUID(MFRC522 rfid);
bool CheckUID(String uid);


#endif