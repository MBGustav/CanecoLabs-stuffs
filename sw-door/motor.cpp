#include "motor.h"

// Control the door motor
#define IN1 17// white wire
#define IN2 16 // purple wire 
#define ENABLE_PIN 35 // control pin (green wire)

void Open(){
    while(digitalRead(ENABLE_PIN)== HIGH){
    digitalWrite(IN1, LOW);   
    digitalWrite(IN2, HIGH);  
    delay(50);
    }
  
  
    digitalWrite(IN1, HIGH);   // Both transistors OFF → L298N = LOW
    digitalWrite(IN2, HIGH);
    delay(1000);
  
  }
  
void Close(){
    while(digitalRead(ENABLE_PIN)== LOW){
      digitalWrite(IN1, HIGH);   // Transistor OFF → L298N IN1 = LOW
      digitalWrite(IN2, LOW);    // Transistor ON → L298N IN2 = HIGH
      delay(50);
    }
  
    // Stop
    digitalWrite(IN1, HIGH);   // Both transistors OFF → L298N = LOW
    digitalWrite(IN2, HIGH);
    delay(1000);
  
  }
  
void CloseAutomatcaly(){
    if(digitalRead(ENABLE_PIN)== LOW){
        delay(5000);
        Close();
    }
}