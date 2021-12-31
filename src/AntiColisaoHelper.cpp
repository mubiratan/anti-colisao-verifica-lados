#include "AntiColisaoHelper.h"

// Anda para frente ou para trás
void AntiColisaoHelper::andaPorUmTempo(const uint_fast8_t sentido,  const uint_fast8_t espera_movimento)
{
    if(sentido == PARA_FRENTE) {
        motores.forward(VELOCIDADE); 
    } else {
        motores.backward(VELOCIDADE);
    }
    
    delay(espera_movimento);
}

// Gira o robô para os lados e verifica se tem obstáculos 
void AntiColisaoHelper::verificaObstaculos() 
{
    delay(ESPERA);

    // Gira para direita
    giraRobo(VELOCIDADE, -VELOCIDADE, ROTACIONA_90);
    
    delay(ESPERA);
    distancia = sensor_ultrassonico();
    
    if (distancia <= DISTANCIA_OBSTACULO)
    {
        pilha.push(OBSTACULO_DIREITA);
    }

    delay(ESPERA);
    
    // Gira para esquerda
    giraRobo(-VELOCIDADE, VELOCIDADE, ROTACIONA_180);

    delay(ESPERA);
    distancia = sensor_ultrassonico();
    
    if (distancia <= DISTANCIA_OBSTACULO)
    {
        pilha.push(OBSTACULO_ESQUERDA);
    }

    // Volta para o centro
    delay(ESPERA);
    giraRobo(VELOCIDADE, -VELOCIDADE, ROTACIONA_90);
}

// Gira o robô para os lados
void AntiColisaoHelper::giraRobo(const uint_fast8_t velocidade, const uint_fast8_t velocidade2, const uint_fast8_t tempo_espera)
{   
    delay(ESPERA);
    motores.turn(velocidade, velocidade2);
    delay(tempo_espera); //matem o movimento do robo
    motores.stop(); //para os motores do robo
    delay(ESPERA);
}

//funcao para a leitura do sensor
int AntiColisaoHelper::sensor_ultrassonico() 
{
    //realiza o pulso de 10 microsegundos no trigger do sensor
    digitalWrite(PINO_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PINO_TRIGGER, LOW);

    //mede o pulso em microsegundos retornado para o echo do sensor
    //e converte o tempo para distancia divindo por 58
    return pulseIn(PINO_ECHO, HIGH) / 58;
}