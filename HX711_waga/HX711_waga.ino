#include "HX711.h"
#include <LiquidCrystal.h>

HX711 waga;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
char odczyt[6];
float ciezar;

void setup() {
  waga.begin(A1, A2);
  lcd.begin(16,2); //inicjalizacja ekranu       
  lcd.setCursor(0,0);
  waga.set_scale(419341.0/200.0);                  
  waga.tare(20);				       
}

void loop() {
  ciezar=waga.get_units(10);
  dtostrf(ciezar,6,1,odczyt);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Odczyt wagi:");
  lcd.setCursor(0,1);
  lcd.print(odczyt);
  lcd.print(" g");
  waga.power_down();
  delay(100);
  waga.power_up();
}
