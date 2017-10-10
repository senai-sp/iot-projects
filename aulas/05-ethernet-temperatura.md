# Envio de dados via Ethernet + HTTP

Nesta aula iremos utilizar um shield Ethernet baseado no chip ENC28J60.

Utilizaremos o mesmo sensor de temperatura visto na aula passada e vamos enviar 

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

Recomendamos utilizar a biblioteca [ArduinoJson](https://github.com/bblanchon/ArduinoJson/) para manipular esse tipo de dados.

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

## Servidor para gráfico de temperaturas

Nesta aula utilizaremos a plataforma [NodeJS](http://nodejs.org/) como um simples servidor http para cadastrarmos as temperaturas lidas de nossos sensores.

O código exemplo do servidor está disponível neste [link](src/ethernet-temperaturas/servidor).
### Utilizando NodeJS portátil no Windows

O NodeJS está disponível num pacote portátil através de seu download binário (Windows Binary) de https://nodejs.org/en/download/current/.

## Links

- [Documentação para API Ethernet do Arduino](https://www.arduino.cc/en/Reference/Ethernet)
- [Repositório para biblioteca UIPEthernet](https://github.com/UIPEthernet/UIPEthernet)
- [Formato JSON](http://www.json.org/json-pt.html)
- [Exemplos de HTTP GET e POST](http://playground.arduino.cc/Code/WebClient)
- [Site oficial do NodeJS](https://nodejs.org/)