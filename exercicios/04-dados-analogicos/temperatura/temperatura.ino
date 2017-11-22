const int temp = A1;
void setup()
{
  // não precisamos configurar o pino como INPUT | OUTPUT
  
  Serial.begin(9600);
  while(!Serial) {}
}

void loop()
{
  // a funçao analogRead lê valores entre 0 e 1023 (informação da documentação)
  int leitura = analogRead(temp);
  // mapeamos esse intervalo para 0mV até 5000mV (porta 5V do arduino = alimentação de 5000mV)
  float milliVolts = map(leitura, 0, 1023, 0, 5000);
  Serial.print(milliVolts); Serial.println(" milliVolts");
  
  // para o sensor TMP36 disponível no TinkerCAD, precisamos subtrair mais 500mV
  // pois segundo sua documentação ele já tem essa tensão como valor mínimo
  // i.e. ele varia de 500mV a 5V
  // milliVolts -= 500;
  
  // dividimos o valor por 10 para saber a temperatura,
  // pois segundo o datasheet do sensor, ele varia 10mV por 1ºC
  float temperatura = milliVolts / 10.0;
  Serial.println(temperatura);
  delay(100);
}
