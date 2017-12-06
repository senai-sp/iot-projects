/**
 * Esta unidade é o 'comunicador', que está conectado à internet atraves de cabo
 * ethernet. Ela recebe da outra unidade pedidos para envio da requisição HTTP
 * que causa o envio de SMS
 *
 * Atua como Slave no protocolo I2C
 */
#include <Wire.h>

// Mensagem que significa um pedido de envio de SMS
// Definimos a mesma constante em ambos os programas de modo que ela tenha o
// mesmo sentido
#define MENSAGEM_ENVIO_SMS 1

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);

  // definido em sms.ino
  setupEthernet();
}

void loop() {}

// Esta função será chamada quando algum dado vier do Master
// length significa a quantidade de bytes vindo do bus
void receiveEvent(int length) {
  while (Wire.available()) {
    // Ler mensagem de tamanho 1 byte
    byte c = Wire.read();

    // Verificar qual tipo de mensagem é e executar ação correspondente
    switch (c) {
      case MENSAGEM_ENVIO_SMS:
        enviarSMS();
        break;
      default:
        Serial.print(F("Mensagem desconhecida via I2C:"));
        Serial.print(c);
    }
  }
}
