const five = require("johnny-five");
const board = new five.Board({
    port: "COM12"
});

const net = require('./net');

board.on("ready", function() {
    net.obterId(function(erro, id) {
        if(erro) {
            console.error(erro);
        }
        // tenho meu id via POST
        ultrassom.on("data", function() {
            console.log(this.cm);
            const cm = Math.floor(this.cm);
            const dados = {
                valor: cm
            };
            net.atualizar(id, dados, function(error, sensor){
                if(error) {
                    console.error(error);
                    return;
                }
                console.log(sensor);
            });
        });
    });
    const ultrassom = new five.Proximity({
        pin: 6,
        controller: "HCSR04",
        freq: 2000
    });
});
