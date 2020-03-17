#include <WiFi.h>
#include <PubSubClient.h>
#include "MQSensor.h"
#include "MGSensor.h"
#define CH4 (0)
#define CO (1)
#define LPG (2)

const char* ssid = "HOME-49EF";
const char* pass = "6AC42223F624C156";
const char* user = "dadeanjuca";
const char* PubTopic = "channels/1021742/publish/1Z1HKPZSFC0QTCF4";
const unsigned int WriteInterval = 6000;
//AskSensors MQTT config
const char* mqtt_server = "mqtt.thingspeak.com";
unsigned int mqtt_port = 1883;
WiFiClient askClient;
PubSubClient client(askClient);

mqsensor mq_co(36,CH4);
mqsensor mq_ch4(36,CO);
mqsensor mq_lpg(36,LPG);
mgsensor CO2(4);
float Ro;
float co;
float ch4;
float lpg;
float co2;

void setup() {

   Serial.begin(115200); 
  
  Serial.print("Calibrating...\n");
  Ro = mq_ch4.MQCalibration();
  Serial.print("Calibracion completa...\n");
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.println("kohm");
  Serial.println("--------------------------------------------------------------------------------------------");
  Serial.print("\n\n");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  } 
}


void loop() {

  if (!client.connected()) 
  reconnect();
  client.loop();

  ch4 = mq_ch4.MQGetGasPercentage(Ro);
  co = mq_co.MQGetGasPercentage(Ro);
  lpg = mq_lpg.MQGetGasPercentage(Ro);
  co2 = CO2.MGGetPercentage();
  char mqtt_payload[100] = "";
  snprintf (mqtt_payload, 100, "field1=%f&field2=%f&field3=%f&field4=%f",ch4,co,lpg,co2);
  client.publish(PubTopic, mqtt_payload);
 
  
  Serial.println("----------------------------------------------------------------------------------------------");
  Serial.print("CH4: ");
  Serial.print(ch4);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  Serial.print("CO: ");
  Serial.print(co);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  Serial.print("LPG: ");
  Serial.print(lpg);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.print(" ppm ");
  Serial.print("\n\n");
  delay (WriteInterval);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("********** Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", user, "")) {  
      Serial.println("-> MQTT client connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("-> try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
