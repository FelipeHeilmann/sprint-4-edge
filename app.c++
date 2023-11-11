#include <WiFi.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <PubSubClient.h>

const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = ""; 

const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "Felipe_mqtt";
const char *TOPIC_PUBLISH_TEMP_HUMI = "FIAP/SPRINT/TempHumi";
const char *TOPIC_PUBLISH_LDR = "FIAP/SPRINT/LDR";

#define PUBLISH_DELAY 2000
#define LDR_PIN 33
#define PIN_DHT 12
#define DHTTYPE DHT11
DHT dht(PIN_DHT, DHTTYPE);

WiFiClient espClient;
PubSubClient MQTT(espClient);
unsigned long publishUpdate = 0;
const int TAMANHO = 200;
long duration;

void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();

void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  String msg = String((char*)payload).substring(0, length);
  
  Serial.printf("Mensagem recebida via MQTT: %s do tópico: %s\n", msg.c_str(), topic);
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      //entrar no mqtt
      
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void)
{
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi conectado com sucesso");
  Serial.print(SSID);
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  dht.begin();
  initWiFi();
  initMQTT();
}

void loop() {

    float temp = dht.readTemperature();
  
    float humi = dht.readHumidity();

    int analogValue = analogRead(LDR_PIN);
    checkWiFIAndMQTT();
    MQTT.loop();

  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();

    if (!isnan(temp) && !isnan(humi)) {
      StaticJsonDocument<TAMANHO> doc_humidity;
      doc_humidity["humidity"] = humi;
      char buffer_humidity[TAMANHO];
      serializeJson(doc_humidity, buffer_humidity);
      MQTT.publish(TOPIC_PUBLISH_TEMP_HUMI, buffer_humidity);
      Serial.println(buffer_humidity);

      StaticJsonDocument<TAMANHO> doc_temperature;
      doc_temperature["temperature"] = temp;
      char buffer_temperature[TAMANHO];
      serializeJson(doc_temperature, buffer_temperature);
      MQTT.publish(TOPIC_PUBLISH_TEMP_HUMI, buffer_temperature);
      Serial.println(buffer_temperature);

      StaticJsonDocument<TAMANHO> doc_ldr;
      doc_ldr["pollutants"] = analogValue;
      char buffer_pollutants[TAMANHO];
      serializeJson(doc_ldr, buffer_pollutants);
      MQTT.publish(TOPIC_PUBLISH_LDR, buffer_pollutants);
      Serial.println(buffer_pollutants);
    }
  }
}
