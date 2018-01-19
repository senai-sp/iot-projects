// Este arquivo ilustra as diferentes formatos de módulos
var batatinha = require('./funcoes');
var cenourinha = require('./somar');
var BotaoFalso = require('./BotaoFalso');

console.log(batatinha.somar(5, 6));
console.log(cenourinha(5, 6));

var botao = new BotaoFalso(8);

botao.on('down', function() {
	console.log('botao apertado');
});

botao.apertar();
