// -------- Bluetooth

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#endif

BluetoothSerial SerialBT;

void setupBT() {
  SerialBT.begin("ESP32test"); //Bluetooth device name
}

// ramka wygląda tak: [liczba,liczba,liczba,tak/nie] przykład: [000.00,000.00,000.00,tak] 
void loopBT() {
  // odebranie ramki
  if (SerialBT.available()) {
    // zmienna do której zapiszemy ramkę
    String data = "";
    
    // czekamy na rozpoczęcie ramki
    while(SerialBT.read() != '[');
    
    // odebranie 25 znaków
    for(int i = 0; i < 25; i++){
      char received = SerialBT.read();
      Serial.print(received);
      data = data+received;
    }
    
    // zapisanie danych do zmiennych
    temperatureC = data.substring(0,5);
    temperature = data.substring(7,12);
    humidity = data.substring(14,19);
    isMotionDetected = data[21] == 't' ? 1 : 0;
  }
//  Serial.println("---");
  // pomijamy kolejne odebrane ramki, aby zawsze czytać tą najnowszą
  while(SerialBT.available()){
    char received = SerialBT.read();
//    Serial.print(received);
  }
  Serial.println();
}
