class Portao {
    constructor(servo) {
        this.aberto = false;
        this.servo = servo;
    }
    fechar() {
        if(!this.servo) {
            console.error("Preciso de um servo, plz");
        }
        this.servo.to(19, 1 * 1000);
        this.aberto = false;
        console.log("Portão fechado");
    }
    abrir() {
        this.servo.to(90, 1 * 1000);
        this.aberto = true;
        console.log("Portão aberto");
    }
    alternar() {
        if(this.aberto) {
            this.fechar();
        } else {
            this.abrir();
        }
        return this.aberto;
    }
}

module.exports = Portao;
