/*
  Exercício de envio de temperaturas
*/

#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>

// # Estas constantes representam os estados possíveis do arduino,
// vamos programá-lo para que em cada estado ele execute uma ação diferente,
// e esta ação se encarrega de trocar para o próximo estado
const int STATE_REQUEST = 1;
const int STATE_RESPONSE = 2;
const int STATE_WAIT = 3;

const int REQUEST_INTERVAL = 5 * 1000;

const int LM35_PIN = A1;

int state = STATE_REQUEST;

// Endereço MAC para nossa placa de rede Ethernet
// Em sala, substituia o último valor pelo nº do seu Kit
// para garantir que não haja MACs duplicados
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x42 };

// Ip estático para este arduino caso o DHCP falhe
IPAddress ip(192, 168, 0, 177);

EthernetClient client;

void setup() {
  // Abrir comunicação via porta serial
  Serial.begin(9600);
  while (!Serial) {}

  // Começar conexão Ethernet, com o intuito de receber endereço IP via DHCP
  // https://www.arduino.cc/en/Reference/EthernetBegin
  // https://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP request failed, trying fixed IP");
    Ethernet.begin(mac, ip);
    Serial.println("Fixed IP:" + String(Ethernet.localIP()));
  } else {
    Serial.println("IP address granted:" + String(Ethernet.localIP()));
  }
  // Esperar 1s para término da inicialização da placa Ethernet
  delay(1000);
}

void loop() {
  switch(state) {
    case STATE_REQUEST:
      // Ler a temperatura
      int temperatureRead = analogRead(LM35_PIN);
      float temperatureCelcius = map(leitura, 0, 1023, 0, 5000) / 10.0;
      
      Serial.println("Connecting to server...");
      if (client.connect(server, 80)) {
        Serial.println("Connection successful");
        
        // Construindo a mensagem HTTP POST
        // https://github.com/senai-sp/iot-projects/blob/master/aulas/05-ethernet-temperatura.md#formato-da-mensagem-http-post
        // Postamos para a raiz do servidor ('/') conforme documentação do exercício
        client.println("POST / HTTP/1.1");
        
        // O cabeçalho Host especifica o 'nome' do servidor que queremos acessar
        // Este valor deve ser alterado para o valor do IP do servidor
        client.println("Host: 127.0.0.1");
    
        // O cabeçalho Content-Type especifica o tipo de conteúdo de nossa mensagem,
        // neste caso é uma String no formato JSON
        // outros valores possíveis seriam:
        // text/plain: texto qualquer
        // text/html: página HTML
        // etc.
        client.println("Content-Type: application/json");
        // esses valores são chamados de mime types:
        // https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Basico_sobre_HTTP/MIME_types
    
        // Este cabeçalho especifica que o servidor deve terminar a conexão após a troca de mensagens
        client.println("Connection: close");
    
        // Esta linha em branco separa os headers do conteúdo da mensagem HTTP,
        // sem ela o formato está inválido
        client.println();
    
        client.println("{\"temp\":" + String(temperatureCelcius) + ",\"id\":42}")
    
        // O método flush() força o envio de todo o texto acima através da placa Ethernet
        // caso não o utilizemos, é possível que nossa mensagem fique 'presa' na memória da própria placa
        // e não seja enviada
        client.flush();
        
        // Mudamos para o estado de esperar uma resposta
        state = STATE_RESPONSE;
      } else {
        Serial.println("Connection failed!");
        
        // Desistimos da conexão e vamos para o estado de espera
        state = STATE_WAIT;
      }
      break;
    case STATE_RESPONSE:
      if (client.available()) {
        Serial.print(client.read());
        // Continuar neste modo para obter mais caracteres de resposta
        state = STATE_RESPONSE;
      } else if (!client.connected()) {
        // Se o servidor desconectou, parar cliente e entrar em modo de espera
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
        state = STATE_WAIT;
      }
      break;
    case STATE_WAIT:
      delay(REQUEST_INTERVAL);
      break;
  }
}

