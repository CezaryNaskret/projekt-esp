// dane WiFi
//const char* ssid     = "Gott ist tot";
//const char* password = "8607jT:6";
const char* ssid = "Microlink.pl";
const char* password = "natalka1234";
const char* serverName = "http://esp32-naskret-cezary.ugu.pl/post-data.php"; // domena ze ściażką URL
String apiKeyValue = "tPmAT5Ab3j7F9"; // API key 

// Stworzenie obiektu AsyncWebServer na porcie 80
AsyncWebServer server(80);

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("łączenie z WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Wyświetlanie lokalnego adresu IP ESP
  Serial.println(WiFi.localIP());

  // Przekierowanie do&nbsp;strony root / web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperaturec", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(temperatureC).c_str());
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(temperature).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", String(humidity).c_str());
  });
  server.on("/motion", HTTP_GET, [](AsyncWebServerRequest *request){
    String result = isMotionDetected == 1 ? "tak" : "nie";
    request->send_P(200, "text/plain", (result).c_str());
  });
  // Start server
  server.begin();
}

void loopWiFi() {
  // jeśli mamy połączenie WiFi
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, serverName); // rozpoczęcie zapytania
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // nadanie nagłówka
    
    // przygotowanie zapytania HTTP 
    String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + temperatureC
                           + "&value2=" + temperature + "&value3=" + humidity + "";

    http.POST(httpRequestData); // wysłanie zapytania
    http.end(); // zwolnienie zasobów
  }

  // jeśli brak połączenia
  else {
    Serial.println("WiFi Disconnected");
  }
}
