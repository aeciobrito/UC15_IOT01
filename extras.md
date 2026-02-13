# Guia de Referência Rápida: Arduino Uno vs. ESP32 DevKitC

Este documento é um guia de consulta rápida para alunos que estão migrando do universo do Arduino Uno para o ESP32. O objetivo é esclarecer as principais diferenças de hardware e programação para facilitar os exercícios e projetos.

---

## 1. Visão Geral: O que muda do Arduino para o ESP32?

Pense no **Arduino Uno** como uma calculadora confiável: ele é excelente para tarefas simples e diretas, como ler um sensor e acender um LED. Ele é um **microcontrolador**.

O **ESP32**, por outro lado, é como um smartphone: ele tem um processador muito mais potente (dual-core), memória de sobra e, o mais importante, **Wi-Fi e Bluetooth integrados**. Ele é um **SoC (System on a Chip)**, um "computador em um chip".

| Característica       | Arduino Uno                              | ESP32 DevKitC                                      |
| -------------------- | ---------------------------------------- | -------------------------------------------------- |
| **Tipo**             | Microcontrolador                         | System on a Chip (SoC)                             |
| **Processador**      | 8-bit, 16 MHz, Single-Core               | 32-bit, 160-240 MHz, Dual-Core                     |
| **Tensão de Operação** | **5V**                                   | **3.3V** (CUIDADO!)                                |
| **Conectividade**    | Nenhuma                                  | Wi-Fi e Bluetooth/BLE                              |
| **Pinos I/O**        | Fixos (Digital, Analógico, PWM)          | Multifuncionais (quase todos podem ser tudo)       |
| **Complexidade**     | Simples, ideal para iniciar              | Mais complexo, mas muito mais poderoso             |

> **Ponto Crítico:** A maior diferença no dia-a-dia é a **tensão de operação**. O Arduino trabalha com 5V, enquanto o ESP32 trabalha com **3.3V**. Conectar um sensor de 5V diretamente em um pino do ESP32 pode danificá-lo! Sempre use divisores de tensão ou conversores de nível lógico se precisar conectar dispositivos 5V.

---

## 2. Mapa de Pinos (Pinout): Onde Conectar as Coisas?

Diferente do Arduino, onde os pinos têm funções fixas, no ESP32 a maioria dos pinos (chamados de **GPIO** - General Purpose Input/Output) são flexíveis.

### Arduino Uno (Referência)

- **Pinos Digitais:** `0` a `13`.
- **Pinos com PWM (`~`):** `3, 5, 6, 9, 10, 11`. Usados com `analogWrite()`.
- **Pinos de Leitura Analógica:** `A0` a `A5`. Usados com `analogRead()`.
- **Comunicação Serial:** `0` (RX) e `1` (TX). Bloqueiam o upload se usados.

### ESP32 DevKitC (O que usamos)

O ESP32 não tem uma separação tão rígida. Quase todo pino pode ser configurado como entrada, saída, analógico, etc.

- **Pinos Seguros para Uso Geral:**
  - `GPIO4`, `GPIO12` a `GPIO19`, `GPIO21` a `GPIO23`, `GPIO25` a `GPIO27`, `GPIO32`, `GPIO33`.
  - Estes são ótimos candidatos para LEDs, botões e a maioria dos sensores.

- **Pinos de Comunicação Serial Padrão:**
  - `GPIO1` (TX) e `GPIO3` (RX). São usados para a comunicação com o computador (`Serial.println()`). Evite usá-los para outras coisas se você precisa depurar seu código.

- **LED Interno:**
  - Na maioria das placas ESP32 DevKitC, o LED azul fica no `GPIO2`.

---

## 3. Pinos do ESP32 que Merecem Atenção (ou devem ser evitados)

Certos pinos do ESP32 têm funções especiais durante o boot ou possuem limitações. Usá-los de forma inadequada pode fazer com que o ESP32 não inicie ou se comporte de maneira estranha.

