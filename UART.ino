#include <EEPROM.h>
#define EEPROM_SIZE 64

char ssid [32];
char password [32];

void setupUART() {
  // start serial port
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  Serial.setTimeout(3000);

  // get ssid and password and save in EEPROM
  Serial.print("ssid: ");
  String str = Serial.readString();
  if(str.length() > 0) writeStr(str.c_str(), 0, str.length());
  
  Serial.print("pass: ");
  str = Serial.readString();
  if(str.length() > 0) writeStr(str.c_str(), 32, str.length());

  // get ssid from EEPROM
  readStr(ssid, 0);
  readStr(password, 32);
  EEPROM.end();
}

void writeStr(const char* toStore, int startAddr, int length) {
  int i = 0;
  for(; i < length; i++)EEPROM.write(i+startAddr, toStore[i]);
  for(;i < 32; i++) EEPROM.write(i+startAddr, 0);
  EEPROM.commit();
}

void readStr(char* toRead, int startAddr){
  for(int i = 0; i < 32; i++){
    EEPROM.get(i+startAddr, toRead[i]);
  }
}

void loopUART() {
  // displaying data from the temperature sensor
  Serial.print("Zmierzona temperatura: ");
  Serial.print(temperatureC);
  Serial.println("°C");
  
  // display of data from the humidity sensor
  Serial.print("Zmierzona temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Zmierzona wilgotność:  ");
  Serial.print(humidity);
  Serial.println("%");

  // displaying data from the motion detector
  if (isMotionDetected == HIGH)
    Serial.println("Wykryto ruch!");

  Serial.println("----------------");
}
