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
