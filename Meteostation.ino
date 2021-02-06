/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 5
Adafruit_SH1106 display(OLED_RESET);


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

#define BME280_I2C_ADDRESS  0x76
Adafruit_BME280 bme280; // I2C

unsigned long delayTime;

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    delay(100);
    display.clearDisplay();
    display.setTextSize(3);   // text size = 1
    display.setTextColor(WHITE, BLACK);  // set text color to white and black background
    display.setTextWrap(false);           // disable text wrap
    display.setCursor(10, 0);
    // move cursor to position (0, 4) pixel
    display.print("Privet,\nKisa!");
    
//    display.print("W\nE\nA\nT\nH\nE\nR");
    display.setCursor(123, 4);            // move cursor to position (123, 4) pixel
   
//    display.println("S");  display.setCursor(123, display.getCursorY());
//    display.println("T");  display.setCursor(123, display.getCursorY());
//    display.println("A");  display.setCursor(123, display.getCursorY());
//    display.println("T");  display.setCursor(123, display.getCursorY());
//    display.println("I");  display.setCursor(123, display.getCursorY());
//    display.println("O");  display.setCursor(123, display.getCursorY());
//    display.println("N");
    display.display();

    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));
//
    unsigned status;
    
//    status = bme.begin(BME280_I2C_ADDRESS); 


    if( bme280.begin(BME280_I2C_ADDRESS) == 0 )
  {  // connection error or device address wrong!
    display.setCursor(34, 23);
    display.print("Connection");
    display.setCursor(49, 33);
    display.print("Error");
    display.display();        // update the display
    while(1)  // stay here
      delay(1000); 
  }
//
//    if (!status) {
//        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
//        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
//        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
//        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
//        Serial.print("        ID of 0x60 represents a BME 280.\n");
//        Serial.print("        ID of 0x61 represents a BME 680.\n");
//        while (1) delay(10);
//    }
//    
//    Serial.println("-- Default Test --");
//    delayTime = 10000;
//
//    Serial.println();
}




void loop() { 
  display.clearDisplay();
  display.setTextSize(2);
  float temp = bme280.readTemperature();    // get temperature in degree Celsius
  float humi = bme280.readHumidity();       // get humidity in rH%
  float pres = bme280.readPressure();       // get pressure in Pa  
  delay(1000);
  display.setCursor(0, 16);
//  display.print("temp=");
  display.print(temp);
  display.setCursor(0, 32);
//  display.print("hum=");
  
  display.print(humi);
//  display.print("press=");
  display.setCursor(0, 48);
  display.print(pres);
  
  
  display.display();

  delay(1000);
  printValues();
}
//   display.clearDisplay();
//  display.display();
//  Temperature();
//  
//    printValues();
//    delay(delayTime);

//
//void Temperature() {
//  display.clearDisplay();
//  display.display();
//  
//  display.setTextSize(2);    
//  display.setCursor(26,2);
//  int Temp1 = bme.readTemperature();
//  display.setTextColor(WHITE);
//  display.println(Temp1); 
//  
//  display.display();
//  delay(4000);
//}

void printValues() {
//    int Temp = bme.readTemperature();
    Serial.print("Temperature = ");
    Serial.print(bme280.readTemperature());

//    Serial.print(Temp);
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme280.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme280.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme280.readHumidity());
    Serial.println(" %");

    Serial.println();
}
