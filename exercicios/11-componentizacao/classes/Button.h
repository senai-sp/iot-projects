// Utilizamos o preprocessador #ifndef para evitar problemas caso este
// arquivo sofra #include mais de uma vez
// https://pt.wikipedia.org/wiki/Include_guard
#ifndef BUTTON_h
#define BUTTON_h

#include <Arduino.h>

// Formato da assinatura do nosso callback,
// um pointer para uma função que não recebe nenhum parâmetro
#define ASSINATURA_CALLBACK void (*callback)()

#define BUTTON_DEFAULT_DEBOUNCE 200

class Button {
private:
	unsigned int port;
	unsigned int debounce;
	unsigned long lastHit;
	int lastPinState;
	ASSINATURA_CALLBACK;
public:
	Button(unsigned int port);
	Button(unsigned int port, ASSINATURA_CALLBACK);
	Button(unsigned int port, ASSINATURA_CALLBACK, unsigned int debounce);
	void setCallback(ASSINATURA_CALLBACK);
	void setDebounce(unsigned int millis);
	void loop();
};

#endif
