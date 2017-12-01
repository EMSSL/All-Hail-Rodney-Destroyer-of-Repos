// Code for the BMP pressure sensor (retired)
// Written by CDY on 11/14/17
//
// Circuit is as follows:
// Arduino UNO, BMP183 sensor
//    UNO 4   -> BMP CS
//    UNO 5   -> BMP SDI
//    UNO 6   -> BMP SDO
//    UNO 7   -> BMP CLK
//    UNO +5V -> BMP Vin
//    UNO GND -> BMP GND


// libraries
#include <Adafruit_BMP183.h>      // load the barometer library

// pins
#define BMP183_CLK  7              // Baro serial clock software SPI
#define BMP183_SDO  6              // Baro MISO software SPI
#define BMP183_SDI  5              // Baro MOSI software SPI
#define BMP183_CS   4              // Baro chip select software SPI
unsigned int tme = 0;

// tell arduino what BMP is
Adafruit_BMP183 bmp = Adafruit_BMP183(BMP183_CLK, BMP183_SDO, BMP183_SDI, BMP183_CS);

void setup() {
  
  // setup serial com with computer
  Serial.begin(9600);

  // check to see if the barometer is working
  bmp.begin();

}

void loop() {
  
  // get current time info
  tme = millis();
  Serial.print("Time: ");
  Serial.println(tme);

  Serial.println("Barometer Data");
  Serial.print("Pressure:    ");
  Serial.print(bmp.getPressure());
  float pressure = bmp.getPressure();   // pressure in Pa
  Serial.print(" Pascals / ");
  Serial.print(bmp.getPressure() / 100);
  Serial.println(" millibar (hPa)");
  float temperature = bmp.getTemperature(); // temperature in degC
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.println(" ");

  delay(500);  

}
