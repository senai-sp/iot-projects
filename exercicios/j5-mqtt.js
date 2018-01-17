var five = require("johnny-five");
var mqtt = require("mqtt");
var board = new five.Board({
    port: "COM10"
});

var client = mqtt.connect("mqtt://test.mosquitto.org");

client.on("connect", function () {
    // a partir daqui, estamos conectados ao broker MQTT
    board.on("ready", function () {
        // a partir daqui, a board do johnny-five está pronta
        console.log("Estou pronta pra ser usada...");

        client.subscribe('codexp1-portao');
        function callback(topic, payload) {
            // recebemos "1" para abrir o portao
            // e "0" para fechar o portao
            var msg = payload.toString();

            if (msg === "1") {
                abrirPortao();
            } else if (msg === "0") {
                fecharPortao();
            } else {
                console.log(topic);
                console.log(msg);
            }
        }
        client.on("message", callback);

        var button = new five.Button(8);
        var portaoAberto = false;
        var servo = new five.Servo({
            pin: 10,
            startAt: 19
        });
        function fecharPortao() {
            servo.to(19, 1 * 1000);
            portaoAberto = false;
            console.log("Portão fechado");
        }
        function abrirPortao() {
            servo.to(90, 1 * 1000);
            portaoAberto = true;
            console.log("Portão aberto");
        }

        button.on("down", function () {
            if (portaoAberto) {
                fecharPortao();
            } else {
                abrirPortao();
            }
        });

        button.on("hold", function () {
            console.log("hold");
        });

        button.on("up", function () {
            console.log("up");
        });
    });
});
