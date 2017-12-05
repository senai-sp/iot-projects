# Comunicação Local

Vamos ver como realizar a comunicação entre dois Arduinos localmente, e podendo através disso construir soluções que utilizam mais pinos digitais ou outras interfaces que possuem somente uma única 'cópia' disponível no modelo UNO que utilizamos no curso.

## Comunicação via Serial

O Arduino UNO possui duas interfaces para comunicação Serial: via o próprio cabo USB, e pelos pinos digitais `0` e `1`, marcados como `RX` e `TX`. É por este motivo que no UNO não podemos utilizar esses 2 pinos caso estejamos utilizando também a comunicação via USB a partir do PC.

Os modelos maiores como o Mega possuem mais interfaces seriais em hardware, estas ficam expostas para Sketchs via as variáveis `Serial1`, `Serial2`, etc.

### SoftwareSerial

A comunicação Serial também pode ser feita através de qualquer par de pinos digitais utilizando a biblioteca [`SoftwareSerial.h`](https://www.arduino.cc/en/Reference/SoftwareSerial).

As principais restrições dessa interface é que -- como o nome indica -- ela mantém o timing delicado da comunicação em software ao invés de poder contar com os timers de hardware disponíveis para a interface principal.

## Exemplos

Para comunicação entre dispositivos, seus pinos devem ser 'cruzados', i.e. o pino `TX` deve ser conectado ao pino `RX` da outra unidade.

```c++
// arduino1/arduino1.ino

void setup() {
	Serial.begin(9600);
	while(!Serial) {}
}

bool ligarLampada = false;

void loop() {
	ligarLampada = !ligarLampada;
	Serial.write(ligarLampada);
	delay(500);
}
```

A função `Serial.write()` escreve o byte diretamente, sem tentar convertê-lo para string, portanto o valor enviado será 0x0 e 0x1, ao invés de `'0'` (valor `48` / `0x30`) e `'1'` (valor `49`/`0x31`).

```c++
// arduino2/arduino2.ino

void setup() {
	Serial.begin(9600);
	while(!Serial) {}

	pinMode(13, OUTPUT);
}

void loop() {
	if(Serial.available()) {
		byte ligarLampada = Serial.read();
		if (ligarLampada) {
			digitalWrite(13, HIGH);
		} else {
			digitalWrite(13, LOW);
		}
	}
}
```

## Comunicação via I2C

O protocolo I2C utiliza os 2 pinos mais próximos do pino `AREF`, no caso do UNO são os pinos `A4` e `A5` (analógicos).

Este protocolo funciona com uma estrutura Master-Slave, onde uma unidade principal (Master) coordena a comunicação e Slaves operam quando requisitados pelo Master.

## Exemplos
- [I2C: Escrever a partir do Master](../exercicios/12-comunicacao-local/master-writer/)
- [I2C: Ler a partir do Master](../exercicios/12-comunicacao-local/master-reader/)

## Links

- [Biblioteca Wire (I2C)](https://www.arduino.cc/en/Reference/Wire)
- [Software Serial](https://www.arduino.cc/en/Reference/SoftwareSerial)
