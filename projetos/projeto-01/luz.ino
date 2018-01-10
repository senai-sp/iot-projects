const int PINO_BTN_LUZ = 6;
const int PINO_LUZ = 2;
int statusLuz = 0;
int statusBtnLuz = 0;

void setLuz(int estado) {
  if (estado) {
    digitalWrite(PINO_LUZ, HIGH);
  } else {
    digitalWrite(PINO_LUZ, LOW);
  }
  statusLuz = estado;
  enviarMQTT(DISPOSITIVO_LUZ, estado);
}

void toggleLuz() {
  setLuz(!statusLuz);
}

void setupLuz() {
	pinMode(PINO_LUZ, OUTPUT);
}

void loopLuz() {
  int status = digitalRead(PINO_BTN_LUZ);
  if (status && !statusBtnLuz) {
    toggleLuz();
  }
  statusBtnLuz = status;
}
