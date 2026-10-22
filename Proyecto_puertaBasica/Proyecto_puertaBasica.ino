#include <Servo.h>

Servo miServo;       
const int pinLDR = A0; 
const int umbralLuz = 2; 

void setup() {
  miServo.attach(9);  
  Serial.begin(9600); 
  miServo.write(0);   
}

void loop() {
  int valorLDR = analogRead(pinLDR); 
  
  Serial.print("Valor LDR: ");
  Serial.println(valorLDR);

  if (valorLDR < umbralLuz) {
    miServo.write(90); 
    delay(1000);       
  } else {
    miServo.write(0); 
    delay(1000);
  }
  
  delay(500); 
}
