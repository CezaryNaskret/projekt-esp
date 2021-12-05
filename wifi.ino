const char* serverName = "http://esp32-naskret-cezary.ugu.pl/post-data.php"; // domain with URL path
String apiKeyValue = "tPmAT5Ab3j7F9"; // API key 

// create an AsyncWebServer object on port 80
AsyncWebServer server(80);

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("łączenie z WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // ESP local IP address display
  Serial.println(WiFi.localIP());

  // redirection to the root / web page
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
  // if we have a WiFi connection
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, serverName); // starting the request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // creating a header
    
    // preparing an HTTP request
    String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + temperatureC
                           + "&value2=" + temperature + "&value3=" + humidity + "";

    http.POST(httpRequestData); // sending request
    http.end(); // release of resources
  }

  // if no connection
  else {
    Serial.println("WiFi Disconnected");
  }
}
