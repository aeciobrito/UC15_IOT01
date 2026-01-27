#define BOTAO 12
#define LED_AZUL 4
#define PIR 13

bool alarmeDisparado = false;
long ultimoTempoPisca = 0;  // Última vez que olhei o relógio
const long intervalo = 150; // Intervalo de 'piscagem'
int estadoLed = LOW;        // Alterar o estado do LED

void setup() {
  Serial.begin(115200);

  pinMode(BOTAO, INPUT);
  pinMode(LED_AZUL, OUTPUT);
  digitalWrite(LED_AZUL, LOW); // COMEÇA DESLIGADO
  pinMode(PIR, INPUT);

  Serial.println("Sistema de Alarme com Reset por Botao - Iniciado");
  Serial.println("Aguarde a estabilização do sensor PIR...");
  delay(5000);
  Serial.println("Sistema Pronto para Uso.");
}

void loop() {
  // Se o alarme não estiver disparado, verifica se há movimento
  if(!alarmeDisparado) {
    int estadoPir = digitalRead(PIR);
    if(estadoPir == HIGH) { // tendo movimento
      Serial.println("ALERTA: Movimento Detectado!");
      alarmeDisparado = true;
    }
  }

  // Se o alarme estiver disparado, fica piscando e verifica botão de reset
  if(alarmeDisparado) {
    piscaLed();
    verificarBotao();
  }

  if(Serial.available() > 0) {
    String senha = Serial.readStringUntil('\n');
    senha.trim();

    if(senha == "SENAC") {
      desligarAlarme();
    } else {
      Serial.print("Senha incorreta!");
    }
  }
}

void desligarAlarme() {
  alarmeDisparado = false;
  Serial.println("Sistema interrompido pelo usuario! Aguarde 6 segundos");
  digitalWrite(LED_AZUL, LOW);
  delay(6000);
  Serial.println("Sistema em operacao novamente!");
}

void verificarBotao() {
  int estadoBotao = digitalRead(BOTAO);
  if(estadoBotao == HIGH) {
    desligarAlarme();
  }
}

void piscaLed() {
  long tempoAtual = millis();

  if(tempoAtual - ultimoTempoPisca >= intervalo) {

    ultimoTempoPisca = tempoAtual;

    if(estadoLed == LOW) {
      estadoLed = HIGH;
    } else {
      estadoLed = LOW;
    }
    digitalWrite(LED_AZUL, estadoLed);
  }
}