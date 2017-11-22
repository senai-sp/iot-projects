# Primeiros sensores analógicos

Nesta aula vamos ver como captar e processar a informação vindo de fontes analógicas

## Proposta do exercício

Para cada sensor, aprender como ler valores deles numa escala correta.

## Desenho

### Protoboard

#### Potenciometro

![potenciometro](../exercicios/04-dados-analogicos/potenciometro/potenciometro_bb.png)

#### Temperatura

![temperatura](../exercicios/04-dados-analogicos/temperatura/temperatura_bb.png)

#### Luz

![luz](../exercicios/04-dados-analogicos/luz/luz_bb.png)

### Elétrico


#### Potenciometro

![potenciometro](../exercicios/04-dados-analogicos/potenciometro/potenciometro_schem.png)

#### Temperatura

![temperatura](../exercicios/04-dados-analogicos/temperatura/temperatura_schem.png)

#### Luz

![luz](../exercicios/04-dados-analogicos/luz/luz_schem.png)

## Código

- [Exemplo potenciometro](../exercicios/04-dados-analogicos/potenciometro/potenciometro.ino)
- [Exemplo temperatura (LM35)](../exercicios/04-dados-analogicos/temperatura/temperatura.ino)
- [Exemplo sensor de luz](../exercicios/04-dados-analogicos/luz/luz.ino)

## Links

- [Datasheet LM35](http://www.ti.com/lit/ds/symlink/lm35.pdf) (sensor de temperatura)
- [Documentação para equação do sensor de temperatura](https://playground.arduino.cc/Main/LM35HigherResolution)
- [Descrição dos pinos analógicos do arduino](https://www.arduino.cc/en/Tutorial/AnalogInputPins)

Detalhe do datasheet LM35:
![datasheet](../exercicios/04-dados-analogicos/lm35.png)

## Conceitos
- Leitura de dados analógicos
- Potenciômetro
- Sensor de luz
- Sensor de temperatura
- Função `map()`
