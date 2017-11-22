#ifdef ONLINE
#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>
EthernetClient ethClient;
// Atualizar ultimo valor para ID do seu Kit para evitar duplicatas
const byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };

IPAddress SERVIDOR_MQTT(192, 168, 3, 110);
const int PORTA_MQTT = 1883;
#else
#include <SerialPubSubClient.h>
#endif

const char* TOPICO_STATUS_LUZ = "led";
const char* TOPICO_COMANDO_LUZ = "led/set";

const char* TOPICO_STATUS_PORTAO = "gate";
const char* TOPICO_COMANDO_PORTAO = "gate/set";

const int DISPOSITIVO_PORTAO = 0;
const int DISPOSITIVO_LUZ = 1;

void aoChegarMensagem(char* topic, byte* payload, unsigned int length) {
	// hack para converter rapidamente primeiro caractere de payload para inteiro
  int payloadInt = payload[0] - '0';
  String topicStr = String(topic);
  feedbackChegadaMqtt();

  if(topicStr == TOPICO_COMANDO_LUZ) {
    setLuz(payloadInt);
  }
  if (topicStr == TOPICO_COMANDO_PORTAO) {
    setPortao(payloadInt);
  }
}

#ifdef ONLINE
PubSubClient client(SERVIDOR_MQTT, PORTA_MQTT, aoChegarMensagem, ethClient);
#else
PubSubClient client(aoChegarMensagem);
#endif

#include <Servo.h>

const int PINO_LED = 2;
const int PINO_SERVO = 3;
Servo servo;
const int PINO_BUZZER = 4;

const int PINO_BTN_LUZ = 6;
const int PINO_BTN_PORTAO = 7;

int lightState = 0;
int gateState = 0;

void setLuz(int state) {
  if (state) {
    digitalWrite(PINO_LED, HIGH);
  } else {
    digitalWrite(PINO_LED, LOW);
  }
  lightState = state;
  mqttUpdate(DISPOSITIVO_LUZ, state);
}

void setPortao(int state) {
  if (state) {
    servo.write(80);
    delay(1000);
  } else {
    servo.write(0);
    delay(1000);
  }
  gateState = state;
  mqttUpdate(DISPOSITIVO_PORTAO, state);
  setLuz(gateState);
}

void togglePortao() {
  setPortao(!gateState);
}

void toggleLuz() {
  setLuz(!lightState);
}

const int TONE_DURATION = 150;
void feedbackSaidaMqtt() {
  tone(PINO_BUZZER, 1047, TONE_DURATION);
  delay(TONE_DURATION);
}

void feedbackChegadaMqtt() {
  tone(PINO_BUZZER, 131, TONE_DURATION);
  delay(TONE_DURATION);
}

void mqttUpdate(int device, int state) {
  const char* topic;
  const char* payload;
  if(state) {
    payload = "1";
  } else {
    payload = "0";
  }
  switch (device) {
    case DISPOSITIVO_PORTAO:
      topic = TOPICO_STATUS_PORTAO;
      break;
    case DISPOSITIVO_LUZ:
      topic = TOPICO_STATUS_LUZ;
      break;
  }
  feedbackSaidaMqtt();
  client.publish(topic, payload);
}

int btnLightStatus = 0;
int btnGateStatus = 0;

void atualizarBtnPortao() {
  int status = digitalRead(PINO_BTN_PORTAO);
  if (status && !btnGateStatus) {
    togglePortao();
  }
  btnGateStatus = status;
}

void atualizarBtnLuz() {
  int status = digitalRead(PINO_BTN_LUZ);
  if (status && !btnLightStatus) {
    toggleLuz();
  }
  btnLightStatus = status;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  servo.attach(PINO_SERVO);

  #ifdef ONLINE
  if (!Ethernet.begin(mac)) {
    Serial.println("DHCP Failed");
  } else {
    Serial.println(Ethernet.localIP());
  }
  #endif

  Serial.println("Connecting...");
  const char* clientId = "arduino-42";

  if (client.connect(clientId)) {
    Serial.println("Connected");
    // Se inscreve nos tópicos para que mensagens futuras possam ser
    // processadas através da função de aoChegarMensagem
    client.subscribe(TOPICO_COMANDO_LUZ);
    client.subscribe(TOPICO_COMANDO_PORTAO);
  } else {
    Serial.println("Failed to connect to MQTT server");
  }
}

void loop()
{
  client.loop();

  atualizarBtnPortao();
  atualizarBtnLuz();
}
