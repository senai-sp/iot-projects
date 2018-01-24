// Para rodar em arduino, fazer upload de PingFirmata:
// https://gist.githubusercontent.com/rwaldron/0519fcd5c48bfe43b827/raw/f17fb09b92ed04722953823d9416649ff380c35b/PingFirmata.ino
const five = require('johnny-five');
const placa = new five.Board();
const Porta = require('./Porta');

const raioDeteccao = 5; // cm

let contagemPessoas = 0;

placa.on("ready", function() {
  const ultrassom1 = new five.Proximity({
    pin: 10,
    controller: "HCSR04",
    freq: 25 // padrão
  });

  let portaEntrada = new Porta(ultrassom1, raioDeteccao);
  portaEntrada.on("passou", function() {
    contagemPessoas++;
  })
  let portaSaida = new Porta(ultrassom1, raioDeteccao);
  portaSaida.on("passou", function() {
    contagemPessoas--;
  })
});
