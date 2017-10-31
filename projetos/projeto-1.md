# Projeto Automação residencial(Garagem) via Cloud/MQTT

## Objetivo

1.  Criar uma mini maquete com uma lâmpada e um portão usando no mínimo
    os componentes abaixo
2.  Fazer o controle tanto da lâmpada, quanto do portão de maneira
    manual e MQTT
3.  Implementar soluções para dar um feedback para o usuário
    evidenciando se algum serviço está inativo ou não está funcionando

## FeedBack para o usuário

-   O arduino deve avisar de alguma forma quando o serviço estiver
    desconectado do MQTT
-   O arduino deve avisar de alguma forma quando o serviço estiver
    conectado ao MQTT
-   O arduino deve avisar de alguma forma quando o serviço estiver se
    conectando ao MQTT
-   O arduino deve avisar de alguma forma quando estiver mandando uma
    mensagem para o MQTT

## Requisitos

Sua solução deve:

-   conter um Servo Motor que irá representar o “Portão de garagem”
-   conter uma lâmpada que irá representar a “Luz” da garagem, por
    exemplo um LED, ou Lâmpada regular controlada via Relay
-   ao interagir com um componente de INPUT (pushbutton, sensor
    analógico, etc.), o estado do Portão deverá se alterar entre Aberto
    e Fechado.
-   reportar o estado do Portão via MQTT
-   alterar o estado do Portão via MQTT
-   reportar o estado da Luz via MQTT
-   alterar o estado da Luz via MQTT
-   reportar constantemente se a conexão com o servidor MQTT está ativa
    via um componente de OUTPUT (LED, LCD, etc.)
-   oferecer feedback para cada mensagem recebida e enviada via MQTT
    (LED piscando por curto tempo, Buzzer, mensagem em LCD, etc)
-   O Portão deve terminar uma transição (abrir e fechar completamente)
    antes de realizar outra, comandos recebidos durante este intervalo
    podem ser ignorados ou enfileirados para serem executados em
    sequência
-   O Luz deve ser acesa 1s após o Portão terminar de ser aberto, e deve
    ser apagada 1s após o portão terminar de ser fechado.

Componentes

-   Micro Servo Motor

    -   [Biblioteca Servo](https://www.arduino.cc/en/reference/servo)
    -   [Micro Servo Motor SG90 com Arduino Uno](https://www.filipeflop.com/blog/micro-servo-motor-9g-sg90-com-arduino-uno/)
    -   [Controlando um servo motor utilizando Android e Bluetooth](http://www.arduinoecia.com.br/2014/01/controlando-um-servo-motor-utilizando.html)

-   Luzes de LED
    -   [Ajustando o brilho de um LED via PWM](https://www.filipeflop.com/blog/ajustando-o-brilho-de-um-led-por-pwm/)

-   Relay (Opcional)
    -   [Modulo Relé](https://www.filipeflop.com/blog/controle-modulo-rele-arduino/)

-   Módulo ethernet
    -   [Como utilizar o Ethernet ENC28J60 com Arduino](https://www.filipeflop.com/blog/modulo-ethernet-enc28j60-arduino/)

-   Servidor MQTT
    -   [https://www.cloudmqtt.com/](https://www.cloudmqtt.com/): Host online com plano gratuito
    -   [https://mosquitto.org/](https://mosquitto.org/): Software para broker MQTT

Conhecimentos necessários

-   Estruturas de controle/decisão e loop ex.: if, else, case, for...

    -   [If](https://www.arduino.cc/en/Reference/If)
    -   [Else](https://www.arduino.cc/en/Reference/Else)
    -   [SwitchCase](https://www.arduino.cc/en/Reference/SwitchCase)
    -   [For](https://www.arduino.cc/en/Reference/For)

-   Comunicação MQTT - [http://mqtt.org/](http://mqtt.org/)

    -   [Biblioteca PubSubClient](https://pubsubclient.knolleary.net/)

-   Criação de funções e variáveis

    -   [Constants](https://www.arduino.cc/en/Reference/Constants)

-   Escrita analógica e digital

    -   [PinMode](https://www.arduino.cc/en/Reference/PinMode)
    -   [DigitalWrite](https://www.arduino.cc/en/Reference/DigitalWrite)
    -   [DigitalRead](https://www.arduino.cc/en/Reference/DigitalRead)
    -   [AnalogRead](https://www.arduino.cc/en/Reference/AnalogRead)
    -   [AnalogWrite](https://www.arduino.cc/en/Reference/AnalogWrite)
    -   [AnalogReference](https://www.arduino.cc/en/Reference/AnalogReference)

-   Comunicação Serial

    -   [https://www.arduino.cc/en/Reference/Serial](https://www.arduino.cc/en/Reference/Serial)

## Ferramentas de controle e organização

1.  [Git](https://git-scm.com/)
2.  [Trello](https://trello.com/)
3.  [Slack](http://codexp-senai.slack.com/)

**Prazo**: 4 Dias

**Quantidade de Pessoas**: 2
