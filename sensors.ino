// -------- obsługa czujnika temperatury

OneWire oneWire(4); // komunikujemy, że będziemy korzysać z interfejsu OneWire na pinie 4
DallasTemperature tempSensor (&oneWire); // komunikujemy, że czujnik DS18B20 będzie wykorzystywał interfejs OneWire

void setupTemperature() {
  tempSensor.begin();
}

void loopTemperature() {
  tempSensor.requestTemperatures(); //Odczyt temperatury
  temperatureC = tempSensor.getTempCByIndex(0); //Odczyt w stopniach celsjusza
}

// -------- obsługa czujnika wilgotności
  
DHT dht(18, DHT11); // czujnik typu DHT11 podłączamy do pinu 18

void setupHumidity() {
  dht.begin();
}

void loopHumidity() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

// -------- czujnik ruchu

int inputPin = 2; // pin z którego będziemy odczytywali stan czujnika

void setupMove() {
  pinMode(inputPin, INPUT);  // deklarujemy pin jako INPUT
  pinMode(outputPin, OUTPUT);  // definiujemy pin jako OUTPUT
}

void loopMove() {
  isMotionDetected = digitalRead(inputPin);
}
