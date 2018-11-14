#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include "HX711.h"
#include "DHT.h"


LiquidCrystal_I2C lcd(0x3F, 20, 4);
DS3231 clock;
RTCDateTime dt;
HX711 waga;
char odczyt[6];
float ciezar, ciezar_zmiana;

DHT dht;

void setup() {
  clock.begin();                          //inicjalizacja RTC
  clock.setDateTime(__DATE__, __TIME__);  // Set sketch compiling time
  waga.begin(A1, A2);                     //inicjalizacja wagi
  lcd.begin();                            //inicjalizacja ekranu
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
  clock.forceConversion();
  dt = clock.getDateTime();


  if (ciezar_zmiana != ciezar) {
    waga.power_down();

    lcd.setCursor(0, 0);
    lcd.print(odczyt);  lcd.print(" g");
    
    lcd.setCursor(0, 1);
    lcd.print(int(temperature)); lcd.print(" *C RTCt=");  lcd.print(clock.readTemperature());
    
    lcd.setCursor(0, 2);
    lcd.print(humidity);  lcd.print(" %");
    
    lcd.setCursor(0, 3);
    lcd.print(clock.dateFormat("d-m-Y H:i:s", dt));
  }
  ciezar_zmiana = ciezar;
  waga.power_up();

}
