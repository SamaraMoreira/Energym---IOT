#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Definições WiFi e MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

// Instâncias de cliente WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Definições do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Definições de pinos
const int potPin = 34;
const int relayPin = 26;
const int ledVerdePin = 18;
const int ledVermelhoPin = 23;
const int buzzerPin = 32;
const int buttonPin = 33;

#define DHTPIN 15  // O pino de conexão do DHT22 no ESP32
#define DHTTYPE DHT22  // Tipo de sensor DHT

// Instanciação do sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variáveis de controle
float corrente = 0.0;
float temperatura = 0.0;
float carga = 0.0;
const float capacidadeTotal = 50.0;
bool carregando = true;
bool alarmeAtivo = false;
bool temperaturaCritica = false;
bool estadoBotaoAnterior = HIGH;
bool sistemaAtivo = true;
bool cargaCompleta = false;
unsigned long tempoAnterior = 0;

// Função de reconexão com MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("", mqttUser, mqttPassword)) {
      Serial.println("Conectado ao MQTT.");
      client.subscribe("carregador/controlar");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

// Função de callback para mensagens MQTT
void callback(char* topic, byte* message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  if (String(topic) == "carregador/controlar") {
    if (messageTemp == "ON") {
      sistemaAtivo = true;
      digitalWrite(relayPin, HIGH);
      digitalWrite(ledVerdePin, HIGH);
      Serial.println("Sistema ativado via MQTT.");
    } else if (messageTemp == "OFF") {
      sistemaAtivo = false;
      digitalWrite(relayPin, LOW);
      digitalWrite(ledVerdePin, LOW);
      digitalWrite(ledVermelhoPin, LOW);
      noTone(buzzerPin);
      Serial.println("Sistema desativado via MQTT.");
    }
  }
}

void setup() {
  // Configura os pinos de saída
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicializa comunicação serial e display OLED
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha na inicialização do display OLED"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Conecta ao Wi-Fi
  Serial.println("Conectando-se à rede Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Configura o servidor MQTT e a função de callback
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Inicializa o sistema com relé e LED verde acesos
  digitalWrite(relayPin, HIGH);
  digitalWrite(ledVerdePin, HIGH);
  Serial.println("Sistema Iniciado.");

  // Inicializa o sensor DHT
  dht.begin();
}

float umidade = 0.0;
bool umidadeCritica = false;

#define UMIDADE_CRITICA 80.0 // Defina o valor de umidade crítica, ex: 80%

// Função de loop
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura do estado do botão
  bool estadoBotaoAtual = digitalRead(buttonPin);

  if (estadoBotaoAnterior == HIGH && estadoBotaoAtual == LOW) {
    sistemaAtivo = !sistemaAtivo;
    if (sistemaAtivo && !cargaCompleta) {
      Serial.println("Sistema reativado pelo usuário.");
    } else {
      Serial.println("Sistema interrompido pelo usuário.");
      digitalWrite(relayPin, LOW);
      digitalWrite(ledVerdePin, LOW);
      digitalWrite(ledVermelhoPin, LOW);
      noTone(buzzerPin);
    }
  }
  estadoBotaoAnterior = estadoBotaoAtual;

  // Leitura da temperatura
  temperatura = dht.readTemperature(); // Leitura da temperatura em °C

  if (isnan(temperatura)) {  // Verifica se a leitura falhou
    Serial.println("Falha na leitura do sensor DHT!");
    return;
  }

  // Leitura da umidade
  umidade = dht.readHumidity(); // Leitura da umidade em %

  if (isnan(umidade)) {  // Verifica se a leitura falhou
    Serial.println("Falha na leitura do sensor DHT!");
    return;
  }

  Serial.print("Temperatura Atual: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade Atual: ");
  Serial.print(umidade);
  Serial.println(" %");

  // Verifica se a temperatura é crítica
  if (temperatura > 50) {
    temperaturaCritica = true;
  } else {
    temperaturaCritica = false;
  }

  // Verifica se a umidade é crítica
  if (umidade > UMIDADE_CRITICA) {
    umidadeCritica = true;
  } else {
    umidadeCritica = false;
  }

  // Envio da temperatura via MQTT
  char tempString[8];
  dtostrf(temperatura, 6, 2, tempString);
  client.publish("carregador/temperatura", tempString);

  // Envio da umidade via MQTT
  char umidadeString[8];
  dtostrf(umidade, 6, 2, umidadeString);
  client.publish("carregador/umidade", umidadeString);

  // Ação em caso de temperatura crítica
  if (temperaturaCritica) {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledVermelhoPin, HIGH);
    corrente = 0;

    if (!alarmeAtivo) {
      tone(buzzerPin, 1000); // Ativa o buzzer
      alarmeAtivo = true;
    }
    Serial.println("Alerta! Temperatura crítica! Carregamento interrompido.");
  } 
  // Ação em caso de umidade crítica
  else if (umidadeCritica) {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledVermelhoPin, HIGH);
    corrente = 0;

    if (!alarmeAtivo) {
      tone(buzzerPin, 1000); // Ativa o buzzer
      alarmeAtivo = true;
    }
    Serial.println("Alerta! Umidade crítica! Carregamento interrompido.");
  }
  // Sistema ativo e não carga completa
  else if (sistemaAtivo && !cargaCompleta) {
    digitalWrite(ledVerdePin, HIGH);
    digitalWrite(ledVermelhoPin, LOW);
    noTone(buzzerPin);
    alarmeAtivo = false;

    // Leitura da corrente
    int valorConsumo = analogRead(potPin);
    corrente = valorConsumo * (200.0 / 4095.0);
    Serial.print("Corrente Atual: ");
    Serial.print(corrente, 2);
    Serial.println(" A");

    // Envio da corrente via MQTT
    char correnteString[8];
    dtostrf(corrente, 6, 2, correnteString);
    client.publish("carregador/corrente", correnteString);

    // Cálculo da carga
    unsigned long tempoAtual = millis();
    float deltaHoras = (tempoAtual - tempoAnterior) / 3600000.0;
    carga += corrente * deltaHoras * (100.0 / capacidadeTotal);
    if (carga >= 100.0) {
      carga = 100.0;
      cargaCompleta = true;
      corrente = 0;
      Serial.println("Carga Completa! Carregamento finalizado.");
      digitalWrite(relayPin, LOW);
    }
    tempoAnterior = tempoAtual;

    Serial.print("Carga Atual: ");
    Serial.print(carga, 2);
    Serial.println(" %");

    // Envio da carga via MQTT
    char cargaString[8];
    dtostrf(carga, 6, 2, cargaString);
    client.publish("carregador/carga", cargaString);
  }

  // Atualização do display OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperatura);
  display.println(" C");
  display.print("Umid: ");
  display.print(umidade);
  display.println(" %");
  display.print("Carga: ");
  display.print(carga);
  display.println(" %");
  display.print("Corrente: ");
  display.print(corrente);
  display.println(" A");
  display.display();

  delay(1000); // Atraso de 1 segundo
}