#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


void Show_Caneco(LiquidCrystal_I2C lcd);
void mostrarMenu(LiquidCrystal_I2C lcd);
void ligarLCD(LiquidCrystal_I2C lcd);
void desligarLCD(LiquidCrystal_I2C lcd);
void Show_Student_Info(unsigned int number_of_informations, String lineText, LiquidCrystal_I2C lcd);




#endif