// include libraries
#include <Adafruit_SH1106.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include "BluetoothSerial.h"
#include <PubSubClient.h>

// global variables
String temperatureC; // zmienna zawierająca odczyt z czujnika
String temperature; // odczyt temperatury z czujnika wilgotności
String humidity; // odczyt wilgotności z czujnika wilgotności
int isMotionDetected = 0; // stan czujnika ruchu

// function prototypes
void setupBT();
void loopBT();
void setupUART();
void loopUART();
void setupDisplay();
void loopDisplay();
void setupWiFi();
void loopWiFi();
void setupMQTT();
void loopMQTT();
String processor(const String& var);
