const char *mqtt_broker = "broker.emqx.io";
const char *topic1 = "alarm/esp32";
const char *topic2 = "alarm/aplikacja1";
const char *topic3 = "alarm/aplikacja2";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}

void setupMQTT() {
  // connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("Klient %s został podłączony do publicznego prokera mqtt\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Połączono do publicznego prokera emqx mqtt");
    } else {
      Serial.print("połączenie nie powiodło się, stan: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  // publish and subscribe
  client.publish(topic1, "Hi EMQ X I'm ESP32 ^^");
  client.subscribe(topic2);
  client.subscribe(topic3);
}

void loopMQTT() {
  String tmp = isMotionDetected == 0 ? "nie" : "tak";
  const char *data = (temperatureC + "°C," + temperature + "°C," + humidity + "%," + tmp).c_str();
  client.publish(topic1, data);
  client.loop();
}
