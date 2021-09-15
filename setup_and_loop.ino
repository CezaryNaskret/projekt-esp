void setup() {
   //Ustawiamy prędkość dla monitora szeregowego
  Serial.begin(115200);
  
  setupDisplay();
  setupBT();
  setupWiFi();
}

void loop() {
  serialPrintTHM();
  loopBT();
  delay(5000); // czekamy 5 sekund
}
