/*
File        : sw-door.ino
Authors     : Gustavo (guga) && Rafa Baninho
Description :   This code has the intention to open the front
only door, located 

*/
#include <SPI.h>
#include <MFRC522.h>

// Output bits  for the door
const int BIT_0 = 2;
const int BIT_4 = 3;
const int BIT_5 = 4;
const int BIT_6 = 5;
const int TimePerCycle_us  = 1536;

// Start the RFID reader
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);


//internal code
#define CAD_CLOSE 10
#define CAD_OPEN 11
#define uint unsigned int

//Global Variabels
int output[5] = {-1,-1,-1,-1,-1};
uint cont = 0;
uint open = 0;

// Database
byte database[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF},  // Cartão 1
  {0x12, 0x34, 0x56, 0x78}   // Cartão 2
};

const int totalUIDs = sizeof(database) / sizeof(database[0]);

void setup() {
  Serial.begin(9600);
  rfid.PCD_Init();

  //Setup input pin
  pinMode(BIT_0, INPUT);

  //Setup output pins
  pinMode(BIT_4, OUTPUT);
  pinMode(BIT_5, OUTPUT);
  pinMode(BIT_6, OUTPUT);
  digitalWrite(BIT_4, LOW);
  digitalWrite(BIT_5, LOW);
  digitalWrite(BIT_6, LOW);

  // Interruption pins
  attachInterrupt(digitalPinToInterrupt(BIT_0), send, FALLING);
}

void send() {
  if(output[cont] >= 0 & open){
    uint line = (output[cont]-1)/3;
    uint col = (output[cont]-1)%3;

    delayMicroseconds(500*line); //Choose the correct line

    
    digitalWrite(BIT_4+col, HIGH);//Choose the correct collum
    delayMicroseconds(40);
    digitalWrite(BIT_4+col, LOW);
    
    if(cont == 4){
      cont = 0;
      for (int i = 0; i < 5; i++) output[i] = -1;
    }
    else cont++;
  }
  
  


  //digitalWrite(BIT_4, HIGH);
  //delayMicroseconds(40);
  //digitalWrite(BIT_4, LOW);
  //
  //delayMicroseconds(TimePerCycle_us);
  //Serial.println("pressed");
  // digitalWrite(BIT_5, HIGH);
  // digitalWrite(BIT_5, LOW);
  
  // delayMicroseconds(TimePerCycle_us/4);
  // digitalWrite(BIT_6, HIGH);
  // digitalWrite(BIT_6, LOW);
  
  // delayMicroseconds(TimePerCycle_us/4);
  // digitalWrite(BIT_7, HIGH);
  // digitalWrite(BIT_7, LOW);

  // delayMicroseconds(TimePerCycle_us/4);
  // digitalWrite(BIT_8, HIGH);
  // digitalWrite(BIT_8, LOW);
}

/*
unsigned char decode2output(uint number) {
  unsigned char output;
  switch (number) {
    case 1: output |= 1 << 3; break;
    case 2: output |= 1 << 2; break;
    case 3: output |= 1 << 1; break;
    case 4: output |= 1 << 3; break;
    case 5: output |= 1 << 2; break;
    case 6: output |= 1 << 1; break;
    case 7: output |= 1 << 3; break;
    case 8: output |= 1 << 2; break;
    case 9: output |= 1 << 1; break;
    case 10: output |= 1 << 3; break;  //cad close
    case 0: output |= 1 << 2; break;
    case 11: output |= 1 << 1; break;  //cad open
  }

  // Serial print to inform output and the number
  Serial.print("Number: ");
  Serial.print(number);
  Serial.print(" -> Output: ");
  Serial.println(output);

  return output;
}

void write2output(unsigned char input_digits) {
  digitalWrite(BIT_0, (input_digits >> 0) & 1);
  digitalWrite(BIT_1, (input_digits >> 1) & 1);
  // digitalWrite(BIT_2, (input_digits >> 2) & 1);
  // digitalWrite(BIT_3, (input_digits >> 3) & 1);
  // digitalWrite(BIT_4, (input_digits >> 4) & 1);
  // digitalWrite(BIT_5, (input_digits >> 5) & 1);
  // digitalWrite(BIT_6, (input_digits >> 6) & 1);
  // digitalWrite(BIT_7, (input_digits >> 7) & 1);
}
*/

void verificaCartao() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial() || open) {
    return;
  }

  Serial.print("UID detectado: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < totalUIDs; i++) {
    bool igual = true;
    for (int j = 0; j < 4; j++) {
      if (database[i][j] != rfid.uid.uidByte[j]) {
        igual = false;
        break;
      }
    }
    if (igual) {
      open = 1;  // Modifica a variável global
      Serial.println("Cartão autorizado. Variável 'open' alterada para 1.");
      while (rfid.PICC_IsNewCardPresent() || rfid.PICC_ReadCardSerial());
      return;
    }
  }

  Serial.println("Cartão não autorizado. Variável 'open' permanece inalterada.");
  while (rfid.PICC_IsNewCardPresent() || rfid.PICC_ReadCardSerial());
}


// the loop function runs over and over again forever
void loop() {
  VerificaCartao();

}
