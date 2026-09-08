# 🐉 Dragão do Shrek — Projeto Arduino

<p align="center">
  <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white">
  <img src="https://img.shields.io/badge/C%2FC%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white">
  <img src="https://img.shields.io/badge/Servo%20Motor-3D3D3D?style=for-the-badge">
  <img src="https://img.shields.io/badge/Ultrass%C3%B4nico-Sensor-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/Oficina%20da%20Toledo-Educa%C3%A7%C3%A3o-blue?style=for-the-badge">
</p>

<p align="center">
  <b>Projeto de automação e robótica desenvolvido na Oficina da Toledo.</b>
</p>

---

## 🐲 Sobre o projeto

Este projeto consiste na construção e programação de um **dragão animatrônico inspirado no Dragão do Shrek**, utilizando Arduino, servomotores e sensores ultrassônicos.

A estrutura do dragão possui movimentos controlados eletronicamente, permitindo criar uma interação com o público.

O sistema utiliza **dois sensores ultrassônicos** para detectar a aproximação de uma pessoa ou objeto. A partir dessas detecções, diferentes servomotores são acionados para movimentar partes do dragão.

O projeto foi desenvolvido dentro de uma proposta prática de **programação, eletrônica e robótica**, permitindo que os estudantes tenham contato com a construção de um sistema automatizado.

---

# 🎯 Objetivo

O objetivo do projeto é criar uma estrutura robótica capaz de realizar movimentos de forma automática a partir da detecção de objetos ou pessoas.

O dragão possui duas etapas principais de interação:

### 🟢 Primeira etapa — Sensor esquerdo

Quando o sensor esquerdo detecta algo a menos de **35 cm**, são acionados movimentos relacionados à primeira parte da animação.

### 🔵 Segunda etapa — Sensor direito

Após a primeira etapa ser executada, o sensor direito passa a controlar a segunda parte da sequência.

Dessa maneira, o dragão realiza uma sequência de movimentos conforme o visitante interage com diferentes regiões da estrutura.

---

# 🧑‍🎓 Projeto educacional

Além de ser uma instalação robótica, o projeto pode ser utilizado como uma atividade prática para estudantes.

Durante o desenvolvimento, são trabalhados conceitos de:

* 🤖 Robótica;
* 💻 Programação;
* ⚡ Eletrônica;
* 📡 Sensores ultrassônicos;
* 🔄 Servomotores;
* 📏 Medição de distância;
* 🧠 Lógica de programação;
* ⏱️ Temporização;
* 🔌 Entradas e saídas digitais;
* 🛠️ Montagem e prototipagem.

A proposta permite que os alunos compreendam como **sensores podem ser utilizados para controlar movimentos mecânicos**.

---

# 🧰 Componentes

* Arduino
* 4 × Servomotores
* 2 × Sensores ultrassônicos
* 1 × Botão
* Estrutura mecânica do dragão
* Cabos jumper
* Fonte de alimentação adequada
* Peças mecânicas para asas, cabeça e demais partes móveis

---

# ⚙️ Servomotores

O projeto utiliza quatro servomotores:

| Motor                | Pino | Função                              |
| -------------------- | ---: | ----------------------------------- |
| Motor baixo esquerdo |    8 | Movimento da estrutura/asa esquerda |
| Motor cima esquerdo  |   10 | Movimento superior esquerdo         |
| Motor cima direito   |    9 | Movimento superior direito          |
| Motor baixo direito  |   11 | Movimento da estrutura/asa direita  |

Os servomotores são controlados através da biblioteca:

```cpp
#include <Servo.h>
```

---

# 📡 Sensores ultrassônicos

O dragão utiliza dois sensores ultrassônicos para detectar a aproximação.

## Sensor esquerdo

| Função  | Pino |
| ------- | ---: |
| Trigger |    2 |
| Echo    |    3 |

## Sensor direito

| Função  | Pino |
| ------- | ---: |
| Trigger |    6 |
| Echo    |    7 |

A distância é calculada através do tempo de retorno do sinal ultrassônico.

A função responsável pela medição é:

```cpp
float lerDistanciaCM(int trigPin, int echoPin)
```

---

# 📏 Distância de ativação

O limite utilizado pelo projeto é:

```cpp
const float limiteDistancia = 35.0;
```

Isso significa que um sensor é considerado ativado quando identifica um objeto a uma distância inferior a **35 cm**.

```text
Objeto
  │
  │
  │  < 35 cm
  ▼
[ SENSOR ]
     │
     ▼
Aciona os movimentos
```

