#include "matrix_button.h"

String keyMap[10] = {
    "0",    // '0'
    "1",    // '1'
    "ABC",  // '2'
    "DEF",  // '3'
    "GHI",  // '4' 
    "JKL",  // '5'
    "MNO",  // '6'
    "PQRS", // '7'
    "TUV",  // '8'
    "WXYZ"  // '9'
  };
  
  unsigned long lastPressTime = 0;
  char lastKey = '\0';
  int charIndex = 0; // Position of the char
  String lineText = "";
  const unsigned long timeout = 1000; // 1 second

  
void Enter_Student_Info(Keypad keypad, LiquidCrystal_I2C lcd){

  unsigned int number_of_informations = 3; // Name, Surname and RA
  Show_Student_Info(number_of_informations, lineText, lcd);

  while(number_of_informations != 0) {
    char key = keypad.getKey();
    unsigned long currentTime = millis();
  
    if (key) {
      if (key >= '0' && key <= '9') {
        if(number_of_informations !=1 ){
          if (key == lastKey && (currentTime - lastPressTime) < timeout) { // Change to the next char in keyMap[]
            charIndex++;
            if (charIndex >= keyMap[key - '0'].length()) {
              charIndex = 0;
            }
          } else { // Put the lastKey in the LCD
            if (lastKey != '\0' && (currentTime - lastPressTime) < timeout) {
              lineText += keyMap[lastKey - '0'][charIndex];
              Show_Student_Info(number_of_informations, lineText, lcd);
            }
            lastKey = key;
            charIndex = 0;
          }
          lastPressTime = currentTime;
        } 
        else{
          lineText += key;
          Show_Student_Info(number_of_informations, lineText, lcd);
        }
      }
      else if (key == '*') { // Delete the last char in the LCD
        if (lineText.length() > 0) {
      lineText.remove(lineText.length() - 1);
      Show_Student_Info(number_of_informations, lineText, lcd);
          }
          lastKey = '\0';
        }
        else if (key == '#') { //Confirm the information
          if (lastKey != '\0' && (currentTime - lastPressTime) < timeout) {
      lineText += keyMap[lastKey - '0'][charIndex];
          }
          // Sent_to_Server(number_of_informations, lineText);
          lineText = "";
          number_of_informations--;
          lastKey = '\0';
          charIndex = 0;
          Show_Student_Info(number_of_informations, lineText, lcd);
        }
      }
  
      if (lastKey != '\0' && (currentTime - lastPressTime) > timeout) {
        if(number_of_informations != 1){
          lineText += keyMap[lastKey - '0'][charIndex];
          Show_Student_Info(number_of_informations, lineText, lcd);
          lastKey = '\0';
          charIndex = 0;
        }
      }
  }

}

