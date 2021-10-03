#include <AsmTinySerial.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

#define DHT11_PIN 0
#define RIP_PIN 2 

OneWire oneWire(1); // komunikujemy, że będziemy korzysać z interfejsu OneWire na pinie 4
DallasTemperature tempSensor (&oneWire); // komunikujemy, że czujnik DS18B20 będzie wykorzystywał interfejs OneWire
dht DHT; // obiekt do obsługi czujnika wilgotności DHT11

void setup() {
  // rozpoczęcie komunikacji przez BT
  SerialInit( PB3  , 9600);

  // rozpoczęcie pracy czujnika temperatury DS18B20
  tempSensor.begin();
  
  // deklarujemy pin, do którego podłączony jest czujnik ruchu PIR HC-SR501, jako INPUT
  pinMode(RIP_PIN, INPUT);
}

int stop = 10;
float temperatureC = 0;
float temperature = 0;
float humidity = 0;
char str[25];

void loop() {

  // pobranie danych z czujnika temperatury i wilgotności co 10 sek
  if(stop == 10){
    // pobranie danych z czujnika temperatury
    tempSensor.requestTemperatures();
    temperatureC = tempSensor.getTempCByIndex(0);

    // pobranie danych z czujnika wilgotności
    DHT.read11(DHT11_PIN);
    temperature = DHT.temperature;
    humidity = DHT.humidity;

    stop = 0;
  }
  stop++;

  // wysłanie odczytu z czujników przez BT
  dtostrf(temperatureC, 6, 2, str); str[6] = ',';
  dtostrf(temperature, 6, 2, str+7); str[13] = ',';
  dtostrf(humidity, 6, 2, str+14); str[20] = ',';
  sprintf(str+21, "%s", digitalRead(RIP_PIN) == 1 ? "tak" : "nie");
  str[24] = ';';
  SerialTx(str);
  
  delay(1000);
}
