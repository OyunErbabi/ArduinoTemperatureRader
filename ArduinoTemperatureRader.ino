  int pin_lm35 = A0;
  int value_lm35 = 0;
  float temperature = 0;
  float temperature_voltage = 0;

  float final_temperature = 0;

  void setup() 
  {
    Serial.begin(9600);
  }

  void loop() 
  {
    calculateTemperature();
    printValues();       
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

  void printValues()
  {
    Serial.print("Lm35 Value:  ");
    Serial.println(value_lm35);
    Serial.print("Voltage:  ");
    Serial.println(temperature_voltage);
    Serial.print("Temperature:  ");
    Serial.println(final_temperature/10,1);
    Serial.println("**********************************");
  }
