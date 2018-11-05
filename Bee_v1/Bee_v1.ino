#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include "DHT.h"


LiquidCrystal_I2C lcd(0x3F, 20, 4);
HX711 waga;
char odczyt[6];
float ciezar, ciezar_zmiana;

DHT dht;

void setup() {
  waga.begin(A1, A2);
  lcd.begin(); //inicjalizacja ekranu
  lcd.backlight();
  waga.set_scale(419341.0 / 1700);
  waga.tare(20);
  dht.setup(2); // data pin 2
    lcd.clear();
}

void loop() {
  ciezar = waga.get_units(1);  //get_unnits (ilosc pomiarow)
  dtostrf(ciezar, 6, 1, odczyt);
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  if (ciezar_zmiana != ciezar) {
    waga.power_down();

    lcd.setCursor(0, 0);
    lcd.print(odczyt);
    lcd.print(" g");
    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" *C");
        lcd.setCursor(0, 2);
    lcd.print(humidity);
    lcd.print(" %");
  }
  ciezar_zmiana = ciezar;
  waga.power_up();

}
