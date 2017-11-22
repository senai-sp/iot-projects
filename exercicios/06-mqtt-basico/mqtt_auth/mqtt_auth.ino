#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

// Atualizar ultimo valor para ID do seu Kit para evitar duplicatas
const byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x42 };

// Endereço do Cloud MQTT
const char* server = "test.mosquitto.org";
// Para apontar para um ip:
// const IPAddress server(192, 168, 3, 110);

// Valor da porta do servidor MQTT
// 1883 é o valor padrão para este serviço
const int port = 1883;

const int LED_PIN = 2;

// Esta função será chamada quando o cliente receber uma mensagem em algum tópico em que ele está inscrito
void whenMessageReceived(char* topic, byte* payload, unsigned int length) {
  // Converter pointer do tipo `byte` para typo `char`
  char* payloadAsChar = payload;
  // Workaround para pequeno bug na biblioteca
  payloadAcChar[length] = 0;
  // Converter em tipo String para conveniência
  String msg = String(payloadAsChar);
  // https://www.arduino.cc/en/Reference/StringToInt
  int msgComoNumero = msg.toInt();
  
  
  Serial.print("Topic received: "); Serial.println(topic);
  Serial.print("Message: "); Serial.println(msg);

  // Dentro do callback da biblioteca MQTT, 
  // devemos usar Serial.flush() para garantir que as mensagens serão enviadas
  Serial.flush();

  Serial.print("Numero recebido: "); Serial.println(msgComoNumero);
  Serial.flush();
  
  turnLed(msgComoNumero);
}

void turnLed(int state) {
  if (state) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
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
  // Este ID deve ser unico para cada cliente (cada arduino, celular, etc)
  char* clientId = "arduino-42";
  
  // Conectando com informações de cliente e senha criados através da interface web do serviço
  char* username = "arduino";
  char* password = "123";
  
  if (client.connect(clientId, username, password)) {
    Serial.println("Connected");
    
    // Envia uma mensagem para o tópico 'temperatura'
    // https://pubsubclient.knolleary.net/api.html#publish1
    client.publish("temperatura", 23);
    Serial.println("temperatura enviada");
    
    // Se inscreve nos tópicos para que mensagens futuras possam ser
    // processadas através da função de callback
    client.subscribe("lampada");
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
