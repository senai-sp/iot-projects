const int PINO_BUZZER = 4;
const int TONE_DURATION = 150;
const int PINO_LED_OK = 9;
const int PINO_LED_WARN = 10;

void feedbackSaidaMqtt() {
  tone(PINO_BUZZER, 1047, TONE_DURATION);
  delay(TONE_DURATION);
}

void feedbackChegadaMqtt() {
  tone(PINO_BUZZER, 131, TONE_DURATION);
  delay(TONE_DURATION);
}

void setupFeedback() {
  pinMode(PINO_BUZZER, OUTPUT);
  pinMode(PINO_LED_OK, OUTPUT);
}

void loopFeedback() {
  int state = client.state();
  if (state == 0) {
    digitalWrite(PINO_LED_OK, HIGH);
    digitalWrite(PINO_LED_WARN, LOW);
  } else {
    digitalWrite(PINO_LED_OK, LOW);
    digitalWrite(PINO_LED_WARN, HIGH);
  }
}
