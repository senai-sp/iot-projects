#define PIN_BUTTON 8

void buttonSetup() {
	pinMode(PIN_BUTTON, INPUT);
	Serial.begin(9600);
}

void buttonLoop() {
	Serial.println(digitalRead(PIN_BUTTON));
	delay(100);
}
