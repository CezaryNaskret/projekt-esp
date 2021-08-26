// Zamienień na&nbsp;własne dane WiFi
const char* ssid = "Microlink.pl";
const char* password = "natalka1234";

// Stworzenie obiektu AsyncWebServer na&nbsp;porcie 80
AsyncWebServer server(80);

// Wygląd HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.5rem; }
    .ds-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Serwer ESP</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
    <span class="ds-labels">Temperatura: </span>
    <span id="temperaturec">%TEMPERATUREC%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-thermometer-three-quarters" style="color:#059e8a;"></i>
    <span class="ds-labels">Temperatura: </span>
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#059e8a;"></i>
    <span class="ds-labels">Wilgotnosc: </span>
    <span id="humidity"%HUMIDITY%></span>
    <sup class="units">&percnt;</sup>
  </p>
  <p>
    <i class="fas fa-walking" style="color:#059e8a;"></i>
    <span class="ds-labels">Wykryto ruch: </span>
    <span id="motion">%MOTION%</span>
  </p>
</body>
<script>

document.getElementById("temperature").innerHTML = (%TEMPERATURE%).toFixed(2);
document.getElementById("humidity").innerHTML = (%HUMIDITY%).toFixed(2);
document.getElementById("motion").innerHTML = "%MOTION%";

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperaturec").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperaturec", true);
  xhttp.send();
}, 10000) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("motion").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/motion", true);
  xhttp.send();
}, 1000 ) ;
</script>
</html>)rawliteral";

// Zastępuje placeholder wartościami DHT
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATUREC"){
    return String(temperatureC);
  }
  else if(var == "TEMPERATURE"){
    return String(temperature);
  }
  else if(var == "HUMIDITY"){
    return String(humidity);
  }
  else if(var == "MOTION"){
    if(isMotionDetected==1)return "tak";
    else return "nie";
  }
  return String();
}

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
