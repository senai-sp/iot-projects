#include <RestClient.h>
#include <UIPEthernet.h>

// Alterar o último valor para o id do seu kit
const byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x52};
EthernetClient ethclient;

#define CONTENT_TYPE "application/json"
#define SERVER "192.168.2.185"
RestClient client = RestClient(SERVER, 8080, ethclient);

#define PIN_ULTRASSOM 6

void setupEthernet() {
  // Connect via DHCP
  if (Ethernet.begin(mac)) {
    Serial.println("Conectado via DHCP");
    Serial.print("IP recebido:");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println("DHCP falhou!");
  }
}

void enviarMedicao() {
  String body = "{\"valor\":";
  body += analogRead(PIN_ULTRASSOM);
  body += "}";
  Serial.println(body);

	char resposta[100] = {};

  int statusCode = client.put("/api/Sensor/1003", body.c_str(), resposta, 50);

  Serial.print(F("Codigo de resposta: "));
  Serial.println(statusCode);

  Serial.print(F("Texto de resposta: "));
  Serial.println(resposta);
}

void setup() {
  Serial.begin(9600);
	Serial.println("Hello World!");
  setupEthernet();
	client.setContentType(CONTENT_TYPE);
  pinMode(PIN_ULTRASSOM, INPUT);
}

void loop() {
  enviarMedicao();
  delay(5000);
}
