/*
File        : sw-door.ino
Authors     : Gustavo (guga) && Rafa Baninho
Description : This code has the intention to open the front
only door, located in the Computer Departament of University of São Carlos 
Simulation  : https://wokwi.com/projects/429666233774245889
*/

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#include "guaxinin.h"s
#include "LCD.h"
#include "matrix_button.h"
#include "motor.h"
#include "RFID.h"

// Control the door motor
#define IN1 17// white wire17
#define IN2 16 // purple wire 16
#define ENABLE_PIN 35 // control pin (green wire)


LiquidCrystal_I2C lcd(0x27, 16, 2); 

RFID RC522
#define SS_PIN 5
#define RST_PIN 4
MFRC522 rfid(SS_PIN, RST_PIN);


// Button matrix 4x3
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// The pins for the ESP32
byte rowPins[ROWS] = {27, 26, 25, 33}; 
byte colPins[COLS] = {32, 15, 4};  // 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


bool firstPress = false;
bool lcdLigado = false;
unsigned long tempoUltimaTecla = 0;
const unsigned long tempoDesligar = 30000;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENABLE_PIN, INPUT); 

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, Guaxinin_0);
  lcd.createChar(1, Guaxinin_1);
  lcd.createChar(2, Guaxinin_2);
  lcd.createChar(3, Guaxinin_3);
  lcd.createChar(4, Guaxinin_4);
  lcd.createChar(5, Guaxinin_5);
  lcd.createChar(6, Guaxinin_6);

  SPI.begin();
  rfid.PCD_Init();
}


void abrirPorta() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o cartao");
  
  // Espera até cartão ser lido
  String uid = "";
  while (uid == "") {
    uid = ReadUID(rfid);
  }

  lcd.clear();
  if (CheckUID(uid)) {
    lcd.setCursor(0, 0);
    lcd.print("Abrindo :)");
    Open();
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Nao cadastrado");
  }

  lcd.setCursor(0, 1);
  lcd.print(uid);
  
  Open();
  delay(2000);
  mostrarMenu(lcd);
}

void marcarHorario() {
  lcd.clear();
  lcd.print("Marcando hora...");
  delay(2000);
  mostrarMenu(lcd);
}

void checarCadastro() {
  lcd.clear();
  lcd.print("Marcando hora...");
  delay(2000);
  mostrarMenu(lcd);
}

void criarCadastro() {
  lcd.clear();
  Enter_Student_Info(keypad, lcd);
  tempoUltimaTecla = millis();
  delay(500);
  mostrarMenu(lcd);
}
*/
void pedirSenha() {

  String senhaDigitada = "";

  while (true) {
    char tecla = keypad.getKey();
    if (tecla) {
      if (tecla == '*') {
        break; // Confirma a senha
      } else if (tecla == '#') {
        senhaDigitada = ""; // Limpa a entrada
      } else if (isDigit(tecla) && senhaDigitada.length() < 10) {
        senhaDigitada += tecla;
      }
    }
  }

  if (senhaDigitada == "13579") {
    Open();
  } else {
  }

  delay(2000);
}






void loop() {
  CloseAutomatcaly();

  char tecla = keypad.getKey();

  if (tecla) {
    tempoUltimaTecla = millis(); // Reinicia contagem de tempo de inatividade

    if (!lcdLigado) {
      ligarLCD(lcd);
      lcdLigado = true;
      firstPress = true;
    }

    // A qualquer momento, aceita a escolha do menu
    if(!firstPress){
      switch (tecla) {
        case '1': abrirPorta(); break;
        case '2': marcarHorario(); break;
        case '3': checarCadastro(); break;
        case '4': criarCadastro(); break;
        case '5': pedirSenha(); break;
        default: break; // ignora outras teclas
      }
    }
    firstPress = false;
  }

  // Desliga o LCD após 10 segundos de inatividade
  if (lcdLigado && (millis() - tempoUltimaTecla > tempoDesligar)) {
    desligarLCD(lcd);
    lcdLigado = false;
  }
}



