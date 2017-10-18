/*
  Exercício de envio de temperaturas
  Nova mudança
*/

#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>

// # Estas constantes representam os estados possíveis do arduino,
// vamos programá-lo para que em cada estado ele execute uma ação diferente,
// e esta ação se encarrega de trocar para o próximo estado.
// trata-se de uma implementação básica de https://pt.wikipedia.org/wiki/State
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

// IP estático para este arduino caso o DHCP falhe
IPAddress ip(192, 168, 3, 177);

// IP do servidor
// TODO: mudar para valor real
IPAddress server(192, 168, 3, 110);

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
    Serial.print("IP address granted: ");
    Serial.println(Ethernet.localIP());
  }
  // Esperar 1s para término da inicialização da placa Ethernet
  delay(1000);
}

void loop() {
  // Ler a temperatura
  int temperatureRead;
  float temperatureCelcius;
  // Estrutura de decisão com possibilidade de vários caminhos em cima de um único valor
  // também pode ser implementado através de `if`s
  // https://www.arduino.cc/en/Reference/SwitchCase
  switch(state) {
    case STATE_REQUEST:
      temperatureRead = analogRead(LM35_PIN);
      temperatureCelcius = map(temperatureRead, 0, 1023, 0, 5000) / 10.0;
      Serial.println("Connecting to server...");
      if (client.connect(server, 8080)) {
        // Montar os dados a serem enviados
        String json = "{\"temp\":" + String(temperatureCelcius) + ",\"id\":42}";
        
        Serial.println("Connection successful");
        
        // Construindo a mensagem HTTP POST
        // https://github.com/senai-sp/iot-projects/blob/master/aulas/05-ethernet-temperatura.md#formato-da-mensagem-http-post
        // Postamos para a raiz do servidor ('/') conforme documentação do exercício
        client.println("POST / HTTP/1.1");
        
        // O cabeçalho Host especifica o 'nome' do servidor que queremos acessar
        // Este valor deve ser alterado para o valor do IP do servidor
        client.print("Host: "); client.print(server); client.println(":8080");
    
        // O cabeçalho Content-Type especifica o tipo de conteúdo de nossa mensagem,
        // neste caso é um texto no formato JSON
        // outros valores possíveis seriam:
        // text/plain: texto qualquer
        // text/html: página HTML
        // etc.
        client.println("Content-Type: application/json");
        // esses valores são chamados de mime types:
        // https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Basico_sobre_HTTP/MIME_types

        // Content-Length deve conter o tamanho do conteúdo da mensagem em bytes,
        // por sorte cada caracter ASCII tem 1 byte, então podemos utilizar String::length()
        client.print("Content-Length: "); client.println(json.length());
    
        // Este cabeçalho especifica que o servidor deve terminar a conexão após a troca de mensagens
        client.println("Connection: close");
    
        // Esta linha em branco separa os headers do conteúdo da mensagem HTTP,
        // sem ela o formato está inválido
        client.println();

        client.println(json);
    
        // O método flush() força o envio de todo o texto acima através da placa Ethernet
        // caso não o utilizemos, é possível que nossa mensagem fique 'presa' na memória da própria placa
        // e não seja enviada
        client.flush();
        
        state = STATE_RESPONSE;
      } else {
        Serial.println("Connection failed!");
        state = STATE_WAIT;
      }
      break;
    case STATE_RESPONSE:
      // verificar se há caracteres disponíveis na resposta do servidor
      if(client.available()) {
        // ler a reposta até não haver mais caracteres disponíveis
        while(client.available()) {
          char c = client.read();
          Serial.print(c);
        }
      } else {
        // tentar novamente até receber a resposta
        // esta linha não é necessária devido a `state` já ser igual a STATE_RESPONSE,
        // mas torna a intenção explícita
        state = STATE_RESPONSE;
      }
      // Se o servidor desconectar (conforme pedimos pelo header Connection, do HTTP)
      // paramos o cliente e vamos para o modod de espera, para pausar o arduino até o próximo envio de temperatura
      if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
        state = STATE_WAIT;
      }
      break;
    case STATE_WAIT:
      Serial.println("Waiting for " + String(REQUEST_INTERVAL) + "ms");
      delay(REQUEST_INTERVAL);
      // após a espera, voltamos para o modo de envio de temperatura
      state = STATE_REQUEST;
      break;
  }
}
