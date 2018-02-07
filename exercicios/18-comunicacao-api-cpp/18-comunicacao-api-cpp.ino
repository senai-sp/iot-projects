// Baixar a biblioteca RestClient de
// https://github.com/paolobueno/arduino-restclient Colocar na pasta
// ~/Documentos/Arduino/libraries/
#include <RestClient.h>
#include <UIPEthernet.h>
#include <Ultrasonic.h>
#include <EEPROM.h>

// Alterar o último valor para o id do seu kit
const byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x52};
EthernetClient ethclient;

// Classe para manipular o componeente de ultrassom.
// Recebe como parametro as portas de (Trig, Echo)
Ultrasonic ultrasonic(6, 5);

#define CONTENT_TYPE "application/json"
#define SERVER "192.168.2.185"
#define ENDPOINT "/api/Sensor"

#define TAMANHO_RESPOSTA 25
#define OFFSET_RESPOSTA 10

RestClient client = RestClient(SERVER, 8080, ethclient);


#define TAMANHO_ID 4

// Utilizamos uma array de 5 chars para ter um espaço extra para finalizar a
// string. Ex.: para um ID "1234", a array deve ficar com o valor
// {'1,'2','3','4',NULL} https://en.wikipedia.org/wiki/Null-terminated_string
char id[TAMANHO_ID + 1] = {};

// Para resetar o arduino via software, podemos chamar como função o endereço de
// memória 0
void (*reset)() = 0;

void setupEthernet() {
  // Connect via DHCP
  if (Ethernet.begin(mac)) {
    Serial.println(F("Conectado via DHCP"));
    Serial.print(F("IP recebido:"));
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println(F("DHCP falhou!"));
  }
  preencherId();
}

void preencherId() {
  // se houver um valor non-0 no início da EEPROM...
  if (EEPROM.read(0)) {
    // assumimos que é nosso id e lemos
    for (int i = 0; i < TAMANHO_ID; i++) {
      id[i] = EEPROM.read(i);
    }
    Serial.print(F("Id lido da EEPROM:"));
    Serial.println(id);
  } else {
    // senão o obtemos via POST

    // Array com 25 bytes para armazenar o retorno da api
    char resposta[TAMANHO_RESPOSTA] = {};

    // Obter id via POST /api/Sensor
    int status =
        client.post(ENDPOINT,
                    // Enviamos um objeto JSON vazio para honrar o Content-Type
                    // 'application-json'
                    "{}",
                    // Para ignorar o resultdo podemos passar um pointer para
                    // NULL tamanho 0:
                    resposta,
                    // Passamos também o tamanho da array
                    TAMANHO_RESPOSTA);

    if (status != 200) {
      reset();
    }

    for (int i = 0; i < TAMANHO_ID; i++) {
      id[i] = resposta[OFFSET_RESPOSTA + i];
    }

    Serial.print(F("Status POST: "));
    Serial.println(status);

    Serial.print(F("Id obtido POST: "));
    Serial.println(id);
  }
}

void enviarMedicao() {
  // Montando o JSON via concatenação
  String body = "{\"valor\":";
  body += ultrasonic.distanceRead();
  body += "}";

  // Concatenar com ID obtido para montar endpoint
  String endpoint = ENDPOINT;
  endpoint += id;

  // A biblioteca retorna o código de status da requisição HTTP
  int statusCode = client.put(
      endpoint.c_str(),
      // utilizamos o método String#c_str() para obter um *char a partir da
      // classe String do arduino
      // https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/c_str/
      body.c_str(),
      // Para ignorar o resultado podemos passar um pointer para NULL e tamanho
      // 0:
      NULL, 0);

  // int status = client.put(ENDPOINT, body.c_str(), NULL, 0);

  Serial.print(F("Codigo de resposta: "));
  Serial.println(statusCode);
}

void setup() {
  Serial.begin(9600);
  setupEthernet();
  // Precisamos informar que estamos enviando dados no formato JSON
  // https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Type
  client.setContentType(CONTENT_TYPE);
}

void loop() {
  enviarMedicao();
  delay(1000);
}
