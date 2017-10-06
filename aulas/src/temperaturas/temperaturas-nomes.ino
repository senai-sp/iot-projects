const int red = 13;
const int yellow = 12;
const int green = 11;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9500);
  
  // Fazer nada enquanto a porta Serial não está pronta
  while(!Serial) {
  }
  Serial.println("Inicio");
}

void ligarSomente(int pino) {
  /** Desligar todas os leds
  * 
  * A instrução a seguir declara uma variavel to tipo `int`, com nome "i"
  * e roda o bloco correspondente até `i <= 13` ser falso,
  * no final de cada loop o comando `i++` é rodado, aumentando a variável i em 1 unidade
  */
  // `i++` é equivalente a `i = i + 1`;
  for(int i = 11; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
  // Ligar luz correta
  digitalWrite(pino, HIGH);
}

void loop()
{
  // verificar se há algo a ler
  if(Serial.available() > 0) {
    // ler nome da cor
    String cor = Serial.readString('\n');
    if (cor == "vermelho") {
      ligarSomente(red);
    } else if (cor == "amarelo") {
      ligarSomente(yellow);
    } else if (cor == "verde") {
      ligarSomente(green);
    } else {
      Serial.println("Cor não identificada");
    }
  }
}