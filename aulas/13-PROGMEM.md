# PROGMEM

O Arduino possui diferentes seções de memória para armazenar o programa a ser executado, e as variáveis em tempo de execução.

Quando um programa é compilado, a IDE nos informa da utilização desse espaço pelo nosso programa:

```
Sketch uses 25482 bytes (78%) of program storage space. Maximum is 32256 bytes.
Global variables use 1716 bytes (83%) of dynamic memory, leaving 332 bytes for local variables. Maximum is 2048 bytes.
```

Os valores acima vem das opções de compilação estarem apontando para um `Arduino UNO`.

## Memória Dinâmica

A seção denominada `dynamic memory` acima é a reservada para as variáveis utilizadas pelo programa. A sigla que a descreve é `SRAM`: (**S**tatic **R**andom **A**ccess **M**emory). Análoga à RAM de um computador regular.

O compilador pode nos informar sobre a utilização de memória das variáveis globais, e através disso informar quanto espaço fica disponível para variáveis locais.

## Memória de Programa

A memória para armazenamento de nossos programas é identificada pelo acrônimo `PROGMEM`, e é armazenada em memória Flash (como a de pendrives e SSDs).

Além do nosso programa em si, é possível também armazenar conteúdo a ser utilizado em tempo de execução. Isso é feito utilizando a biblioteca `avr/pgmspace.h`, documentada [aqui](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/), e também de maneira mais simples através da macro `F()`.


### Macro `F()`

O ambiente de desenvolvimento do Arduino disponibiliza uma macro para mais facilmente armazenar variáveis na memória de programa ao invés da SRAM.

Ela é utilizada de maneira mais simples com strings estáticas:

```c++
Serial.println(F("Olá Mundo!"));
```

A string acima será armazenada em memória de programa e lida dela em tempo de execução para ser passada para a função `Serial.println()`.

## Links

A tabela seguinte mostra a quantidade de memória disponível para cada microcontrolador presentes no Arduino.

O modelo UNO utliza o ATMega328P:

|   | ATMega168 | ATMega328P | ATmega1280 | ATmega2560 |
|---|---|---|---|---|
| Flash | 16 kBytes | 32 kBytes | 128 kBytes | 256 kBytes |
| SRAM | 1024 bytes | 2048 bytes | 8 kBytes | 8kBytes |
| EEPROM | 512 bytes | 1024 bytes | 4 kBytes | 4 kBytes |

- [Tipos de memória do Arduino](https://www.arduino.cc/en/Tutorial/Memory)
- [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)
