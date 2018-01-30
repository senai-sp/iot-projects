const five = require("johnny-five");
const board = new five.Board({
    port: "COM11"
});

const request = require("request");
const configuracao = require("./config");
const id = configuracao.idSensor;
const api = configuracao.api;
const endpointUpdateSensor = api + "/api/Sensor/" + id;

board.on("ready", function() {
    const ultrassom = new five.Proximity({
        pin: 10,
        controller: "HCSR04",
        freq: 2000
    });
    ultrassom.on("data", function() {
        console.log(this.cm);
        const cm = Math.floor(this.cm);
        const dados = {
            valor: cm
        };
        request.put(endpointUpdateSensor, {
            json: true,
            body: dados
        }, function(error, res, body){
            if(error) {
                console.error(error);
                return;
            }
            // erro é nulo, tudo ok
            console.log(res && res.statusCode);
            console.log(body);
        });
    });
});