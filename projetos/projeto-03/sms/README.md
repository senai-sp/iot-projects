# Servidor Proxy SMS para o Projeto 3

Este é um servidor que acessa o serviço do [Twilio](https://www.twilio.com/) para envio de SMS


## Utilização

Para rodar este servidor, tenha o [NodeJS](http://nodejs.org/) instalado e rode os seguintes comandos via linha de comando no diretório do servidor:

```
npm install
npm start
```

## API

### `POST /sms`

Envia SMS através do serviço do Twilio.

Os parâmetros necessários são os seguintes:

- from: Número origem do twilio, sem o `"+"`
- to: Número alvo do SMS, sem o `"+"` (por exemplo seu número de celular)
- body: Texto da mensagem

Envie parâmetros no formato `applicationn/x-www-form-urlencoded` (texto simples separado por `'&'`).

O exemplo a seguir utiliza a biblioteca [RestClient](https://github.com/paolobueno/arduino-restclient).

```c++
EthernetClient ethClient;
const int porta = 3000;
RestClient client("ip-do-servidor", 3000, ethClient);


void setup() {
	Ethernet.begin(mac);
	client.post("/sms", "to=12345678&from=12345678&body=Ola Mundo");
}
```
