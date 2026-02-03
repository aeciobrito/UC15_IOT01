#include <WiFi.h>
#include <WebServer.h>

// Definir nome e senha da rede
const char* ssid = "ESP32_AULA_X";
const char* password = "12345678"; // Mínimo 8 caracteres

WebServer server(80);

const char paginaHTML[] = R"rawliteral(<h1>Hello World</h1><p>Operando no modo ACCESS POINT (Roteador)</p>")rawliteral";

void setup() {
  Serial.begin(115200);

  // 1. Define o modo como ACCESS POINT
  WiFi.mode(WIFI_AP);

  // 2. Configura a rede (Cria o sinal Wi-Fi)
  // softAP(Nome, Senha)
  Serial.println("Criando a rede Wi-Fi...");
  WiFi.softAP(ssid, password);

  // 3. Mostra o IP do próprio ESP32 (Geralmente 192.168.4.1)
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Rede criada! Conecte-se em: ");
  Serial.println(ssid);
  Serial.print("Depois acesse: http://");
  Serial.println(IP);

  // Configura a rota do servidor
  server.on("/", []() {
    server.send(200, "text/html", paginaHTML);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}