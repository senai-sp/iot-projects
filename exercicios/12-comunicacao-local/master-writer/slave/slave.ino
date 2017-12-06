#include <Wire.h>

void setup() {
  // Inicia comunicação como slave com endereço 8
  Wire.begin(8);
  // Registra callback para ser chamado quando receber mensagem
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
}

void loop() { delay(100); }

// Esta função será chamada quando algum dado vier do Master
// length significa a quantidade de bytes vindo do bus
void receiveEvent(int length) {
  // Enquanto houver algum byte a ser lido
  while (Wire.available()) {
    // Ler único byte como char
    char c = Wire.read();
    Serial.print(c);
  }
}
