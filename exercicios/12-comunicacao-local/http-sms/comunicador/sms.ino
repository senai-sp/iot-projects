#include <ArduinoHttpClient.h>
#include <UIPEthernet.h>

// Alterar o último valor para o id do seu kit
const byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x52};
EthernetClient ethclient;

HttpClient client = HttpClient(ethclient, "192.168.3.186", 3000);

#define SMS_TWILIO_SID "TWILIO_SID"
#define SMS_TWILIO_TOKEN "TWILIO_TOKEN"
#define SMS_PHONE_TO "1234567890"
#define SMS_PHONE_FROM "1234567890"
#define SMS_MESSAGE "Mensagem Legal"

#define CONTENT_TYPE "application/x-www-form-urlencoded"

#define PARAMETROS                                                     \
  "sid=" SMS_TWILIO_SID "&token=" SMS_TWILIO_TOKEN "&to=" SMS_PHONE_TO \
  "&from=" SMS_PHONE_FROM "&body=" SMS_MESSAGE

#define RESPONSE_SIZE 60
char response[RESPONSE_SIZE] = {};

void setupEthernet() {
  // Connect via DHCP
  if (Ethernet.begin(mac)) {
    Serial.println("Conectado via DHCP");
    Serial.print("IP recebido:");
    Serial.println(Ethernet.localIP());
  }
}

void enviarSMS() {
  client.post("/sms", F(CONTENT_TYPE), F(PARAMETROS));

  int statusCode = client.responseStatusCode();
  Serial.print("Status da resposta: ");
  Serial.println(statusCode);

  String response = client.responseBody();
  Serial.print("Resposta do servidor: ");
  Serial.println(response);
}
