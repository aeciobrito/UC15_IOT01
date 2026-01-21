int segundos = 45;
int minutos = 59;
int horas = 23;

void setup() {
  // Inicia a comunicação serial
  Serial.begin(115200);
  Serial.println("ESP32 Iniciado com sucesso");
}

void loop() {
  Serial.print(horas);
  Serial.print(":");
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos); // pula linha

  segundos++; // aumenta 1 segundo

  if(segundos == 60)
  {
    minutos++;
    segundos = 0;
  }

  if(minutos == 60)
  {
    horas++;
    minutos = 0;
  }

  if(horas == 24)
  {
    horas = 0;
  }

  delay(1000);// aguarda 0,1 segundo
}
