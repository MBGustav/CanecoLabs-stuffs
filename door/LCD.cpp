#include "LCD.h"

void Show_Caneco(LiquidCrystal_I2C lcd){
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.print("   CANECO");
  

  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.write(6);
  lcd.print("   LABS");
  delay(1000);

}

void mostrarMenu(LiquidCrystal_I2C lcd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1:ID 2:Hor 3:Che");
  lcd.setCursor(0, 1);
  lcd.print("4:Cri 5:Sen");
}

void ligarLCD(LiquidCrystal_I2C lcd) {
  lcd.begin(16, 2);
  lcd.backlight();
  Show_Caneco(lcd);
  mostrarMenu(lcd);
}

void desligarLCD(LiquidCrystal_I2C lcd) {
  lcd.clear();
  lcd.noBacklight();
}

void Show_Student_Info(unsigned int number_of_informations, String lineText, LiquidCrystal_I2C lcd){
    lcd.clear();
    lcd.setCursor(0, 0);

    if(number_of_informations == 3)
        lcd.print("Nome:");
    else{
        if(number_of_informations == 2)
            lcd.print("Sobrenome:");
        else    
            lcd.print("RA:");
    }

    lcd.setCursor(0, 1);
    lcd.print(lineText);
}