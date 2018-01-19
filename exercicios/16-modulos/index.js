var five = require("johnny-five");
var mqtt = require("mqtt");
var Portao = require("./Portao");
var board = new five.Board({
    port: "COM10"
});

var config = require('./config');
var broker = config.mqttBroker;

board.on("ready", function () {
    // a partir daqui, a board do johnny-five está pronta
    console.log("Estou pronta pra ser usada...");

    var client = mqtt.connect(broker);
    client.on("connect", function () {
        console.log('MQTT Conectado!');
        // a partir daqui, estamos conectados ao broker MQTT
        client.subscribe('codexp1-portao');
        function callback(topic, payload) {
            // recebemos "1" para abrir o portao
            // e "0" para fechar o portao
            var msg = payload.toString();

            if (msg === "1") {
                portao.abrir();
            } else if (msg === "0") {
                portao.fechar();
            } else {
                console.log(topic);
                console.log(msg);
            }
        }
        client.on("message", callback);
    });

    var button = new five.Button(8);
    var servo = new five.Servo({
        pin: 10,
        startAt: 19
    });
    var servo2 = new five.Servo({
        pin: 13,
        startAt: 19
    });
    var portao = new Portao(servo);
    var portao2 = new Portao(servo2);
    button.on("down", function () {
        portao.alternar();
    });

    button.on("hold", function () {
        console.log("hold");
    });

    button.on("up", function () {
        console.log("up");
    });
});
