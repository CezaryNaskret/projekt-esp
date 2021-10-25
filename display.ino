// -------- wyświetlacz

// definiujemy piny ESP, do których podłączony jest wyświetlacz
Adafruit_SH1106 display(21, 22);

void setupDisplay() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
}

void displayPrintTHM() {
  // temperature
  display.setCursor(0, 0);
  display.print("Temperatura: ");
  display.print(temperatureC);
  display.print(" ");
  display.cp437(true);
  display.write(167);
  display.println("C");

  // humidity
  display.print("Temperatura: ");
  display.print(temperature);
  display.print(" ");
  display.cp437(true);
  display.write(167);
  display.println("C");
  display.print("Wilgotnosc:  ");
  display.print(humidity);
  display.println("%");

  // move
  if (isMotionDetected == HIGH)  {
    display.println("Wykryto ruch!");
  }
  else {
    display.println("Nie wykryto ruchu!");
  }
  
  display.display();
  display.clearDisplay();
}

// -------- wypisanie danych z czujników do monitora szeregowego

void serialPrintTHM() {
  // dane z czujnika temperatury
  Serial.print("Zmierzona temperatura: ");
  Serial.print(temperatureC);
  Serial.println("°C");
  
  // dane z czujnika wilgotności
  Serial.print("Zmierzona temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Zmierzona wilgotność:  ");
  Serial.print(humidity);
  Serial.println("%");

  // dane z czujnika ruchu
  if (isMotionDetected == HIGH)
    Serial.println("Wykryto ruch!");

  Serial.println("----------------");
}
