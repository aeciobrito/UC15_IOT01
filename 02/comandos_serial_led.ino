#define LED_ROXO 4

void setup() {  
  Serial.begin(115200);
  pinMode(LED_ROXO, OUTPUT);
  digitalWrite(LED_ROXO, HIGH);
  Serial.println("Digite 'L' para Ligar e 'D' para Desligare 'P' para piscar");
}

void loop() {
  // Veriica se há dados chengado no PC
  if(Serial.available() > 0) {
    // Lê 1 caractere recebido
    char comando = Serial.read();

    if(comando == 'L' || comando == 'l')
    {
      // ligar
      digitalWrite(LED_ROXO, HIGH);
      Serial.println("Comando recebido: LED Ligado");
    }
    else if (comando == 'D' || comando == 'd')
    {
      // desligar
      digitalWrite(LED_ROXO, LOW);
      Serial.println("Comando recebido: LED Desligado");
    }
    else if (comando == 'P' || comando == 'p')
    {
      Serial.println("Comando recebido: LED Piscando");
      for(int i = 0; i < 10; i++)
      {
        digitalWrite(LED_ROXO, HIGH);
        delay(400);
        digitalWrite(LED_ROXO, LOW);
        delay(200);
      }
      
      Serial.println("Comando encerrado: LED Desligado");
    }
    else
    {
      Serial.print("Comando '");
      Serial.print(comando);
      Serial.println("' não reconhecido!");
    }
    // Ignora caracteres direfentes
  }

  delay(20);
}
