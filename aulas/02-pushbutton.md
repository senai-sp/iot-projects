# Introdução

Neste projeto adicionamos um Pushbutton ao nosso circuito com LED.

O Pushbutton é um botão que retorna ao estado normal quando é solto (ao invés de permanecer pressionado como um interruptor).
Dentre seus 4 terminais, 2 pares ficam sempre conectados entre si, porém todos se conectam quando o botão é pressionado.

Essa é a razão de sua representação em circuito elétrico ser a seguinte:

![pushbutton](https://github.com/senai-sp/iot-exercicios/raw/master/02-pushbutton/pushbutton.png)

## Desenho

### Protoboard

![protoboard](https://github.com/senai-sp/iot-exercicios/raw/master/02-pushbutton/sketch.png)

### Elétrico

![eletrico](https://github.com/senai-sp/iot-exercicios/raw/master/02-pushbutton/sketch_schem.png)

## Código

- [pushbutton.ino](https://github.com/senai-sp/iot-exercicios/blob/master/02-pushbutton/pushbutton.ino)
- [exemplo mínimo](https://github.com/senai-sp/iot-exercicios/blob/master/02-pushbutton/pushbutton-minimo.ino)
- [versão 'toggle'](https://github.com/senai-sp/iot-exercicios/blob/master/02-pushbutton/pushbutton-toggle.ino)

## Conceitos

- Entendimento mais profundo do `loop()`
- Variáveis globais para acompanhamento de estado
- pinMode INPUT