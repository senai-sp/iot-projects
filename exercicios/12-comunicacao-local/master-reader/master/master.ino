#include <Wire.h>

void setup() {
  // Ingressar no bus como Master
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // Pedir 6 bytes do slave de endereço 8
  Wire.requestFrom(8, 6);

  // O slave pode não enviar todos os bytes requisitados
  // Então lemos os dados em um loop ao invés de assumir o tamanho
  while (Wire.available()) {
    // ler o byte como char
    char c = Wire.read();
    Serial.print(c);
  }

  delay(500);
}
