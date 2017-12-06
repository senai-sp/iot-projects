#include <Ultrasonic.h>

Ultrasonic ultrasonic(9, 10);

void loopUltrassom() {
  // Lê o valor do sensor
  int distancia = ultrasonic.distanceRead();

#ifdef DEBUG_ULTRASSOM
  // Escreve o valor da distância no painel Serial
  Serial.print(F("Distancia em CM: "));
  Serial.println(distancia);
#endif

  // Neste exemplo simplificado, mandamos SMS simplesmente quando algo
	// se aproxima
  if (distancia < 10) {
    requererEnvioSMS();
	}

  delay(1000);
}
