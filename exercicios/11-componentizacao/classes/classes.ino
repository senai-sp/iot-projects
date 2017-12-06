#include "Button.h"

#define PIN_BUTTON 8

void callback() { Serial.println("Botao pressionado!"); }

Button btn1(PIN_BUTTON);

void setup() {
  Serial.begin(9600);
  btn1.setCallback(callback);
  btn1.setDebounce(5 * 1000);
}

void loop() { btn1.loop(); }
