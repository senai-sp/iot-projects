#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

// Atualizar ultimo valor para ID do seu Kit para evitar duplicatas
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };

// Endereço do Cloud MQTT
char* server = "m13.cloudmqtt.com";

// Valor da porta do servidor MQTT
int port = 10141;

void whenMessageReceived(char* topic, byte* payload, unsigned int length) {
  // Converter pointer do tipo `byte` para typo `char`
  char* payloadAsChar = payload;

  // Converter em tipo String para conveniência
  String msg = String(payloadAsChar);
  Serial.print("Topic received: "); Serial.println(topic);
  Serial.print("Message: "); Serial.println(msg);

  // Dentro do callback da biblioteca MQTT, 
  // devemos usar Serial.flush() para garantir que as mensagens serão enviadas
  Serial.flush();

  int msgComoNumero = msg.toInt();

  Serial.print("Numero lido: "); Serial.println(msgComoNumero);
  Serial.flush();
}

EthernetClient ethClient;
PubSubClient client(server, port, whenMessageReceived, ethClient);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  if (!Ethernet.begin(mac)) {
    Serial.println("DHCP Failed");
  } else {
    Serial.println(Ethernet.localIP());
  }

  Serial.println("Connecting...");
  // Conectando com informações de cliente e senha criados através da interface web do serviço
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
  // A biblioteca PubSubClient precisa que este método seja chamado em cada iteração de `loop()`
  // para manter a conexão MQTT e processar mensagens recebidas (via a função callback)
  client.loop();
}
