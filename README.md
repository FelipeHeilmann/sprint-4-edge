## Integrantes:

1. Açucessa Macedo Mautane - RM 552568
2. Carlos Eduardo Caramante Ribeiro - RM 552159
3. Daniel Barbosa Mariano - RM 551171
4. Felipe Heilmann Marques - RM 551026
5. Felipe Voidela Toeldo - RM 98595

## Fresh Air

O Fresh Air é um sistema de monitoramento da qualidade do ar baseado em dispositivos IoT (Internet of Things) que permite aos usuários coletar e compartilhar dados sobre a qualidade do ar em diferentes locais. Este README fornecerá uma visão geral abrangente do projeto, incluindo sua arquitetura, recursos necessários, instruções de uso e outras informações relevantes.


## Visão geral

O Fresh Air é um sistema que integra dispositivos IoT baseados em Arduino para monitorar a qualidade do ar em tempo real. Ele permite que os usuários coletem dados sobre poluentes atmosféricos, temperatura, umidade e localização, criando uma base de dados centralizada. Os dados coletados são enviados para um servidor backend que os armazena em um banco de dados PostgreSQL. Além disso, os usuários têm a capacidade de relatar eventos específicos, como episódios de poluição grave, por meio da plataforma.

### As principais funcionalidades incluem:

1. Coleta de dados de sensores MQ-135 (poluentes do ar), NEO 6M (localização), DHT-11 (temperatura e umidade).
2. Conexão dos dispositivos Arduino à Internet por meio do sensor ESP-32.
3. Armazenamento centralizado de dados no servidor backend.
4. Aplicação web frontend para visualização e interação com os dados.
5. Aplicativo mobile para acessar os dados em movimento.
6. Capacidade de relatar incidentes de poluição e eventos relacionados.

## Arquitetura Proposta

### A arquitetura do sistema Fresh Air é composta pelos seguintes componentes:

1. Sensor MQ-135: Mede a quantidade de gases poluentes presentes no ar.
2. Sensor NEO 6M: Fornece informações de localização com base em satélites.
3. Sensor DHT-11: Mede a temperatura e umidade do ar.
4. Sensor ESP-32: Facilita a conexão dos dispositivos Arduino à Internet para envio de dados à API.

### Backend
1. Tecnologia: Node.js com TypeScript.
2. Banco de Dados: PostgreSQL para armazenar os dados coletados.
3. API: Backend fornece uma API para receber dados dos dispositivos IoT e aplicativos.

### Frontend
1. Web Frontend: Desenvolvido com React, TypeScript e Tailwind CSS.
2. Mobile App: Criado usando React Native, TypeScript e Tailwind CSS.

## Imagens da arquitetura

1. Circuito completo

<img src="./circuito.jpg">

Para melhor identificação, fotos dos componentes isolados

1. DHT 11

<img src="./dht11.png">

2. LDR

<img src="./ldr.png">

3.ESP32

<img src="./esp32.png">

### Requisitos Funcionais

1. O usuário comum deve ser capaz de realizar um cadastro, enviando informações como: nome, email e senha.

2. O usuário deve ser capaz de se autenticar na plataforma e ter acesso aos recursos disponíveis para seu nível de acesso.

3. O usuário deve ser capaz de visualizar informações como: umidade, temperatura, quantidade de gases poluentes como: amônia, enxofre etc.

4. O usuário deve ser capaz de visualizar recomendações sobre as melhores atitudes diante da qualidade do ar aferida.

5. O usuário deve ser capaz de reportar um foco de poluição em uma determinada região.

6. O usuário deve ser capaz de visualizar um reporte feito por outro usuário. 

7. O usuário deve ser capaz de acessar um SAC e fazer um reporte de alguma dúvida ou melhoria da aplicação.

8. O sistema deve calcular a qualidade do ar baseado nas informações oriundas dos Arduinos e fazer previsões ao longo tempo.

### Requisitos não funcional

1. A aplicação deve ter uma fácil usabilidade, facilitando a compreensão dos usuários, envio e visualização das informações.

2. A aplicação deve ser capaz de escalar verticalmente e horizontalmente, para atender, assim as demandas dos usuários.

### Regras de negócio

1. As autoridades devem fazer cadastro passando informações como: nome, email, cnpj e senha.
O Cadastro será validado para confirmar a existência da autoridade.

2. Apenas as autoridades podem aprovar um reporte feito por um usuário.

3. Apenas as autoridades podem acessar e mudar o status de um reporte.

4. Apenas as autoridades podem compartilhar informações sobre o ar para garantir a veracidade das informações.

5. A aplicação deve se basear na localização do dispositivo do usuário para mostrar as informações sobre a qualidade do ar.

### Requisitos técnicos

1. O sistema deverá rodar tanto em celulares Android como em IOS, além de prever versão Web, para operação por browser

2. O Arduino deve se comunicar com a api via protocolo http, para assim enviar os dados para o backend. 
O frontend deve buscar informações do servidor via api e no protocolo HTTP.

## Para fazer funcionar

1. Precisa baixar as bibliotecas: Arduino Json, DHT11 e Ardafruit Sensor.

--- Link do Ardafruit: https://github.com/adafruit/Adafruit_Sensor

--- link do DTH11: https://github.com/adafruit/DHT-sensor-library 

### É importante relembrar que na simualção, utilizamos o sensor LDR para simular o sensor MQ-135. Também não dispusemos do sensor NEO 6M