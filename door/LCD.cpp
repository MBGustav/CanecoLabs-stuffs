#include "LCD.h"

void mostrarMenu(LiquidCrystal_I2C lcd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1:Abrir 2:Horario");
  lcd.setCursor(0, 1);
  lcd.print("3:Checar 4:Criar");
}

void ligarLCD(LiquidCrystal_I2C lcd) {
  lcd.begin(16, 2);
  lcd.backlight();
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