// include libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_SH1106.h>
#include <DHT.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// global variables
float temperatureC; // zmienna zawierająca odczyt z czujnika
float temperature; // odczyt temperatury z czujnika wilgotności
float humidity; // odczyt wilgotności z czujnika wilgotności
int outputPin = 5; // pin do którego podłączymy diode LED
int isMotionDetected = 0; // stan czujnika ruchu

// function prototypes
void setupTemperature();
void loopTemperature();
void setupHumidity();
void loopHumidity();
void setupMove();
void loopMove();
void serialPrintTHM();
void setupDisplay();
void displayPrintTHM();
void setupWiFi();
