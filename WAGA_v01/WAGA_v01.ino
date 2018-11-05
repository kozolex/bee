#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"


LiquidCrystal_I2C lcd(0x3F, 20, 4);
HX711 waga;
char odczyt[6];
float ciezar, ciezar_zmiana;

void setup() {
  waga.begin(A1, A2);
  lcd.begin(); //inicjalizacja ekranu
  lcd.backlight();
  waga.set_scale(419341.0 / 1700);
  waga.tare(20);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Odczyt wagi:");
}

void loop() {
  ciezar = waga.get_units(1);  //get_unnits (ilosc pomiarow)
  dtostrf(ciezar, 6, 1, odczyt);
  if (ciezar_zmiana != ciezar) {
    waga.power_down();

    lcd.setCursor(0, 1);
    lcd.print(odczyt);
    lcd.print(" g");
  }
  ciezar_zmiana = ciezar;
  waga.power_up();

}
