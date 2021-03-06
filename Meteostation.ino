/***************************************************************************
TODO: разнести функции дисплея и метеодатчика по файлам.
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h> //нужна для 1.3 дисплея, контроллер SH1106
//#include <Adafruit_SSD1306.h> //нужна для 0,96 дисплея, контроллер SSD1306. 

/*In Adafruit_SSD1306.h you should find "dim". You need pass to it "false". 
  void dim(bool dim = false);
*/
 
#define SEALEVELPRESSURE_HPA (1013.25)
#define BME280_I2C_ADDRESS  0x76
#define OLED_RESET 5

Adafruit_BME280 bme280; // I2C
Adafruit_SH1106 display(OLED_RESET); // for 1.3" display
//Adafruit_SSD1306 display(OLED_RESET); // for 0.96" display




unsigned long delayTime;

void setup() {
    display.begin(SH1106_SWITCHCAPVCC, 0x3C); //here you can don't change to SH1106
    delay(100);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);  // set text color to white and black background
    display.setTextWrap(false);           // disable text wrap
    display.print("Start\nservice");
    display.display();
    delay(3000);

    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));
    unsigned status;
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
}

void loop() { 
  display.clearDisplay();
  display.setTextSize(2);
  float temperature = bme280.readTemperature();    // get temperature in degree Celsius
  float humidity = bme280.readHumidity();       // get humidity in rH%
  float pressure = (bme280.readPressure()) * 0.00750062;       // get pressure in Pa  
  display.setCursor(0, 16);

  display.print(temperature, 1); display.print(" *C");
  display.setCursor(0, 32);
  display.print(humidity, 0); display.print(" %");
  display.setCursor(0, 48);
  display.print(pressure, 0); display.print(" mm Hg");
  
  display.display();

  delay(30000);
  printValues();
}

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
