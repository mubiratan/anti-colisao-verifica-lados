/********************************************************
 * RoboCore - Kit Robo Explorer - Robo Anticolisao
 * 
 * O robo fica constantemente medindo a distancia do
 * sensor ultrassonico e, quando a distancia for menor que 
 * a distancia de obstaculo configurada, o robo ira girar
 * para a direita ou para a esquerda, desviando do 
 * obstaculo e voltando a andar para frente.
********************************************************/

#include "AntiColisao.h"

  //declaracao dos pinos do sensor
  const uint_fast8_t PINO_TRIGGER = 25;
  const uint_fast8_t PINO_ECHO = 26;

void setup() {  

    pinMode(PINO_TRIGGER, OUTPUT); //configuracao do pino trigger como saida
    pinMode(PINO_ECHO, INPUT); //configuracao do pino echo como entrada
    digitalWrite(PINO_TRIGGER, LOW); //inicia o pino trigger com o nivel logico baixo
}

void loop() {
  AntiColisao a;
  //antiColisao.loop_anti_colisao();  
}