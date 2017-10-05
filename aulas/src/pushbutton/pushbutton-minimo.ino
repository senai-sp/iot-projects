/*
  Este exemplo contém uma versão mínima do código necessário para que nosso projeto
  com pushbutton funcione.
  Como exercício adicional, tente compreender como ele é equivalente.
*/
const int btn = 2;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(btn, INPUT);
}

void loop(){
  digitalWrite(LED_BUILTIN, digitalRead(btn));
}

