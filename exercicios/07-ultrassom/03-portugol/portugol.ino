// Inclusão da biblioteca do sensor
// Essa biblioteca não vem por padrão com o arduino e 
// precisa ser instalada pelo gerenciador de bibliotecas
#include <Ultrasonic.h>

int portaLed = 8;

// Inicializa o objeto do sensor ultrasônico
// Usando as portas 12 e 13 para trigger e echo
Ultrasonic ultrasonic(12, 13);

void setup() {
  // Inicializa a porta Serial
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do sensor
  int distancia = ultrasonic.distanceRead();

  // Escreve o valor da distância no painel Serial
  Serial.print("Distance in CM: ");
  Serial.println(distancia);
  
  delay(1000);

//  SE distancia MENOR QUE 100 E distancia MAIOR QUE 80
//    acender led amarelo
//  SENAO SE distancia MENOR QUE 80 E distancia MAIOR QUE 60
//    acender led vermelho
//  SENAO SE distancia MENOR QUE 60
//    tocar buzzer
//  SENAO 
//    desligar buzzer
//    desligar led vermelho
//    desligar led amarelo
}

// Links para traduzir o código
//
// SE/SENAO = IF/ELSE -> https://www.arduino.cc/en/Reference/Else
// E = && (logical and) -> https://www.arduino.cc/en/Reference/Boolean
