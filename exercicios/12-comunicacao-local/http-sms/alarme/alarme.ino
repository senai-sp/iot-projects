/**
 * Esta unidade é a que estaria conectada aos sensores e portanto requer da
 * outra unidade o envio de mensagem SMS
 *
 * Neste exemplo ela atua como Master no protocolo I2C
 */
#include <Wire.h>

// Mensagem que significa um pedido de envio de SMS
// Definimos a mesma constante em ambos os programas de modo que ela tenha o
// mesmo sentido
#define MENSAGEM_ENVIO_SMS 1

void setup() {
  // Ingressar no bus como Master
  Wire.begin();
}

void loop() {
  // Definido em ultrassom.ino
  loopUltrassom();
  delay(500);
}

void requererEnvioSMS() {
  Wire.beginTransmission(8);
  Wire.write(MENSAGEM_ENVIO_SMS);
  Wire.endTransmission();
}
