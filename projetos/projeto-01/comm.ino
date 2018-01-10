#include <PubSubClient.h>
#include <UIPEthernet.h>
EthernetClient ethClient;

const char* TOPICO_LUZ = "luz";
const char* TOPICO_PORTAO = "gate";

const int DISPOSITIVO_PORTAO = 0;
const int DISPOSITIVO_LUZ = 1;

// Atualizar ultimo valor para ID do seu Kit para evitar duplicatas
const byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };
const char* clientId = "arduino-42";

const char* SERVIDOR_MQTT = "test.mosquitto.org";
const int PORTA_MQTT = 1883;
PubSubClient client(SERVIDOR_MQTT, PORTA_MQTT, callback, ethClient);

void ethernetConnect() {
	if (!Ethernet.begin(mac)) {
    Serial.println("DHCP Failed");
  } else {
    Serial.println(Ethernet.localIP());
  }
}

void mqttLoop() {
  client.loop();
}

void mqttSetup() {
  Serial.println(F("Conectando MQTT..."));

  if (client.connect(clientId)) {
    Serial.println(F("Connectado"));
    // Se inscreve nos tópicos para que mensagens futuras possam ser
    // processadas através da função de aoChegarMensagem
    client.subscribe(TOPICO_LUZ);
    client.subscribe(TOPICO_PORTAO);
  } else {
    Serial.println(F("Failed to connect to MQTT server"));
  }
}

void enviarMQTT(int dispositivo, int estado) {
  const char* topic;
  const char* payload;

  // o payload para envio deve ser um char*, então utilizamos um simples if para `converter` o int
  if (estado) {
    payload = "1";
  } else {
    payload = "0";
  }

  // Selecionamos o tópico baseado no tipo de dispositivo requerido
  switch (dispositivo) {
    case DISPOSITIVO_PORTAO:
      topic = TOPICO_PORTAO;
      break;
    case DISPOSITIVO_LUZ:
      topic = TOPICO_LUZ;
      break;
  }
  feedbackSaidaMqtt();
  client.publish(topic, payload, true);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // hack para converter rapidamente primeiro caractere de payload para inteiro
  int payloadInt = payload[0] - '0';
  String topicStr = String(topic);
  feedbackChegadaMqtt();

  if(topicStr == TOPICO_LUZ) {
    setLuz(payloadInt);
  }
  if (topicStr == TOPICO_PORTAO) {
    setPortao(payloadInt);
  }
}