- ### Pinos "Strapping" (Modo de Boot)
  - **Pinos:** `GPIO0`, `GPIO2`, `GPIO5`, `GPIO12`.
  - **Problema:** O estado desses pinos (HIGH ou LOW) durante a inicialização define o modo de boot do ESP32 (ex: modo de gravação ou modo de execução). Se você conectar um sensor que puxe o `GPIO0` para HIGH, por exemplo, talvez não consiga mais gravar código nele.
  - **Solução:** Evite usar esses pinos se possível. Se precisar usá-los, garanta que nada conectado a eles force um estado específico durante o boot. `GPIO2` é geralmente seguro, pois seu estado "normal" é o de boot.

- ### Pinos "Somente Entrada" (Input-Only)
  - **Pinos:** `GPIO34`, `GPIO35`, `GPIO36`, `GPIO39`.
  - **Problema:** Estes pinos não podem ser configurados como `OUTPUT`. Você só pode ler dados deles (`digitalRead` ou `analogRead`). Além disso, eles não possuem resistores internos de pull-up ou pull-down.
  - **Solução:** Use-os para sensores que só enviam dados, como um sensor PIR ou um LDR. Para botões, você precisará de um resistor de pull-up/pull-down externo.

- ### Pinos Ligados à Memória Flash Interna
  - **Pinos:** `GPIO6` a `GPIO11`.
  - **Problema:** Estes pinos são usados internamente para comunicação com a memória flash onde seu código está armazenado.
  - **Solução:** **NUNCA USE ESTES PINOS.**

- ### ADC2 e Wi-Fi
  - **Pinos com ADC2:** `GPIO4`, `GPIO0`, `GPIO2`, `GPIO15`, `GPIO13`, `GPIO12`, `GPIO14`, `GPIO27`, `GPIO25`, `GPIO26`.
  - **Problema:** O conversor analógico-digital 2 (**ADC2**) é desativado quando o Wi-Fi está em uso. Se você tentar fazer um `analogRead()` em um pino do ADC2 enquanto o Wi-Fi estiver ativo, a leitura irá falhar ou retornar valores inconsistentes.
  - **Solução:** Para leituras analógicas em projetos com Wi-Fi, **dê preferência aos pinos do ADC1**: `GPIO32`, `GPIO33`, `GPIO34`, `GPIO35`, `GPIO36`, `GPIO39`.

---

## 4. Sinal Digital vs. Analógico: Revisão e Diferenças

### Leitura/Escrita Digital (`digitalRead`/`digitalWrite`)

| Placa       | Nível Lógico | Função de Pull-up                             |
| ----------- | ------------ | --------------------------------------------- |
| Arduino Uno | 5V           | `pinMode(pino, INPUT_PULLUP);`                 |
| ESP32       | **3.3V**     | `pinMode(pino, INPUT_PULLUP);` (ou `INPUT_PULLDOWN`) |

O conceito é o mesmo, mas a tensão é diferente. O ESP32 também oferece `INPUT_PULLDOWN`, que é útil em algumas situações.

### Leitura Analógica (`analogRead`)

- **Arduino Uno:**
  - `analogRead(A0);`
  - Retorna um valor entre **0 e 1023** (resolução de 10 bits).
- **ESP32:**
  - `analogRead(34);`
  - Retorna um valor entre **0 e 4095** (resolução de 12 bits). Mais precisão!
  - Lembre-se da restrição do ADC2 com Wi-Fi.

### Escrita "Analógica" (PWM - Pulse Width Modulation)

PWM é a técnica para simular uma saída de tensão analógica, como para controlar o brilho de um LED ou a velocidade de um motor.

- **Arduino Uno:**
  - `analogWrite(pino, valor);`
  - O `valor` vai de **0 (0%) a 255 (100%)**.
  - Funciona apenas nos pinos com `~`.
- **ESP32:**
  - A forma "compatível" com o Arduino `analogWrite(pino, valor);` também funciona, mas a forma nativa e mais poderosa é usando o periférico **LEDC**.
  - O sistema LEDC permite configurar a frequência e a resolução do PWM, e você pode "anexar" o PWM a quase qualquer pino. Para simplificar, podemos usar `analogWrite` nos projetos iniciais, que funciona de forma similar ao do Arduino (valor 0-255).
