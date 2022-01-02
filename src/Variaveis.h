#ifndef VARIAVEIS_H
#define VARIAVEIS_H

#include <RoboCore_Vespa.h>

//declaracao dos pinos do sensor
const uint_fast8_t PINO_TRIGGER = 25;
const uint_fast8_t PINO_ECHO = 26;
//declaracao da variavel que armazena a distancia do obstaculo
const uint_fast8_t DISTANCIA_OBSTACULO = 25;
//declaracao das variaveis que armazenam a velocidade de giro e de reta dos motores do robo
const uint_fast8_t VELOCIDADE = 80;
//declaracao da variavel que armazena o tempo de espera entre leituras do sensor
const uint_fast8_t ESPERA = 150;
//declaracao da variavel que armazena o tempo que os movimentos de desvio irao durar
const unsigned int ESPERA_MOVIMENTO = 1000;
//declaracao da variavel que armazena a distancia medida pelo sensor
const unsigned int ROTACIONA_90 = ESPERA_MOVIMENTO;
const unsigned int ROTACIONA_180 = ESPERA_MOVIMENTO * 2;
const int LED_Vespa = 15;

const uint_fast8_t OBSTACULO_DIREITA = 1, OBSTACULO_ESQUERDA = 2;
const uint_fast8_t PARA_FRENTE = 0, PARA_TRAS = 1; 

#endif