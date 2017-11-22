#include <Keypad.h>
#include <Tone.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {5, 4, 3, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Tone freq1;
Tone freq2;

// https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling#Keypad
// os valores representam frequencias de linha e coluna para cada número
// os valores 10 e 11 representam '*' e '#', respectivamente
const int DTMF_freq1[] = { 1336, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1477 };
const int DTMF_freq2[] = {  941,  697,  697,  697,  770,  770,  770,  852,  852,  852, 941, 941 };
const int duration = 500;

void setup(){
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);

	freq1.begin(A4);
	freq1.begin(A5);
}

void loop(){
  char key = keypad.getKey();

	switch(key) {
		case '1':
			freq1.play(DTMF_freq1[1], duration);
			freq2.play(DTMF_freq2[1], duration);
			break;
		case '2':
			freq1.play(DTMF_freq1[2], duration);
			freq2.play(DTMF_freq2[2], duration);
			break;
		case '3':
			freq1.play(DTMF_freq1[3], duration);
			freq2.play(DTMF_freq2[3], duration);
			break;
		case '4':
			freq1.play(DTMF_freq1[4], duration);
			freq2.play(DTMF_freq2[4], duration);
			break;
		case '5':
			freq1.play(DTMF_freq1[5], duration);
			freq2.play(DTMF_freq2[5], duration);
			break;
		case '6':
			freq1.play(DTMF_freq1[6], duration);
			freq2.play(DTMF_freq2[6], duration);
			break;
		case '7':
			freq1.play(DTMF_freq1[7], duration);
			freq2.play(DTMF_freq2[7], duration);
			break;
		case '8':
			freq1.play(DTMF_freq1[8], duration);
			freq2.play(DTMF_freq2[8], duration);
			break;
		case '9':
			freq1.play(DTMF_freq1[9], duration);
			freq2.play(DTMF_freq2[9], duration);
			break;
		case '0':
			freq1.play(DTMF_freq1[0], duration);
			freq2.play(DTMF_freq2[0], duration);
			break;
		case '*':
			freq1.play(DTMF_freq1[10], duration);
			freq2.play(DTMF_freq2[10], duration);
			break;
		case '#':
			freq1.play(DTMF_freq1[11], duration);
			freq2.play(DTMF_freq2[11], duration);
			break;
	}


	// BONUS: perceber como o seguinte código é equivalente para os caracteres '0'..'9'
	// int number = key - '0';
	// if(key) {
	// 	freq1.play(DTMF_freq1[number], duration);
	// 	freq2.play(DTMF_freq2[number], duration);
	// }
}
