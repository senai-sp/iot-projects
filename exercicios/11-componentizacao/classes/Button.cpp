#include "Button.h"

/**
 * Construtor principal que recebe todos os parâmetros
 */
Button::Button(unsigned int port, ASSINATURA_CALLBACK, unsigned int debounce) {
	this->port = port;

	// Delegamos a configuração dos outros parâmetros para funções específicas
	setCallback(callback);
	setDebounce(debounce);
}

Button::Button(unsigned int port, ASSINATURA_CALLBACK) {
	this->port = port;
	setCallback(callback);
	// Para as versões dos construtores que recebem menos parâmetros,
	// só configuramos valores padrão
	setDebounce(BUTTON_DEFAULT_DEBOUNCE);
}
Button::Button(unsigned int port) {
	this->port = port;
	setCallback(callback);
	setDebounce(BUTTON_DEFAULT_DEBOUNCE);
}

void Button::setCallback(ASSINATURA_CALLBACK) {
	this->callback = callback;
}

/**
 *  Configurar o tempo mínimo entre detectar pressionamentos
 */
void Button::setDebounce(unsigned int millis) {
	this->debounce = millis;
}

void Button::loop() {
	unsigned long now = millis();

	if (now - this->lastHit < this->debounce) {
		return;
	}

	if (!callback) {
		return;
	}

	int currentPinState = digitalRead(this->port);

	if(!this->lastPinState && currentPinState) {
		this->lastHit = now;
		this->callback();
	}

	this->lastPinState = currentPinState;
}
