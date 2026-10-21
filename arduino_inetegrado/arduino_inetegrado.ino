  #include <Stepper.h>
  int ldr = A0;

  // El motor 28BYJ-48 suele requerir 2048 pasos para completar una vuelta completa (360°)
  const int PASOS_POR_REVOLUCION = 2048;

  // OJO CON EL ORDEN DE PINES: Para este motor en específico el orden correcto es (IN1, IN3, IN2, IN4)
  Stepper miMotor(PASOS_POR_REVOLUCION, 2, 4, 3, 5);

  void setup() {
    Serial.begin(9600);
    // Ajusta la velocidad en RPM (Revoluciones por minuto).
    // Rango recomendado para 28BYJ-48: entre 5 y 15 RPM.
    miMotor.setSpeed(10);
  }

  void loop() {
    int ValorLDR = analogRead(ldr);
    Serial.println(ValorLDR);
    if (ValorLDR > 190) {

    } else {
      // Dar una vuelta completa en sentido horario
     miMotor.step(1);
    }
  }