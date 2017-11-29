// O arquivo .cpp deve incluir seu próprio header
#include "Button.h"

/**
 * Construtor principal que recebe todos os parâmetros
 */
Button::Button(unsigned int pin, ASSINATURA_CALLBACK, unsigned int debounce) {
	this->pin = pin;

	// Delegamos a configuração dos outros parâmetros para funções específicas
	setCallback(callback);
	setDebounce(debounce);
}

Button::Button(unsigned int pin, ASSINATURA_CALLBACK) {
	this->pin = pin;
	setCallback(callback);
	// Para as versões dos construtores que recebem menos parâmetros,
	// só configuramos valores padrão
	setDebounce(BUTTON_DEFAULT_DEBOUNCE);
}
Button::Button(unsigned int pin) {
	this->pin = pin;
	setCallback(callback);
	setDebounce(BUTTON_DEFAULT_DEBOUNCE);
}

/**
 * Altera o pointer de callback interno para outra função
 */
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
	// Caso não haja função de callback para chamar, não é necessário executar processamento
	if (!callback) {
		return;
	}

	// Tempo atual da execução
	unsigned long now = millis();

	// Se o tempo de debounce não se passou, fazer nada
	if (now - this->lastHit < this->debounce) {
		// A instrução return; numa função void (que não deve retornar valor)
		// simplesmente finaliza a execução da função
		return;
	}

	// Ler estado do botão
	int currentPinState = digitalRead(this->pin);

	// Caso o estado do botão tenha mudado...
	if(!this->lastPinState && currentPinState) {
		// ...armazenar o tempo do ultimo clique...
		this->lastHit = now;
		// ...e chamar a função de callback
		this->callback();
	}

	// Armazenar estado anterior do botão
	this->lastPinState = currentPinState;
}
