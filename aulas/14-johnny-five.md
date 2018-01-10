# Johnny-Five

Nesta aula utilizaremos a biblioteca [Johnny-Five](http://johnny-five.io/) para manipular o Arduino a partir de um processo NodeJS rodando em nossa máquina principal.

## Instalação

### NodeJS

O NodeJS é uma plataforma para o desenvolvimento de aplicações utilizando JavaScript rodando em ambientes fora de browsers (costumamos ver JavaScript rodando somente em nossos Firefox, Google Chrome, etc.)

Com a biblioteca Johhny-Five podemos controlar plataformas de IoT como o Arduino dentro de programas escritos para NodeJS.

### Configuração do Arduino

Para controlarmos o arduino através de um processo NodeJS com Johnny-Five, devemos carregar o programa StandardFirmataPlus, ele contém uma implementação do [protocolo Firmata](https://github.com/firmata/protocol), criado para padronizar o controle de unidades IoT de softwares em computador.

Ele está disponível na galeria padrão de exemplos da IDE do Arduino em `Arquivo > Exemplos > StandardFirmataPlus`.

## Criação do projeto com Johnny-Five

Para criar o projeto, crie uma nova pasta, e abra um terminal do `cmd.exe` ou `bash` nela, por exemplo através do `Windows Explorer > Menu de Contexto > Git Bash Here` e execute os seguintes comandos:

```bash
npm init # inicializa um arquivo package.json com configurações do projeto, como nome do projeto, autor, etc.
npm install --save johnny-five # adiciona a biblioteca johnny-five ao projeto
```

O executável `npm`, ou **N**ode **P**ackage **M**anager, é um programa auxiliar que utilizamos para adicionar dependências a nossos projetos e executar scripts auxiliares, assim como potencialmente publicar nossas próprias bibliotecas.

A seguir, crie um arquivo `index.js` nessa nova pasta com o seguinte código:

```javascript
// obter o código da biblioteca
var five = require("johnny-five");

// criar uma instância que representa nossa placa
var board = new five.Board({
	port: "COM*" // substitua pela porta a qual seu Arduino estiver conectado
});

// vincular código a ser rodado quando a comunicação com a placa começar
board.on("ready", function() {

	// vincular uma variável do tipo Led que controla o pino 13
  var led = new five.Led(13);

	// piscar o led a cada 500ms
  led.blink(500);
});
```

Em seguida rode-o com `node index.js`.

## Exercício

Ver a [documentação das classes do Johnny Five](http://johnny-five.io/api/) e exemplos disponíveis e faça um programa que manipule outros elementos presentes em nosso kit, como por exemplo: `Button`, `Led.RGB`, `Sensor` (para qualquer sensor analógico), `Piezo` (Buzzer), etc.

## Links

- [NodeJS](http://nodejs.org/)
- [Johnny Five](http://johnny-five.io/)
- [Firmata Protocol](https://github.com/firmata/protocol)
- [Visual Studio Code](https://code.visualstudio.com/) - Editor de código recomendado
