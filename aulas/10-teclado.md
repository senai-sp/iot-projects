# Teclado

Neste exercício vamos utilizar o teclado numérico para tocar sons do telefone analógico ([DTMF](https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling)).

# Cenários propostos

Para a execução destes cenários seu projeto físico deverá conter no máximo:

- 1 Teclado Numérico (presente no kit avançado)
- 1 Buzzer
- 2 Resistores para controle do Buzzer
- 1 Arduino Uno

## 1 - Básico

Instale o teclado numérico em seu Arduino e faça com que as teclas digitadas sejam enviadas imediatamente via comunicação Serial.

Verifique o funcionamento através do Monitor Serial da IDE.

## 2 - Enviando Senha

Quando o usuário digitar o caractere '*', comece a armazenar os caracteres digitados pelo usuário através do teclado numérico.

Ao caractere '#' ser digitado, envie os caracteres em uma linha via comunicação Serial.

## 3 - DTMF (Sons de telefone)

Fazer o buzzer tocar os dois tons respectivos à tecla pressionada no teclado numérico.

Seguir a tabela em [link](https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling#Keypad) e verificar o exemplo em [DTMF](https://github.com/paolobueno/Tone/blob/master/examples/DTMFTest/DTMFTest.pde).

Para controlar o Buzzer a partir de 2 pinos, utilize os resistores de 300 Ohms para seu polo positivo.

## Bibliotecas

- **Keypad**: https://playground.arduino.cc/Code/Keypad
- **Tone**: https://github.com/paolobueno/Tone

## Exemplos a utilizar

- Keypad: https://playground.arduino.cc/Main/KeypadTutorial
- DTMF: https://github.com/paolobueno/Tone/blob/master/examples/DTMFTest/DTMFTest.ino

A biblioteca **Keypad** necessita informações de quais pinos são Linhas e Colunas no teclado.

![keypad](https://www.robocore.net/upload/lojavirtual/164_4_H.png)

A figura acima mostra que os primeiros 3 pinos do teclado presente no kit se tratam dos pinos de Colunas, enquanto os 4 restantes são pinos de Linhas.

Portanto os pinos digitais do Arduino aos quais estes estão conectados são os que devem ser passados à biblioteca, respectivamente.

## Desenho

![protoboard](https://github.com/senai-sp/iot-exercicios/blob/master/10-teclado/circuito.png)

## Código

- [Básico](https://github.com/senai-sp/iot-exercicios/blob/master/10-teclado/teclado/teclado.ino)
- [DTMF](https://github.com/senai-sp/iot-exercicios/blob/master/10-teclado/dtmf/dtmf.ino)
