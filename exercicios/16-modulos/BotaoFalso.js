class BotaoFalso {
	// constructor
	constructor(pin) {
		this.pin = pin;
		this.handlers = {};
	}
	apertar() {
		console.log("Apertado botão no pino " + this.pin);
		this.invoke('down');
	}
	on(evento, cb) {
		this.handlers[evento] = this.handlers[evento] || [];
		this.handlers[evento].push(cb);
	}

	invoke(event) {
		if(this.handlers[event] && this.handlers[event].length) {
			this.handlers[event].forEach(function(cb) {
				cb(this);
			});
		}
	}
}

module.exports = BotaoFalso;
