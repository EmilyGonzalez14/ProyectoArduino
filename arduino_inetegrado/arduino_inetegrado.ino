 #include <Stepper.h>
#include <Servo.h>

Servo servo_clasificador;
int ldr = A0;
int TRIG = 9;
int ECHO = 10;

const int PASOS_POR_REVOLUCION = 2048;
Stepper miMotor(PASOS_POR_REVOLUCION, 2, 4, 3, 5);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  servo_clasificador.attach(6);
  miMotor.setSpeed(15);  // Velocidad máxima recomendada

  servo_clasificador.write(90);
}

void loop() {
  // 1. Leer el sensor LDR
  int ValorLDR = analogRead(ldr);
  //Serial.println(ValorLDR);

  // 2. Disparar el sensor ultrasónico
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracion = pulseIn(ECHO, HIGH, 30000);  // Añadimos un timeout de 30ms para que no se congele si no hay eco
  float distancia = (duracion * 0.0343) / 2;

  // 3. Control del Motor Paso a Paso
  if (ValorLDR < 190) {
    // Subimos a 5 pasos por ciclo para que tenga fluidez y no vibre
    miMotor.step(5);
  } else {
    // Si es mayor o igual a 190, se detiene al instante
  }

  static unsigned long lastSend = 0;
  if (millis() - lastSend > 1000) {
    lastSend = millis();
    // 4. Control del servomotor basado en la distancia 
    if (distancia > 0 && distancia <= 5) {
      servo_clasificador.write(25);
      Serial.println("servo de 25 grados");
    }
    else if (distancia > 5 && distancia <= 10) {
      servo_clasificador.write(150);
      Serial.println("servo de 150 grados");
    }
    else {
      servo_clasificador.write(90);
    }
  }
}
