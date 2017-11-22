const int luz = A1;
void setup()
{
  // não precisamos configurar o pino como INPUT | OUTPUT
  
  Serial.begin(9600);
  while(!Serial) {}
}

void loop()
{
  int leitura = analogRead(luz);
  Serial.println(leitura);
  delay(100);
}