# **Energym: Academia Inteligente e Sustentável**

Energym é uma plataforma inovadora que une tecnologia, sustentabilidade e gamificação para transformar a experiência de treinar em academias. Nosso objetivo é promover o bem-estar físico dos usuários enquanto contribuímos para a redução da pegada ecológica.

## Como Funciona

- Utilizamos equipamentos inteligentes, como bicicletas ergométricas, que geram energia sustentável durante os treinos. Essa energia pode ser usada para carregar baterias ou alimentar dispositivos da própria academia, reduzindo a dependência de fontes não renováveis.
- Por meio de nosso aplicativo, os usuários podem registrar seus treinos e acompanhar a energia gerada. Cada pedalada vale pontos que podem ser trocados por prêmios, descontos e outros benefícios oferecidos por parceiros.

### Benefícios

- **Sustentabilidade:** Cada treino ajuda a reduzir o consumo de energia não renovável, contribuindo para um futuro mais sustentável.
- **Engajamento:** A gamificação motiva os usuários a se exercitarem regularmente, recompensando-os por seus esforços.
- **Bem-estar:** Incentivamos hábitos saudáveis, unindo saúde física e cuidado com o meio ambiente.

Energym é mais do que uma academia — é uma maneira inteligente e sustentável de transformar energia física em impacto positivo para o planeta.

### 🎥 **Vídeo da Solução**  
[Assista à apresentação](https://www.youtube.com/watch?v=wrTgmf4sM9Q)

### 📱 **Páginas da Solução (Mobile)**  
Algumas telas da aplicação mobile:  
![Páginas Energym](https://github.com/SamaraMoreira/Energym---IOT/blob/main/geral/PagApps.PNG)

### 🛠️ **Projeto no Simulador**  
Diagrama realizado no **Wokwi** para simulação da nossa solução:
![Diagrama](https://github.com/SamaraMoreira/Energym---IOT/blob/main/geral/diagrama.PNG)

### 📊 **Dashboard Node-Red**  
Visualize os dados gerados pela solução:  
![Dashboard Node-Red](https://github.com/SamaraMoreira/Energym---IOT/blob/main/geral/dashboard.PNG)

### 🔄 **Fluxo no Node-Red**  
Fluxo de dados implementado no **Node-Red**:  
![Fluxo Node-Red](https://drive.google.com/uc?id=1FuXiEM4zqZZxVn8x75avT2xfqD0OB3C1)

---
## **Sistema de Monitoramento e Controle com ESP32**

O projeto integra sensores, controle remoto e visualização de dados, com destaque para:

1. **Conexão Wi-Fi e MQTT:** Comunicação contínua com o broker MQTT para envio de dados e comandos.
2. **Monitoramento:** Sensores DHT22 verificam temperatura (>50°C) e umidade (>80%).
3. **Controle do Sistema:** Ativação/desativação remota via MQTT e botão físico; relé controla o carregador.
4. **Alertas:** Desativação do carregador, buzzer e LED vermelho indicam condições críticas.
5. **Cálculo da Carga:** Mede corrente e simula carga com base no tempo.
6. **Interface OLED e Dashboard:** Informações em tempo real no display e no Node-Red.
7. **Publicação de Dados:** Leituras enviadas via MQTT para integração com outros sistemas.
8. **Gestão de Estados:** Automatização do carregamento e alerta para carga completa.

Energym une saúde, tecnologia e sustentabilidade em uma experiência inovadora para o usuário e o planeta.
Com base no conteúdo do seu projeto, segue um exemplo de instruções detalhadas para o README.md para ajudar outros desenvolvedores a replicar e testar sua solução.

---

## 🛠️ Configuração do Ambiente

Siga os passos abaixo para configurar e testar este projeto.

### 1. Pré-requisitos
- [PlatformIO IDE](https://platformio.org/) instalado (pode ser usado com Visual Studio Code).
- Placa de desenvolvimento ESP32.
- Broker MQTT (como [test.mosquitto.org](https://test.mosquitto.org/)).
- Display OLED compatível com SSD1306.
- Sensor DHT22.
- Outros componentes (potenciômetro, relé, buzzer, LED).

### 2. Clonando o Projeto
Clone o repositório diretamente do GitHub:

```bash
git clone https://github.com/SamaraMoreira/Energym-IOT.git
cd Energym-IOT
```

### 3. Instalando Dependências
As dependências do projeto são gerenciadas automaticamente pelo PlatformIO. Certifique-se de que os seguintes pacotes estejam listados no arquivo `platformio.ini`:

```ini
lib_deps = 
	knolleary/PubSubClient@^2.8.0
	adafruit/Adafruit GFX Library@^1.11.11
	adafruit/Adafruit SSD1306@^2.5.13
	adafruit/DHT sensor library@^1.4.6
	adafruit/Adafruit Unified Sensor@^1.1.14
```

Ao abrir o projeto no PlatformIO, as bibliotecas serão baixadas automaticamente.

### 4. Configurando a Rede Wi-Fi e o Broker MQTT
Edite o arquivo principal (`src/esp32-http-server.ino`) para adicionar suas credenciais de Wi-Fi e as configurações do broker MQTT:

```cpp
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
```

### 5. Simulando no Wokwi
Este projeto pode ser simulado diretamente no [Wokwi](https://wokwi.com/). O arquivo de configuração `wokwi.toml` está incluído para compatibilidade. Basta abrir o projeto no Wokwi e iniciar a simulação.

### 6. Compilando
 Compile e faça o upload do firmware:

```bash
pio run --target upload
```

### 7. Testando o Projeto
1. Verifique no monitor serial (`PlatformIO > Monitor Serial`) as leituras e o status da conexão Wi-Fi.
2. Utilize um cliente MQTT (como MQTT Explorer) para enviar e receber mensagens nos tópicos definidos.
3. Monitore a exibição de dados no display OLED e os alertas sonoros/visuais.

### 8. Estrutura do Projeto

```plaintext
Energym-IOT
├── .vscode
│   └── extensions.json
├── geral
├── src
│   └── esp32-http-server.ino  # Código principal
├── .gitignore
├── diagram.json               # Arquivo do circuito
├── README.md                  # Instruções detalhadas
├── platformio.ini             # Configuração do PlatformIO
└── wokwi.toml                 # Configuração para simulação Wokwi
```

## **Configurações dos Nós Utilizados**

### 🌡️ Temperatura  
![Temperatura](https://drive.google.com/uc?id=1poM5-pc66Zi81XV6tQmacFnn0AEoiIb4)

### 💧 Umidade  
![Umidade](https://drive.google.com/uc?id=1X7Xjuo93W7bdkli6C-PT1_stxeG5QUDY)

### ⚡ Corrente  
![Corrente](https://drive.google.com/uc?id=1poM5-pc66Zi81XV6tQmacFnn0AEoiIb4)

### 🔋 Carga  
![Carga](https://drive.google.com/uc?id=107ATQOV7vKMgJ7CTCwUFcmznVXkyHpHS)

---
