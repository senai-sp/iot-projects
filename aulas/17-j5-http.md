# Controlando o Arduino via HTTP no Johnny Five

Nesta aula vamos servir uma página HTML com botões para interação do usuário e executar ações no Arduino.

## Configurando o projeto

1. Crie o projeto conforme descrito [na aula anterior](./14-johnny-five.md).
2. Adicione o módulo [express](https://expressjs.com/) via `npm install express`, que cuida de estabelecer um servidor HTTP

## Servindo uma página web via express

A seguir vamos utilizar o express para enviar uma página que será utilizada para controlar nosso arduino.

Veja o [exemplo](./15/estatico/index.js) para como enviar uma página HTML estática.

O código do exemplo irá rodar um servidor HTTP em http://localhost:3000 que retorna uma página com 2 botôes:

![estatico](./15/estatico.png)

## Tornando nossa página dinâmica

Em seguida iremos fazer que as requisições causadas pelos botôes alterem o valor de uma variável de nosso programa em node e refletir esse valor na página retornada pelo servidor.

Para isso precisamos instalar o módulo `express-handlebars` e utilizar o método `response.render()` para fazer com que nosso HTML seja processado e alterado dinâmicamente.

Veja o [2o exemplo](./15/dinamico/index.js) para como isso é feito.

## Integrando com o Johnny Five
