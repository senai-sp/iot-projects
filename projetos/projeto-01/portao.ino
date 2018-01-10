#include <Servo.h>

const int PINO_SERVO = 3;
const int PINO_BTN_PORTAO = 7;
int statusPortao = 0;
int statusBtnPortao = 0;

long desligarLuzEm = -1;

Servo servo;

void setPortao(int estado) {
  if (estado) {
    servo.write(80);
    delay(1000);
  } else {
    servo.write(0);
    delay(1000);
  }
  statusPortao = estado;
  enviarMQTT(DISPOSITIVO_PORTAO, estado);

	// A Luz deve ser acesa 1s após o Portão terminar de ser aberto, e deve ser apagada 1s após o portão terminar de ser fechado.
	desligarLuzEm = millis() + 1000;
}

void togglePortao() {
  setPortao(!statusPortao);
}

void setupPortao() {
  servo.attach(PINO_SERVO);
}

void loopPortao() {
  int status = digitalRead(PINO_BTN_PORTAO);
  if (status && !statusBtnPortao) {
    togglePortao();
  }
  statusBtnPortao = status;

	if (desligarLuzEm != -1 && desligarLuzEm > millis()) {
		desligarLuzEm = -1;
		setLuz(statusPortao);
	}
}
