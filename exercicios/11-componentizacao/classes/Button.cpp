#include "Button.h"

// Construtores
Button::Button(unsigned int port, ASSINATURA_CALLBACK, unsigned int debounce) {
	this->port = port;
	setCallback(callback);
	setDebounce(debounce);
}
Button::Button(unsigned int port, ASSINATURA_CALLBACK) {
	this->port = port;
	setCallback(callback);
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
