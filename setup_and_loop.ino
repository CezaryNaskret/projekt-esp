void setup() {
  setupBT();
  setupUART();
  setupDisplay();
  setupWiFi();
  setupMQTT();
}

void loop() {
  loopBT();
  loopUART();
  loopDisplay();
  loopWiFi();
  loopMQTT();
  delay(1000);
}
