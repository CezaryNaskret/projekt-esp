void setup() {
   //Ustawiamy prędkość dla monitora szeregowego
  Serial.begin(115200);
  
  setupDisplay();
  setupBT();
  setupWiFi();
  setupMQTT();
}

void loop() {
  loopBT();
//  serialPrintTHM();
  displayPrintTHM();
  loopWiFi();
  loopMQTT();
  delay(1000); // czekamy 1 sekund
}
