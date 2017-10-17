/*
  Basic MQTT example with Authentication

  - connects to an MQTT server, providing username
    and password
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };
char* server = "m13.cloudmqtt.com";
int port = 10141;

void callback(char* topic, byte* payload, unsigned int length) {
  char* payloadAsChar = payload;
  String msg = String(payloadAsChar);
  Serial.print("Topic received: "); Serial.println(topic);
  Serial.print("Message: "); Serial.println(msg);
  Serial.flush();

  int msgComoNumero = msg.toInt();

  Serial.print("Numero lido: "); Serial.println(msgComoNumero);
  Serial.flush();
}

EthernetClient ethClient;
PubSubClient client(server, port, callback, ethClient);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  if (!Ethernet.begin(mac)) {
    Serial.println("DHCP Failed");
  } else {
    Serial.println(Ethernet.localIP());
  }

  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this,
  // you will need to increase the value of MQTT_MAX_PACKET_SIZE in
  // PubSubClient.h

  Serial.println("Connecting...");
  if (client.connect("arduinoClient", "arduino", "123")) {
    Serial.println("Connected");
    client.publish("outTopic", "hello world");
    Serial.println("outTopic sent");
    client.subscribe("inTopic");
  } else {
    Serial.println("Failed to connect to MQTT server");
  }
}

void loop()
{
  client.loop();
}
