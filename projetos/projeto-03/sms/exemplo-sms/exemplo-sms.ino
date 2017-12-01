#include <UIPEthernet.h>
#include <RestClient.h>

// Alterar o último valor para o id do seu kit
const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x52 };
EthernetClient ethclient;

RestClient client = RestClient("192.168.3.41", 3000, ethclient);

#define SMS_TWILIO_SID "TWILIO_SID"
#define SMS_TWILIO_TOKEN "TWILIO_TOKEN"
#define SMS_PHONE_TO "1234567890"
#define SMS_PHONE_FROM "1234567890"
#define SMS_MESSAGE "Mensagem Legal"

const char* parametros = "sid=" SMS_TWILIO_SID "&token=" SMS_TWILIO_TOKEN "&to=" SMS_PHONE_TO "&from=" SMS_PHONE_FROM "&body=" SMS_MESSAGE;

#define RESPONSE_SIZE 30
char response[RESPONSE_SIZE] = {};

void setup() {
	Serial.begin(9600);
	// Connect via DHCP
	if(Ethernet.begin(mac)) {
		Serial.println("Conectado via DHCP");
		Serial.print("IP recebido:"); Serial.println(Ethernet.localIP());
	}

	Serial.println(parametros);
	int statusCode = client.post("/sms", parametros, response, RESPONSE_SIZE);
	Serial.print("Status da resposta: ");
	Serial.println(statusCode);
	Serial.print("Resposta do servidor: ");
	Serial.println(response);
	delay(1000);
}

void loop(){

}
