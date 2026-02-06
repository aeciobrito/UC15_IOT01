#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>

// --- CONFIGURAÇÃO DE REDE ---
const char* ssid = "TP-LINK_9FE0E6";
const char* hostname = "esp32-aecio";

// --- CONFIGURAÇÃO DHT ---
#define DHTPIN 4
#define DHTTYPE DHT22 // ou, DHT11
DHT dht(DHTPIN, DHTTYPE);

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // -- INICIA DHT --
  dht.begin();

  // -- CONEXÃO DE REDE --
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print("."); // enquanto não conecta, mostra pontos
    delay(500); // da um tempo para tentar novamente
  }

  Serial.println("\n Wi-Fi Conectado!");

  if(MDNS.begin(hostname)) {
    Serial.println("mDNS inciado! Acesse: http://esp32-aecio.local");
  }

  // -- CONFIG DE API --
  server.on("/api/hello", []() {
    server.send(200, "application/json", R"raw(
      {
        "mensagem": "Ola, IOT01"
      }
    )raw");
  });

  server.on("/api/sensores", []() {
    float umdLida = dht.readHumidity();
    float tmpLida = dht.readTemperature();
    
    // tratamento de erro de leitura

    // tratamento de dados lidos com sucesso
    server.send(200, "application/json", R"raw(
      {
        "temperatura": "30",
        "umidade": "20%"
      }
    )raw");
  });

  server.on("/", []() {
    server.send(200, "text/plain", "API Online. Acesse /api/hello");
  });

  server.begin();
  Serial.println("Servidor inciado.");
  Serial.print("Acese em http://");
  Serial.print(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
