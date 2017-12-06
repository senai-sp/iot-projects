#include <Wire.h>
void setup() {
  // Ingressar no bus como Master
  Wire.begin();
}

byte x = 0;

// A função loop neste exemplo irá transmitir um contador incrementado a cada
// meio segundo
void loop() {
  // Transmitir para slave com endereço 8
  Wire.beginTransmission(8);

  // Envia os 5 bytes da mensagem
  Wire.write("x eh ");

  char numeroX[10];

  // transformar x em char[] e transmitir
  sprintf(numeroX, "%d", x);
  Wire.write(numeroX);
  // finaliza a transmissão
  Wire.endTransmission();

  x++;
  delay(500);
}
