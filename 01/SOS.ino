#define PORTA_LED 5

void setup() {
  pinMode(PORTA_LED, OUTPUT);
  digitalWrite(PORTA_LED, LOW); 
}

// CRIE UM SINAL DE S.O.S
// (...---...)
void loop() {
  // 3x rápido
  for(int i = 0; i < 3; i++) {
    // 3x rápido
    digitalWrite(PORTA_LED, HIGH);
    delay(300);

    digitalWrite(PORTA_LED, LOW);
    delay(200);
  } 

  // 3x lento
  for(int i=0; i<3; i++) {
    digitalWrite(PORTA_LED, HIGH);
    delay(1300);

    digitalWrite(PORTA_LED, LOW);
    delay(300);
  }

  // 3x rápido
  for(int i = 0; i < 3; i++) {
    // 3x rápido
    digitalWrite(PORTA_LED, HIGH);
    delay(300);

    digitalWrite(PORTA_LED, LOW);
    delay(200);
  } 

  // pusa para o próximo loop
  delay(1000);
}
