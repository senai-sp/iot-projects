// Utilizamos o preprocessador #ifndef para evitar problemas caso este
// arquivo sofra #include mais de uma vez
// https://pt.wikipedia.org/wiki/Include_guard
#ifndef BUTTON_h
#define BUTTON_h

// Dependências do módulo devem ser incluidas no arquivo .h
// A biblioteca Arduino.h é a que é incluida por padrão pela IDE do Arduino, ela que contém as definições de `digitalWrite()`, `digitalRead()`, etc.
// https://www.arduino.cc/reference/en/
#include <Arduino.h>

// Formato da assinatura do nosso callback,
// um pointer para uma função que não recebe nenhum parâmetro
#define ASSINATURA_CALLBACK void (*callback)()

//
#define BUTTON_DEFAULT_DEBOUNCE 200

// Declaração de classe
class Button {
private:
	unsigned int port;
	unsigned int debounce;
	unsigned long lastHit;
	int lastPinState;
	ASSINATURA_CALLBACK;
public:
	// Os métodos com o nome da própria classe são chamados Construtores
	// cada classe necessita de pelo menos um, que tem a função de inicializar suas variáveis internas
	Button(unsigned int pin);
	Button(unsigned int pin, ASSINATURA_CALLBACK);
	Button(unsigned int pin, ASSINATURA_CALLBACK, unsigned int debounce);

	void setCallback(ASSINATURA_CALLBACK);
	void setDebounce(unsigned int millis);

	// A função loop() deve ser chamada em toda iteração do loop() do Arduino, é nela que o processamento principal da biblioteca
	void loop();
};

#endif
