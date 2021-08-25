int stop = 0;

void setup() {
  setupTemperature();
  setupHumidity();
  setupMove();
  setupDisplay();
  
  //Ustawiamy prędkość dla monitora szeregowego
  Serial.begin(115200);

  // wczytanie początkowych wartości
  loopTemperature();
  loopHumidity();
  loopMove();

  setupWiFi();
}

void loop() {
  loopMove(); // sprawdzenie czujnika ruchu
  if(stop >= 10){
    stop = 0;
    
    loopTemperature(); // wypisanie temperatury
    loopHumidity(); // wypisanie wilgotności
    serialPrintTHM(); // wypisanie danych z czujników na porcie szeregowym co 5 sek
  }
  displayPrintTHM(); // wypisanie danych z czujników na monitorze (i obsługa diody LED) co 0.5 sek

  stop++;
  delay(500); // czekamy 5 sekund
}
