const int S0 = 4;
const int S1 = 5;
const int S2 = 6;
const int S3 = 7;
const int sensorOut = 8;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Configuramos la escala de frecuencia al 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600);
}

void loop() {
  // 1. Leer ROJO
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int r = pulseIn(sensorOut, LOW);
  delay(30);

  // 2. Leer VERDE
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int g = pulseIn(sensorOut, LOW);
  delay(30);

  // 3. Leer AZUL
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int b = pulseIn(sensorOut, LOW);
  delay(30);

  // --- LÓGICA DE DETECCIÓN DE PRODUCTOS ---

  // Si los tres valores son muy altos, no hay objeto cerca
  if (r > 270 && g > 270 && b > 270) {
    Serial.println("Esperando producto...");
  }
  // NEGRO (Café Gourmet): Valores altos y parejos
  else if (r > 150 && g > 150 && b > 150 && abs(r - g) < 30 && abs(g - b) < 30) {
    Serial.println("Producto detectado: Café Gourmet (Negro)");
  }
  // AMARILLO (Cereal de Maíz): Rojo y Verde bajos y parecidos, Azul alto
  else if (r < g && abs(r - g) < 40 && b > r + 30) {
    Serial.println("Producto detectado: Cereal de Maíz (Amarillo)");
  }
  // FUCSIA (Gelatina de Fresa): Rojo muy bajo, Azul bajo, Verde alto
  else if (r < 110 && b < 140 && g > r + 40) {
    Serial.println("Producto detectado: Gelatina de Fresa (Fucsia)");
  }
  // MORADO (Jugo de Uva): Rojo y Azul bajos y cercanos, Verde alto
  else if (r < b && abs(r - b) < 40 && g > r + 30) {
    Serial.println("Producto detectado: Jugo de Uva (Morado)");
  }
  // NARANJA (Galletas de Naranja): Rojo muy bajo, Verde intermedio, Azul alto
  else if (r < g && g < b && (g - r) > 20) {
    Serial.println("Producto detectado: Galletas de Naranja (Naranja)");
  }
  // ROJO (Salsa de Tomate): El rojo es el menor de los tres
  else if (r < g && r < b) {
    Serial.println("Producto detectado: Salsa de Tomate (Rojo)");
  }
  // VERDE (Té Verde): El verde es el menor de los tres
  else if (g < r && g < b) {
    Serial.println("Producto detectado: Té Verde (Verde)");
  }
  // AZUL (Jabón Líquido): El azul es el menor de los tres
  else if (b < r && b < g) {
    Serial.println("Producto detectado: Jabón Líquido (Azul)");
  } 
  else {
    Serial.println("Producto detectado: Objeto genérico / Indefinido");
  }

  delay(400);
}