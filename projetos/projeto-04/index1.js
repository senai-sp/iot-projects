// Para rodar em arduino, fazer upload de PingFirmata:
// https://gist.githubusercontent.com/rwaldron/0519fcd5c48bfe43b827/raw/f17fb09b92ed04722953823d9416649ff380c35b/PingFirmata.ino
const five = require('johnny-five');

const board = new five.Board();

const distanciaObstaculo = 10; // cm

let contagemPessoas;

board.on("ready", function() {
  const ultrasound = new five.Proximity({
    pin: 10,
    controller: "HCSR04",
    freq: 50
  });

  let possuiaObstaculo = false;
  ultrasound.on("data", function() {
    const distancia = this.cm;
    // caso o obstaculo 'saiu' da frente do sensor nesta chamada do evento...
    if (distancia >= distanciaObstaculo && possuiaObstaculo) {
      // considerar que uma pessoa passou
      contagemPessoas++;
    }
    possuiaObstaculo = distancia < distanciaObstaculo;

    console.log("Medição: " + this.cm + " cm");
    console.log("Contagem: " + contagemPessoas);
  });
});
