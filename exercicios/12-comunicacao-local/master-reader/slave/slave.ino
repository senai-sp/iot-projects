#include <Wire.h>
void setup() {
  // Ingressa no bus como slave com endereço 8
  Wire.begin(8);

  // Registrar callback para ser chamado quando o Master pede dados
  Wire.onRequest(requestEvent);
}

void loop() { delay(100); }

// Esta função será chamada quando o Master requerer dados deste Slave #8
void requestEvent() {
  // Enviar os bytes pedidos pelo Master
  Wire.write("hello!");
}
