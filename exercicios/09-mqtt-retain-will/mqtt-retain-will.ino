#include <SPI.h>
#include <UIPEthernet.h>
#include <PubSubClient.h>

// pino ao qual está conectado nosso LED
const int LED_PIN = 2;

// Atualizar ultimo valor para ID do seu Kit para evitar duplicatas
const byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };

// Informações de conexão mqtt
const char* server = "test.mosquitto.org";
const int port = 1883

// Identificação única do cliente, trocar número pelo id de seu kit
const char* clientId = "arduino-codexp-42";

// tópico mqtt com prefixos para garantir que seja único no servidor que utilizamos
// porque test.mosquitto.org é público
const char* topic = "senai/codexp/42/luz";

void ligarDesligarLED(int ligar) {
	if (ligar) {
		digitalWrite(LED_PIN, HIGH);
	} else {
		digitalWrite(LED_PIN, LOW);
	}
}

void atualizarTopico(int estado) {
	// Este método publica mensagens com a configuração Retain = true,
	// tornando suficiente publicar somente quando a lâmpada de fato muda de estado
	// ao invés de periodicamente
	if (estado) {
		client.publish(topic, "1", true);
	} else {
		client.publish(topic, "0", true);
	}
}

void callback(char* topic, byte* payload, unsigned int length) {
	// Truque para converter rapidamente o valor do primeiro caractere da mensagem
	// para seu valor numérico
	// Isto assume que o primeiro caractere é um dígito [0-9]
	int payloadAsInt = payload[0] - '0';
	ligarDesligarLED(payloadAsInt);
	atualizarTopico(payloadAsInt);
}

EthernetClient ethernetClient;
PubSubClient client(server, port, callback, ethernetClient);

// Função que conecta ao broker mqtt
int mqttConnect() {
	// Conexão do cliente MQTT com configuração de topico Will:
	// A linha seguinte configura o broker mqtt para que publique a seguinte mensagem
	// caso este cliente se desconecte abruptamente:

	// topico: "senai/codexp/42/luz"
	// QoS: 0
	// Retain: true
	// Payload: vazio

	// O payload vazio garante que a última mensagem publicada com Retain = true
	// seja removida da memória do broker
	if(client.connect(clientId, topic, 0, true, "")) {
		client.subscribe(topic);
	}
	return client.connected();
}

void setup() {
	// Inicialização da comunicação serial
	Serial.begin(9600);
	if(client.connect(clientId, topic, 0, true, "")) {
		client.subscribe(topic);
	}
	return client.connected();
}

void setup() {
	// Inicialização da comunicação serial
	Serial.begin(9600);
	while (!Serial) {}

	// Inicialização da placa ethernet
  if (Ethernet.begin(mac)) {
    Serial.print("Endereço IP: ");
    Serial.println(Ethernet.localIP());
	}

	pinMode(LED_PIN, OUTPUT);
	mqttConnect();
}

void loop() {
	if(!client.connected()) {
		mqttConnect();
	}
	client.loop();
}