---

# 🔘 Botão de início

Antes de iniciar a operação dos sensores, o sistema aguarda o acionamento de um botão conectado ao pino **12**.

```cpp
const int pinBotao = 12;
```

Quando o botão é pressionado, o programa aguarda **1 minuto** antes de iniciar a leitura dos sensores.

```cpp
delay(60000);
```

Essa etapa pode ser utilizada, por exemplo, para permitir que o sistema seja ligado antes de uma apresentação ou demonstração.

---

# 🪽 Controle das asas

Os servomotores inferiores são utilizados para realizar movimentos relacionados às asas e à estrutura inferior do dragão.

Quando o sensor esquerdo é ativado, o motor inferior esquerdo muda de posição:

```cpp
setMotor(motorBaixoEsq, 110, estadoBaixoEsq);
```

Ao mesmo tempo, o motor inferior direito realiza um movimento temporário:

```cpp
setMotor(motorBaixoDir, 0, estadoBaixoDir);
delay(600);
setMotor(motorBaixoDir, posNormalBaixoDir, estadoBaixoDir);
```

Esse movimento cria uma sequência mecânica sincronizada entre os lados do dragão.

---

# 🐲 Controle da cabeça

O sistema também utiliza os servomotores superiores para controlar os movimentos da parte superior do dragão.

Na primeira etapa, o motor superior esquerdo é movimentado:

```cpp
setMotor(motorCimaEsq, 40, estadoCimaEsq);
```

Na segunda etapa, após a ativação do sensor direito, o motor superior direito é acionado:

```cpp
setMotor(motorCimaDir, 110, estadoCimaDir);
```

Enquanto isso, o motor superior esquerdo retorna à sua posição anterior:

```cpp
setMotor(motorCimaEsq, 120, estadoCimaEsq);
```

A combinação desses movimentos permite criar uma animação mecânica para o dragão.

---

# 🔄 Sistema de etapas

Para impedir que os movimentos sejam executados repetidamente enquanto o sensor continua detectando um objeto, o programa utiliza duas variáveis:

```cpp
bool etapaEsquerdaAtivada = false;
bool etapaDireitaAtivada = false;
```

O funcionamento é dividido em duas etapas:

```text
             INÍCIO
                │
                ▼
         Pressiona botão
                │
                ▼
       Aguarda 1 minuto
                │
                ▼
       Sistema iniciado
                │
                ▼
       ┌────────────────┐
       │ Sensor esquerdo│
       └───────┬────────┘
               │
          < 35 cm?
               │
              SIM
               │
               ▼
       🪽 Primeira etapa
               │
               ▼
       Movimenta servos
               │
               ▼
       Etapa esquerda = ON
               │
               ▼
        Sensor direito
               │
          < 35 cm?
               │
              SIM
               │
               ▼
       🐲 Segunda etapa
               │
               ▼
       Movimenta servos
               │
               ▼
        Fim da sequência
```

---

# 🧠 Lógica de programação

Um dos principais conceitos utilizados é o controle de **estados**.

A variável:

```cpp
etapaEsquerdaAtivada
```

indica se a primeira etapa já aconteceu.

A variável:

```cpp
etapaDireitaAtivada
```

indica se a segunda etapa já aconteceu.

Isso permite criar uma sequência lógica:

```text
Etapa 1
   ↓
Etapa 2
```

A segunda etapa só pode acontecer depois da primeira.

---

# 🛠️ Função de controle dos motores

Para facilitar a programação, foi criada a função:

```cpp
void setMotor(Servo &motor, int posicao, int &estado)
```

Essa função realiza duas tarefas:

1. Move o servomotor para a posição desejada;
2. Salva a posição atual na variável de estado.

Exemplo:

```cpp
setMotor(motorBaixoEsq, 110, estadoBaixoEsq);
```

Isso deixa o código mais organizado e facilita futuras alterações na animação.

---

# 📊 Painel de monitoramento

O projeto também possui um sistema de monitoramento através do **Monitor Serial**.

A função:

```cpp
void mostrarPainel(float distEsq, float distDir)
```

mostra informações como:

* Distância do sensor esquerdo;
* Distância do sensor direito;
* Posição dos quatro servomotores;
* Estado da primeira etapa;
* Estado da segunda etapa.

Isso facilita os testes e a identificação de problemas durante o desenvolvimento.

---

# 💻 Exemplo do Monitor Serial

Durante a execução, informações semelhantes a estas são apresentadas:

