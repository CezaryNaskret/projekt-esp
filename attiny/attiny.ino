#include "SoftwareSerial.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

#define DHT11_PIN 0
#define RIP_PIN 2 
#define TxD 3
#define RxD 4

OneWire oneWire(1); // komunikujemy, że będziemy korzysać z interfejsu OneWire na pinie 4
DallasTemperature tempSensor (&oneWire); // komunikujemy, że czujnik DS18B20 będzie wykorzystywał interfejs OneWire
dht DHT; // obiekt do obsługi czujnika wilgotności DHT11
SoftwareSerial SerialBT(RxD, TxD); // serial do komunikacji przez Bluetooth

void setup() {
  // rozpoczęcie komunikacji przez BT
  SerialBT.begin(9600); 
  pinMode(TxD, OUTPUT);
  pinMode(RxD, INPUT);

  // rozpoczęcie pracy czujnika temperatury DS18B20
  tempSensor.begin();
  
  // deklarujemy pin, do którego podłączony jest czujnik ruchu PIR HC-SR501, jako INPUT
  pinMode(RIP_PIN, INPUT);
}

void loop() {
  // wysłąnie odczytu z czujnika temperatury przez BT
  tempSensor.requestTemperatures();
  SerialBT.print(tempSensor.getTempCByIndex(0));
  SerialBT.print(",");

  // wysłanie odczytu z czujnika wilgotności przez BT
  DHT.read11(DHT11_PIN);
  SerialBT.print(DHT.temperature);
  SerialBT.print(",");
  SerialBT.print(DHT.humidity);
  SerialBT.print(",");

  String isMotionDetected = digitalRead(RIP_PIN) == 1 ? "tak" : "nie";
  SerialBT.println(isMotionDetected);
  
  delay(1000);
}
