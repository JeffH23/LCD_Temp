
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");

  lcd.init();
  lcd.backlight();
  
}

void loop(void)
{ 
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures(); 
  
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print((char)176);//shows degrees character
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print((char)176);//shows degrees character
    Serial.println("F");
  }
  lcd.setCursor(0,0);
  lcd.print(DallasTemperature::toFahrenheit(sensors.getTempCByIndex(0)));
  lcd.setCursor(5,0);
  lcd.print(" F");

  lcd.setCursor(0,1);
  lcd.print(DallasTemperature::toFahrenheit(sensors.getTempCByIndex(1)));
  lcd.setCursor(5,1);
  lcd.print(" F");
  Serial.println("");
  
  delay(10000);
}