```text
====================================
Distancia esquerda: 28.50 cm
Distancia direita : 87.21 cm
------------------------------------
Motor baixo esquerda: 110
Motor esquerda cima : 40
Motor direita cima  : 10
Motor direita baixo : 90
------------------------------------
Etapa esquerda: ATIVADA
Etapa direita : AGUARDANDO
====================================
```

Essa ferramenta é especialmente útil durante as aulas, pois permite que os estudantes observem o que está acontecendo internamente no programa.

---

# 📚 Conceitos trabalhados

## Variáveis

```cpp
const float limiteDistancia = 35.0;
```

## Booleanos

```cpp
bool sistemaIniciado = false;
```

## Funções

```cpp
float lerDistanciaCM(...)
```

## Estruturas condicionais

```cpp
if (distEsq < limiteDistancia) {
    ...
}
```

## Referências

```cpp
Servo &motor
```

## Temporização

```cpp
delay()
delayMicroseconds()
```

## Comunicação serial

```cpp
Serial.begin(9600);
```

## Controle de servomotores

```cpp
motor.write(posicao);
```

---

# 🐉 Resultado esperado

O resultado é um **dragão animatrônico inspirado no Dragão do Shrek**, capaz de responder à aproximação do público através de sensores.

A interação acontece em sequência:

**1.** O sistema é iniciado pelo botão.

**2.** O Arduino aguarda o período de inicialização.

**3.** O sensor esquerdo detecta uma aproximação.

**4.** Os primeiros movimentos das asas e da estrutura são executados.

**5.** O sistema aguarda a ativação do sensor direito.

**6.** O segundo conjunto de movimentos é executado.

**7.** As duas etapas permanecem registradas para evitar que sejam repetidas.

---

# 🚀 Possíveis melhorias

O projeto pode ser expandido pelos estudantes com novas funcionalidades:

* [ ] Adicionar LEDs nos olhos;
* [ ] Adicionar iluminação nas asas;
* [ ] Adicionar buzzer ou alto-falante;
* [ ] Criar sons do dragão;
* [ ] Fazer a cabeça acompanhar a posição do visitante;
* [ ] Adicionar mais sensores;
* [ ] Criar movimentos graduais dos servomotores;
* [ ] Criar várias sequências de animação;
* [ ] Adicionar controle remoto;
* [ ] Criar um modo automático;
* [ ] Adicionar sensores para detectar pessoas dos dois lados;
* [ ] Criar uma sequência de movimentos contínua.

---

# 📁 Estrutura do projeto

```text
dragao-shrek/
│
├── dragao_shrek.ino
│
└── README.md
```

---

# 💻 Como utilizar

### 1. Montagem

Monte os servomotores e sensores na estrutura mecânica do dragão.

### 2. Conexões

Realize as conexões de acordo com a tabela de pinos.

### 3. Código

Abra o arquivo:

```text
dragao_shrek.ino
```

na Arduino IDE.

### 4. Placa

Selecione a placa Arduino utilizada no projeto.

### 5. Porta

Selecione a porta COM correspondente ao Arduino.

### 6. Upload

Faça o upload do programa para a placa.

### 7. Teste

Abra o Monitor Serial em **9600 baud** e teste cada etapa do sistema.

---

# ⚠️ Cuidados com os servomotores

Servomotores podem consumir uma quantidade significativa de corrente, principalmente quando vários motores são acionados simultaneamente.

Para projetos maiores, recomenda-se avaliar uma **fonte de alimentação externa adequada para os servos**, mantendo o GND da fonte conectado ao GND do Arduino.

Também é importante verificar se os mecanismos não estão travados, pois um servo tentando movimentar uma estrutura bloqueada pode consumir corrente elevada.

---

# 🏫 Oficina da Toledo

Este projeto representa a aplicação prática de conhecimentos de **programação, eletrônica e robótica** em uma construção interativa.

A criação do Dragão do Shrek permite transformar conceitos abstratos de programação em movimentos físicos e visíveis.

Ao desenvolver o projeto, os estudantes podem passar por todas as etapas de um projeto tecnológico:

```text
IDEIA
  ↓
PLANEJAMENTO
  ↓
MONTAGEM
  ↓
PROGRAMAÇÃO
  ↓
TESTES
  ↓
CORREÇÃO DE ERROS
  ↓
MELHORIAS
  ↓
PROJETO FINAL
```

Dessa forma, o projeto não se limita à programação do Arduino, mas também envolve **criatividade, trabalho em equipe, prototipagem, resolução de problemas e desenvolvimento tecnológico**.

---

