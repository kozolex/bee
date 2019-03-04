#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include "HX711.h"
#include "DHT.h"
// include the SD library:
#include <SPI.h>
#include <SD.h>


LiquidCrystal_I2C lcd(0x3F, 20, 4);
DS3231 clock;
RTCDateTime dt;
HX711 waga;     //fiolet 6 / zielony 7 / czerwony VCC / niebieski / GND
char odczyt[6];
float ciezar, ciezar_zmiana;

DHT dht;
const int chipSelect = 4; //PIN SD CARD
void setup() {
  clock.begin();                          //inicjalizacja RTC
  clock.setDateTime(__DATE__, __TIME__);  // Set sketch compiling time
  waga.begin(7, 6);                     //inicjalizacja wagi
  lcd.begin();                            //inicjalizacja ekranu
  lcd.backlight();
  waga.set_scale(419341.0 / 1700);
  waga.tare(20);
  dht.setup(2); // data pin 2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing SD card...");

  // see if the card is present and can be initialized:

  lcd.setCursor(0, 1);
  if (!SD.begin(chipSelect)) {
    lcd.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  lcd.println("card initialized.");
  delay(200);
  
  lcd.clear();
}


void loop() {
  File dataFile = SD.open("log.csv", FILE_WRITE);
  String dataString = "";   //stron przechowujący wiersz
  ciezar = waga.get_units(10);  //get_unnits (ilosc pomiarow)
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
    lcd.print(int(temperature)); //lcd.print(" *C RTCt="); lcd.print(clock.readTemperature());

    lcd.setCursor(0, 2);
    lcd.print(humidity);  lcd.print(" %");

    lcd.setCursor(0, 3);
    lcd.print(clock.dateFormat("d-m-Y H:i:s", dt));
  }
  ciezar_zmiana = ciezar;
  waga.power_up();

  
  dataString += String(clock.dateFormat("d-m-Y H:i:s", dt));
  dataString += String(";");
  dataString += String(odczyt);
  dataString += String(";");
  dataString += String(temperature);
  dataString += String(";");
  dataString += String(clock.readTemperature());
  dataString += String(";");
  dataString += String(humidity);
/*
  delay(900);
  // if the file is available, write to it:
  lcd.setCursor(9, 0);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    lcd.print("ZAPIS...   ");
  }
  // if the file isn't open, pop up an error:
  else {
    lcd.print("  error    ");
  }
  */
  delay(100);
  lcd.setCursor(9, 0);
  lcd.print("           ");

}
