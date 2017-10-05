const int btn = 2;

// Declaramos as variáveis a seguir fora do loop() para que estejam disponíveis para
// todas as execuções de loop(), e seus valores sejam mantidos

// Variável para termos um histórico de se o botão estava pressionado no
// loop() anterior ou não
int prevBtnState = 0;

// Variável para determinar se o led deve ser aceso ou não
int ledOn = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(btn, INPUT);
}

void loop() {
  int btnState = digitalRead(btn);
  // Caso o botão esteja pressionado neste instante, e não estava pressionado anteriormente
  if (btnState && !prevBtnState) {
    // Invertemos o estado do LED
    if (ledOn) {
      ledOn = 0;
    } else {
      ledOn = 1;
    }

    // Como exercício adicional, tente compreender como a seguinte linha seria
    // equivalente ao bloco `if` acima:

    // ledOn = 1 - ledOn;
  }

  // Finalmente ligamos/desligamos o LED de acordo com a variavel
  digitalWrite(LED_BUILTIN, ledOn);

  // Armazenando o estado atual do botão para a próxima execução de loop()
  prevBtnState = btnState;
}

