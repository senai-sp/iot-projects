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

- O exemplo em `Exemplos > Ethernet > WebClient` é um bom início para seu programa, ele deve rodar somente substituindo a biblioteca conforme a seção [Utilizando a biblioteca UIPEthernet](#utilizando-a-biblioteca-uipethernet)
- Veja o [código do servidor](src/ethernet-temperatura/servidor) para documentação

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

Nesta aula utilizaremos um simples servidor HTTP para cadastrarmos as temperaturas lidas de nossos sensores.

Esse servidor foi escrito em cima da plataforma [NodeJS](https://nodejs.org) e seu código está disponível [neste link](src/ethernet-temperatura/servidor).

Para acessar o servidor entre em http://[endereço da maquina]:8080/grafico.

### Utilizando NodeJS portátil no Windows

O NodeJS está disponível num pacote portátil através de seu download binário (Windows Binary) de https://nodejs.org/en/download/current/.

### Formato da mensagem HTTP POST
A seguir está um exemplo da mensagem completa que deve ser enviada ao servidor.

```
POST / HTTP 1.1
Host: 127.0.0.1
Content-Type: application/json
Content-Length: 22
Connection: close

{"temp": 25, "id": 42}
```

Explicação das seções:

- **POST**: método do protocolo HTTP, normalmente significa a inserção de um novo recurso. Em nosso exercício, estamos 'inserindo' um novo registro de temperatura
- **'/'**: Endereço relativo à raiz do servidor web, neste caso estamos manipulando um recurso situado à própria raiz do servidor.
- **HTTP 1.1**: identificação do protocolo e sua versão
- **Host**: identificação do servidor
- **127.0.0.1**: endereço do servidor, substituir pelo real. Este valor é um valor especial para a própria máquina local.
- **Content-Type**: [Cabeçalho](https://en.wikipedia.org/wiki/List_of_HTTP_header_fields) que identifica o tipo de conteúdo enviado na requisição, pode ser texto, dados binários (exemplo: upload de imagem), etc.
- **application/json**: identificação do conteúdo como sendo uma mensagem contendo JSON
- **Content-Length: 22**: Cabeçalho que informa ao servidor o tamanho em bytes do conteúdo da mensagem, 22 refere-se ao tamanho do texto JSON
- **Connection: close**: Cabeçalho que pede que a conexão seja terminada logo após a troca de mensagens.
- **{"temp": 25, "id": 42}**: conteúdo JSON da mensagem em si, às vezes chamado de **Body** ou **Payload**

## Links

- [Fundamentos do HTTP](https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Basico_sobre_HTTP)
- [Documentação para API Ethernet do Arduino](https://www.arduino.cc/en/Reference/Ethernet)
- [Repositório para biblioteca UIPEthernet](https://github.com/UIPEthernet/UIPEthernet)
- [Formato JSON](http://www.json.org/json-pt.html)
- [Exemplos de HTTP GET e POST](http://playground.arduino.cc/Code/WebClient)
- [Site oficial do NodeJS](https://nodejs.org/)
- [Lista de cabeçalhos HTTP](https://en.wikipedia.org/wiki/List_of_HTTP_header_fields)

## Código
- [Servidor (NodeJS)](./src/ethernet-temperatura/servidor/)
- [Solução](./src/ethernet-temperatura/ethernet-temperatura.ino)