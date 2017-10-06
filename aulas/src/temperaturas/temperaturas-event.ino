/*
  Esta versão utiliza a função serialEvent() para rodar o código de leitura somente
  quando há alguma alteração nos dados da porta Serial,
  isso evita a checagem dentro de loop()
*/
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
  
  while(!Serial) {
  }
  Serial.println("Inicio");
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
  for(int i = 11; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
  digitalWrite(pino, HIGH);
}

void tocarSom(int tom) {
  const int duracao = 5;
  tone(buzzer, tom, duracao);
}

// https://www.arduino.cc/en/Reference/SerialEvent
void serialEvent() {
  int temp = Serial.parseInt();
  processarTemperatura(temp);
}

void loop()
{
}