void setup() {
   //Ustawiamy prędkość dla monitora szeregowego
  Serial.begin(115200);
  
  setupDisplay();
  setupBT();
  setupWiFi();
}

void loop() {
  loopBT();
  serialPrintTHM();
  displayPrintTHM();
  delay(1000); // czekamy 5 sekund
}
