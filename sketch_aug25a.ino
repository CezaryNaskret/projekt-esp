// include libraries
#include <Adafruit_SH1106.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "BluetoothSerial.h"

// global variables
String temperatureC; // zmienna zawierająca odczyt z czujnika
String temperature; // odczyt temperatury z czujnika wilgotności
String humidity; // odczyt wilgotności z czujnika wilgotności
int outputPin = 23; // pin do którego podłączymy diode LED
int isMotionDetected = 0; // stan czujnika ruchu

// function prototypes
void serialPrintTHM();
void setupDisplay();
void displayPrintTHM();
void setupWiFi();
void setupBT();
void loopBT();
