#define LED_EXTERNO 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_EXTERNO, OUTPUT);

  Serial.println("Digite 'ligar' ou 'desligar':");
}

void loop() {
  if(Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toLowerCase();

    if(comando == "ligar") {
      // liga o led
      digitalWrite(LED_EXTERNO, HIGH);
    } else if (comando == "desligar") {
      // desliga o led
      digitalWrite(LED_EXTERNO, LOW);
    } else {
      // comando incorreto
      Serial.print("Comando incorreto, digite 'ligar' ou 'desligar'");
      piscarLed(8, 1000, 500, "Tente novamente");
    }
  }
}

void piscarLed(int vezes, int tempoLigado, int tempoDesligado, String mensagem) {
  for(int i = 0; i < vezes; i++) {
    digitalWrite(LED_EXTERNO, HIGH);
    delay(tempoLigado);
    digitalWrite(LED_EXTERNO, LOW);
    delay(tempoDesligado);
  }
  Serial.println(mensagem);
}
