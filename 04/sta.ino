#include <WiFi.h>
#include <WebServer.h>

// Substitua pelos dados do roteador
const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_REDE";

WebServer server(80); // Cria o servidor na porta padrão 80

// Conteúdo da página
const char paginaHTML[] = R"rawliteral(<h1>Hello World</h1><p>Operando no modo STATION (Cliente)</p>")rawliteral";

void setup() {
  Serial.begin(115200);

  // 1. Define o modo como STATION (Cliente)
  WiFi.mode(WIFI_STA);
  
  // 2. Inicia a conexão
  Serial.print("Conectando em: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 3. Loop de espera (enquanto não conectar, fica imprimindo pontos)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // 4. Sucesso! Mostra o IP que o roteador "emprestou" para o ESP32
  Serial.println("");
  Serial.println("Conectado!");
  Serial.print("Acesse pelo navegador: http://");
  Serial.println(WiFi.localIP());

  // Configura a rota do servidor
  server.on("/", []() {
    server.send(200, "text/html", paginaHTML);
  });
  
  server.begin();
}

void loop() {
  server.handleClient(); // Mantém o servidor escutando
}