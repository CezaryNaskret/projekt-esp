// -------- OLED display

// define the ESP pins to which the display is connected
Adafruit_SH1106 display(21, 22);

void setupDisplay() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
}

void loopDisplay() {
  // displaying data from the temperature sensor
  display.setCursor(0, 0);
  display.print("Temperatura: ");
  display.print(temperatureC);
  display.print(" ");
  display.cp437(true);
  display.write(167);
  display.println("C");

  // display of data from the humidity sensor
  display.print("Temperatura: ");
  display.print(temperature);
  display.print(" ");
  display.cp437(true);
  display.write(167);
  display.println("C");
  display.print("Wilgotnosc:  ");
  display.print(humidity);
  display.println("%");

  // displaying data from the motion detector
  if (isMotionDetected == HIGH)  {
    display.println("Wykryto ruch!");
  }
  else {
    display.println("Nie wykryto ruchu!");
  }
  
  display.display();
  display.clearDisplay();
}
