// Para rodar em arduino, fazer upload de PingFirmata:
// https://gist.githubusercontent.com/rwaldron/0519fcd5c48bfe43b827/raw/f17fb09b92ed04722953823d9416649ff380c35b/PingFirmata.ino
const five = require('johnny-five');
const placa = new five.Board();

const raioDeteccao = 5; // cm

let contagemPessoas = 0;

let tinhaObstaculo = false;
function callback() {
  let haObstaculo = this.cm >= raioDeteccao;
  if (
    // se não há mais obstaculo
    !haObstaculo
    // e havia na iteração anterior
    && tinhaObstaculo
  ) {
    // incrementar contador
    contagemPessoas++;
  }

  console.log(contagemPessoas);

  // tem algum obstaculo em frente
  tinhaObstaculo = haObstaculo;
}

placa.on("ready", function() {
  const portaEntrada = new five.Proximity({
    pin: 10,
    controller: "HCSR04",
    freq: 25 // padrão
  });

  portaEntrada.on("data", callback);
});
