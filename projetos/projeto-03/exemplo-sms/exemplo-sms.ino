#include <UIPEthernet.h>
#include <RestClient.h>

// Alterar o último valor para o id do seu kit
const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x52 };
EthernetClient ethclient;

RestClient client = RestClient("192.168.3.122", 3000, ethclient);
String sid = "SEU_SID";
String token = "SEU_TOKEN";
String to = "1234567980";
String from = "1234567980";

String response = "";

//Setup
void setup() {
	Serial.begin(9600);
	// Connect via DHCP
	if(Ethernet.begin(mac)) {
		Serial.println("Conectado via DHCP");
		Serial.print("IP recebido:"); Serial.println(Ethernet.localIP());
	}

	String parametros = "sid=" + sid +
	"token=" + token +
	"to=" + to
	"from=" + from +
	"body=Mensagem Legal";

	int statusCode = client.post("/sms", parametros.c_str(), &response);
	Serial.print("Status da resposta: ");
	Serial.println(statusCode);
	Serial.print("Resposta do servidor: ");
	Serial.println(response);
	delay(1000);
}

void loop(){

}
