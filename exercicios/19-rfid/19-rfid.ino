#include <UIPEthernet.h>
#include <RestClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x52 };

EthernetClient internet;
RestClient client("192.168.2.185", 3000, internet);

#include <SoftwareSerial.h>

#define TAMANHO_CARTAO 12

bool estavaLendoCartao = false;
bool lendoCartao = false;
char cartao[TAMANHO_CARTAO] = {};
int idxCartao = 0;

// conectar RX com TX do RFID,
// pino TX da SoftwareSerial não é utilizado
SoftwareSerial portaRFID(2, 3); // RX, TX
void setup() {
  Serial.begin(9600);
  portaRFID.begin(9600);

  Serial.println("Inicio");

  // inicializar ethernet
  if(Ethernet.begin(mac)) {
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println(F("Ethernet falhou!"));
  }
}

void loop() {
  // enquanto houver algum caractere vindo do RFID
  while(portaRFID.available()) {
    // após ler 12 caracteres, parar e resetar indice
    if(idxCartao == TAMANHO_CARTAO) {
      lendoCartao = false;
      idxCartao = 0;
    }
    
    char c = portaRFID.read();
    if(c == 2) {
      lendoCartao = true;
    } else if (lendoCartao) {
      cartao[idxCartao] = c;
      idxCartao++;
    }
  }
  
  if(estavaLendoCartao && !lendoCartao) {
    // verificar se o cartao lido é o correto
    if(devoAbrirPortao()) {
      // abrir/fechar servo (toggle)
      Serial.println("Abrir portao");
    } else {
      // tocar buzzer
      Serial.println("Não abrir portao");
    }
  }
  
  estavaLendoCartao = lendoCartao;
}

bool devoAbrirPortao() {
  // return comparar(cartao, cartaoCorreto, TAMANHO_CARTAO);
  String endpoint = "/usuario/";
  endpoint += cartao;
  int status = client.get(endpoint.c_str(), NULL, 0);
  Serial.print(F("Status GET:"));
  Serial.println(status);

  // o usuario pode entrar se foi encontrado na API
  return status == 200;
}

// Funcao que retorna se 2 arrays de chars são iguais
bool comparar(char *um, char *outro, int tamanho) {
  // percorrer caractere a caractere
  for(int i = 0; i < tamanho; i++) {
    // se algum for diferente
    if(um[i] != outro[i]) {
      // as duas 'strings' são diferentes
      return false;
    }
  }
  // senão são iguais
  return true;
}

