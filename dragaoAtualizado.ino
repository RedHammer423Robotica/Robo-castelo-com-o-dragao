#include <Servo.h>

// ==========================
// MOTORES
// ==========================
Servo motorBaixoEsq;
Servo motorCimaEsq;
Servo motorCimaDir;
Servo motorBaixoDir;

// ==========================
// PINOS DOS MOTORES
// ==========================
const int pinMotorBaixoEsq = 8;
const int pinMotorCimaEsq  = 10;
const int pinMotorCimaDir  = 9;
const int pinMotorBaixoDir = 11;

// ==========================
// BOTAO
// pressionado = HIGH
// ==========================
const int pinBotao = 12;
bool sistemaIniciado = false;

// ==========================
// PINOS DOS ULTRASSONICOS
// ==========================
const int trigEsq = 2;
const int echoEsq = 3;

const int trigDir = 6;
const int echoDir = 7;

// ==========================
// POSICOES DOS MOTORES
// ==========================
int posNormalBaixoEsq = 90;
int posNormalCimaEsq  = 90;
int posNormalCimaDir  = 90;
int posNormalBaixoDir = 90;

int posAtivaBaixoEsq = 180;
int posAtivaCimaEsq  = 180;
int posAtivaCimaDir  = 180;
int posAtivaBaixoDir = 180;

// ==========================
// DISTANCIA LIMITE
// ==========================
const float limiteDistancia = 35.0;

// ==========================
// CONTROLE DAS ETAPAS
// ==========================
bool etapaEsquerdaAtivada = false;
bool etapaDireitaAtivada  = false;

// ==========================
// ESTADO DOS MOTORES
// ==========================
int estadoBaixoEsq;
int estadoCimaEsq;
int estadoCimaDir;
int estadoBaixoDir;

// ==========================
// LEITURA DO ULTRASSONICO
// ==========================
float lerDistanciaCM(int trigPin, int echoPin) {
  long duracao;
  float distancia;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH, 30000);

  if (duracao == 0) {
    return 999.0;
  }

  distancia = duracao * 0.0343 / 2.0;
  return distancia;
}

// ==========================
// ESCREVE NO MOTOR E SALVA
// ==========================
void setMotor(Servo &motor, int posicao, int &estado) {
  motor.write(posicao);
  estado = posicao;
}

// ==========================
// MOSTRA STATUS
// ==========================
void mostrarPainel(float distEsq, float distDir) {
  Serial.println("====================================");

  Serial.print("Distancia esquerda: ");
  Serial.print(distEsq);
  Serial.println(" cm");

  Serial.print("Distancia direita : ");
  Serial.print(distDir);
  Serial.println(" cm");

  Serial.println("------------------------------------");

  Serial.print("Motor baixo esquerda: ");
  Serial.println(estadoBaixoEsq);

  Serial.print("Motor esquerda cima : ");
  Serial.println(estadoCimaEsq);

  Serial.print("Motor direita cima  : ");
  Serial.println(estadoCimaDir);

  Serial.print("Motor direita baixo : ");
  Serial.println(estadoBaixoDir);

  Serial.println("------------------------------------");

  Serial.print("Etapa esquerda: ");
  Serial.println(etapaEsquerdaAtivada ? "ATIVADA" : "AGUARDANDO");

  Serial.print("Etapa direita : ");
  Serial.println(etapaDireitaAtivada ? "ATIVADA" : "AGUARDANDO");

  Serial.println("====================================");
  Serial.println();
}

// ==========================
// SETUP
// ==========================
void setup() {
  Serial.begin(9600);

  pinMode(pinBotao, INPUT); // pressionado = HIGH

  pinMode(trigEsq, OUTPUT);
  pinMode(echoEsq, INPUT);

  pinMode(trigDir, OUTPUT);
  pinMode(echoDir, INPUT);

  motorBaixoEsq.attach(pinMotorBaixoEsq);
  motorCimaEsq.attach(pinMotorCimaEsq);
  motorCimaDir.attach(pinMotorCimaDir);
  motorBaixoDir.attach(pinMotorBaixoDir);

  setMotor(motorBaixoEsq, 30, estadoBaixoEsq);//0 escondido
  setMotor(motorCimaEsq,  120,  estadoCimaEsq);
  setMotor(motorCimaDir,  10,  estadoCimaDir); //90 escondido
  setMotor(motorBaixoDir, posNormalBaixoDir, estadoBaixoDir);

  Serial.println("Sistema ligado.");
  Serial.println("Aperte o botao no pino 12 para iniciar.");
}

// ==========================
// LOOP
// ==========================
void loop() {
  if (!sistemaIniciado) {
    if (digitalRead(pinBotao) == HIGH) {
      Serial.println("Botao pressionado.");
      Serial.println("Aguardando 1 minuto...");

      delay(60000);

      sistemaIniciado = true;

      Serial.println("Sistema iniciado.");
    }

    return;
  }

  float distEsq = lerDistanciaCM(trigEsq, echoEsq);
  delay(50);
  float distDir = lerDistanciaCM(trigDir, echoDir);

  // ETAPA ESQUERDA
  if (!etapaEsquerdaAtivada && distEsq < limiteDistancia) {
    setMotor(motorBaixoEsq, 110, estadoBaixoEsq);

    setMotor(motorBaixoDir, 0, estadoBaixoDir);
    delay(600);
    setMotor(motorBaixoDir, posNormalBaixoDir, estadoBaixoDir);
    
    setMotor(motorCimaEsq, 40, estadoCimaEsq);

    etapaEsquerdaAtivada = true;

    Serial.println(">>> SENSOR ESQUERDO ATIVADO");
    Serial.println("Baixo esquerda, baixo direita e esquerda cima ativados.");
  }

  // ETAPA DIREITA
  if (etapaEsquerdaAtivada && !etapaDireitaAtivada && distDir < limiteDistancia) {
    setMotor(motorCimaDir, 110, estadoCimaDir);
    setMotor(motorCimaEsq, 120, estadoCimaEsq);

    etapaDireitaAtivada = true;

    Serial.println(">>> SENSOR DIREITO ATIVADO");
    Serial.println("Direita cima ativado e esquerda cima voltou ao normal.");
  }

  mostrarPainel(distEsq, distDir);

  delay(1000);
}
