const EventEmitter = require('events');

/**
 * Classe que simboliza uma porta com contagem de passantes
 * Manipula um sensor do tipo johnnyFive.Proximity
 */
class Porta {
	/**
	 * Construtor para classe Porta
	 * @param {five.Proximity} sensor Sensor de proximidade
	 * @param {number} raio distancia a medir em cm
	 */
	constructor(sensor, raio) {
		this.sensor = sensor;
		this.raio = raio;
		this.emissor = new EventEmitter();

		let tinhaObstaculo = false;

		function callback() {
			let haObstaculo = this.cm >= raioDeteccao;
			if (
				// se não há mais obstaculo
				!haObstaculo
				// e havia na iteração anterior
				&& tinhaObstaculo
			) {
				// emitir o evento "passou"
				this.emissor.emit("passou");
			}

			// tem algum obstaculo em frente
			tinhaObstaculo = haObstaculo;
		}

		// Configurar sensor do j5 para chamar callback com nossa lógica
		this.sensor.on("data", callback);
	}
	/**
	 * Cadastra 'ouvintes' para o evento desta classe
	 * Funções chamadas quando eventos são disparados são chamadas normalmente
	 * de 'listener' ou 'handler' em ingles
	 * @param {string} evento nome do evento, valores possíveis: "passou"
	 * @param {function} cb ouvinte para o evento
	 */
	on(evento, cb) {
		// cadastrar cb como ouvinte do evento
		this.emissor.on(evento, cb);
	}
}
module.exports = Porta;
