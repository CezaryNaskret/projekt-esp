// -------- Bluetooth

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#endif

BluetoothSerial SerialBT;

void setupBT() {
  SerialBT.begin("ESP32test"); //Bluetooth device name
}

// the frame looks like this: [number,number,number,tak/nie] e.g.: [000.00,000.00,000.00,tak] 
void loopBT() {
  // receiving the frame
  if (SerialBT.available()) {
    // the variable to which the frame will be written
    String data = "";
    
    // waiting for the frame to start
    while(SerialBT.read() != '[');
    
    // receiving 25 characters
    for(int i = 0; i < 25; i++){
      char received = SerialBT.read();
//      Serial.print(received);
      data = data+received;
    }
    
    // saving data to variables
    temperatureC = data.substring(0,5);
    temperature = data.substring(7,12);
    humidity = data.substring(14,19);
    isMotionDetected = data[21] == 't' ? 1 : 0;
  }

  // omitting the remaining received data
  while(SerialBT.available()){
    char received = SerialBT.read();
//    Serial.print(received);
  }
//  Serial.println();
}
