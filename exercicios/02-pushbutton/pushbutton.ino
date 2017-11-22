const int btn = 2;

void setup(){
  // Configurar o pino do LED (13) como OUTPUT para o controlarmos digitalmente
  pinMode(LED_BUILTIN, OUTPUT);

  // Configurar o pino btn (2) como INPUT para que possamos ler seu estado
  // esta configuração faz com que o pino fique com uma voltagem baixa,
  // "sugando" corrente para si
  pinMode(btn, INPUT);
}

void loop() {
  // Declarando uma variavel para armazenar a leitura do estado do pushbutton
  // esta variável existe somente dentro desta execução de loop()
  // sendo recriada na próxima execução
  int btnState = digitalRead(btn); 

  // Caso o botão esteja "apertado"
  if (btnState == HIGH) {
    // ligamos o LED
    digitalWrite(LED_BUILTIN, HIGH);
  } else { // Caso contrário
    // desligamos o LED
    digitalWrite(LED_BUILTIN, LOW);
  }
}

