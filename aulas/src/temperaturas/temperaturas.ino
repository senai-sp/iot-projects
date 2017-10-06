const int red = 13;
const int yellow = 12;
const int green = 11;
const int buzzer = 5;

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
  // Serial.write("Inicio\n");
}

void processarTemperatura(int temperatura) {
  if(temperatura < 30) {
    ligarSomente(green);
    tocarSom(4186);
    Serial.println("Temperatura normal");
  } else if (temperatura < 40) {
    ligarSomente(yellow);
    tocarSom(523);
    Serial.println("Temperatura perigosa");
  } else {
    ligarSomente(red);
    tocarSom(131);
    Serial.println("Temperatura critica");
  }
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

// Veja https://www.arduino.cc/en/Tutorial/ToneMelody para uma lista de valores para notas musicais
void tocarSom(int tom) {
  const int duracao = 500;
  tone(buzzer, tom, duracao);
}

void loop()
{
  // verificar se há algo a ler
  if(Serial.available() > 0) {
  	// ler "temperatura"
    int temp = Serial.parseInt();
  	processarTemperatura(temp);
  }
}
