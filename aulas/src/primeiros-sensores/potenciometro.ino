const int pot = A1;
void setup()
{
  // não precisamos configurar o pino como INPUT | OUTPUT
  
  Serial.begin(9600);
  while(!Serial) {}
}

void loop()
{
  // O valor retornado por analogRead esta no intervalo entre 0-1023
  int leitura = analogRead(pot);
  Serial.println(leitura);
  delay(100);
}
