#include <AsmTinySerial.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

#define DHT11_PIN 1
#define PIR_PIN 2 

OneWire oneWire(0); // declaration that we will be using the OneWire interface on pin 0
DallasTemperature tempSensor (&oneWire); // declaration that the DS18B20 sensor will use the OneWire interface
dht DHT; // object to operate the DHT11 humidity sensor

void setup() {
  // start of communication via BT
  SerialInit(PB4  , 9600);

  // starts of DS18B20 temperature sensor
  tempSensor.begin();
  
  // declare the pin to which the HC-SR501 PIR motion sensor is connected as INPUT
  pinMode(PIR_PIN, INPUT);
}

float temperatureC = 0;
float temperature = 0;
float humidity = 0;
float newTemperature = 0;
float newHumidity = 0;
char str[26];

void loop() {
  // getting data from the temperature sensor
  tempSensor.requestTemperatures();
  temperatureC = tempSensor.getTempCByIndex(0);

  // getting data from the humidity sensor
  DHT.read11(DHT11_PIN);
  temperature = DHT.temperature;
  humidity = DHT.humidity;

  if(newTemperature == 0 || temperature - newTemperature < 10){
    newTemperature = temperature;
    newHumidity = humidity;
  }

  // sending data from sensors via BT
  str[0] = '[';
  dtostrf(temperatureC, 6, 2, str+1); str[7] = ',';
  dtostrf(newTemperature, 6, 2, str+8); str[14] = ',';
  dtostrf(newHumidity, 6, 2, str+15); str[21] = ',';
  sprintf(str+22, "%s", digitalRead(PIR_PIN) == 1 ? "tak" : "nie");
  str[25] = ']';
  SerialTx(str);
  
  delay(1000);
}
