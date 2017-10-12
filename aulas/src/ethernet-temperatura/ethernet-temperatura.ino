/*
  Exercício de envio de temperaturas
*/

#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>

// Endereço MAC para nossa placa de rede Ethernet
// Em sala, substituia o último valor pelo nº do seu Kit
// para garantir que não haja MACs duplicados
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x42 };

//ip estático para este arduino caso o DHCP falhe
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void lerResposta() {
  // caso a resposta do servidor esteja disponível,
  // lê-la caracter por caracter
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
}

void setup() {
  // Abrir comunicação via porta serial
  Serial.begin(9600);
  while (!Serial) {}

  // Começar conexão Ethernet, com o intuito de receber endereço IP via DHCP
  // https://www.arduino.cc/en/Reference/EthernetBegin
  // https://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Falha de resposta DHCP, utilizando IP fixo");
    Ethernet.begin(mac, ip);
    Serial.println("IP fixo utilizado:" + String(Ethernet.localIP()));
  } else {
    Serial.println("Endereço de IP recebido:" + String(Ethernet.localIP()));
  }
  // Esperar 1s para término da inicialização da placa Ethernet
  delay(1000);
}

void loop() {
  Serial.println("Conectando ao servidor...");
  
  // # ENVIO DOS DADOS DE TEMPERATURA
  if (client.connect(server, 80)) {
    Serial.println("Conectado com sucesso");
    
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

    // Esta linha em branco separa os headers do conteúdo da mensagem,
    // sem ela o formato está inválido
    client.println();

    client.println("{\"temp\":25,\"id\":42}")

    // O método flush() força o envio de todo o texto acima através da placa Ethernet
    // caso não o utilizemos, é possível que nossa mensagem fique 'presa' na memória da própria placa
    // e não seja enviada
    client.flush();
  } else {
    Serial.println("Conexão falhou!");
  }

  // ## LEITURA DA RESPOSTA
  while() {
    lerResposta();
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
}

