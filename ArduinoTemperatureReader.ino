#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C screen(0x3F,16,2);

int redLed = 3;
int yellowLed = 5;
int blueLed = 6;

int pin_lm35 = A0;
int value_lm35 = 0;
float temperature = 0;
float temperature_voltage = 0;

float final_temperature = 0;

String temperatureText = "";

void setup() 
{
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed ,OUTPUT);
  pinMode(blueLed, OUTPUT);

  setLed(0,0,0);
  screen.init();
  screen.backlight(); 
  
  Serial.begin(9600);
}

void loop() 
{
  calculateTemperature();
  switchLedLight();
  printValuesI2cScreen(); 
  printValuesSerial();
  delay(1000);
}

void calculateTemperature()
{
  final_temperature = 0;  
  for(int i = 0; i < 10; i++) 
  {
     value_lm35 = analogRead(pin_lm35);
     temperature_voltage = (value_lm35/1023.0)*5000;
     temperature = temperature_voltage/10.0;
     final_temperature += temperature;
     delay(10);
  }     
}

void switchLedLight()
{
  switch((int)final_temperature/10)
  {
    case -50 ... 19:
        setLed(0,0,50);
        temperatureText = "Cold";
        break;
    case 20 ... 29:
        setLed(0,50,0);
        temperatureText = "Normal";
        break;
    case 30 ... 100:
        setLed(50,0,0);
        temperatureText = "Hot!";
        break;
    default:
        setLed(50,50,50);
        temperatureText = "ERR!";
        break; 
  }
}

void printValuesI2cScreen()
{
  screen.clear();
  screen.setCursor(0,0);
  screen.print("Temperature");
  screen.setCursor(0,1);
  screen.print(final_temperature/10,1);
  screen.print(" C");
  screen.setCursor(10,1);
  screen.print(temperatureText);
}

void setLed(int r, int y ,int b)
{
  analogWrite(redLed,r);
  analogWrite(yellowLed,y);
  analogWrite(blueLed,b);
}

void printValuesSerial()
{
  Serial.print("Lm35 Value:  ");
  Serial.println(value_lm35);
  Serial.print("Voltage:  ");
  Serial.println(temperature_voltage);
  Serial.print("Temperature:  ");
  Serial.println(final_temperature/10,1);
  Serial.println("**********************************");
}
