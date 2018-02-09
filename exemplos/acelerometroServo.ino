#include <Servo.h>
Servo servo;

// O protocolo I2C utiliza as portas SDA e SCL (A4 e A5 do Arduino Uno)
#include <Wire.h>
// Baixar biblioteca do gerenciador da IDE do arduino
#include <SparkFun_MMA8452Q.h>
// Para mais informações, abrir exemplo da própria biblioteca

// declarar variavel para controlar o acelerometro
MMA8452Q accel;

void setup() {
  // Controlar servo no pino 2
  servo.attach(2);

  // inicializar módulo de acelerometro
  accel.init();
}

void loop() {
  // Se houver nova leitura de aceleração
  if (accel.available()) {
    // ler valores
    accel.read(); // atualiza accel.cx, cy, cz, etc

    // calcular intervalo de [0, 180] a partir
    // da aceleração que varia entre [-1, 1]
    int graus = (accel.cx + 1) * 90;
    servo.write(graus);
  }
}
