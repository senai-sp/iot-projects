# Envio de dados via Ethernet + HTTP

Nesta aula iremos utilizar um shield Ethernet baseado no chip ENC28J60.

## Cenário proposto

- Utilizar o sensor de temperatura em um Sketch Arduino.
- Enviar dados do sensor de temperatura num intervalo de 5 segundos para o servidor rodando na máquina do professor

**Notas**

- Incluir a identificação do seu Kit em parte dos dados:

```javascript
{
  "id": 12, // numero do kit
  "temp": 25 // Celcius
}
```

## Pinos para o ENC28J60

| ENC28J60 | Arduino |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| SCK | Pino 13 |
| SO  | Pino 12 |
| SI  | Pino 11 |
| CS  | Pino 10 |

## Utilizando a biblioteca UIPEthernet

1. Vá em `Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...` e instale a biblioteca `UIPEthernet` em sua última versão
2. Vá em `Sketch > Incluir Biblioteca > UIPEthernet`
3. Remova referências à biblioteca `Ethernet.h` do Arduino caso necessário


## Instalando NodeJS portátil no Windows

1. Baixar o binário (Windows Binary) de https://nodejs.org/en/download/current/
2. Download the last zip version of npm from http://nodejs.org/dist/npm
4. Unpack the zip inside the node folder
5. Download the last tgz version of npm from http://nodejs.org/dist/npm
6. Open the tgz file and unpack only the file **bin/npm** (without extension) directly on the node folder.
7. Add the the node folder and the packages/bin folder to PATH
8. On a command prompt execute ```npm install -g npm``` to update npm to the latest version

## Links

- [Documentação para API Ethernet do Arduino](https://www.arduino.cc/en/Reference/Ethernet)
- [Repositório para biblioteca UIPEthernet](https://github.com/UIPEthernet/UIPEthernet)
- [Formato JSON](http://www.json.org/json-pt.html)
- [Exemplos de HTTP GET e POST](http://playground.arduino.cc/Code/WebClient)