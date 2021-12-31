#ifndef ANTI_COLISAO_HELPER
#define ANTI_COLISAO_HELPER    

#include <RoboCore_Vespa.h>
#include <stack>

static std::stack<uint_fast8_t> pilha{};

class AntiColisaoHelper
{
private:
    /* data */
public:
    //declaracao dos pinos do sensor
    const uint_fast8_t PINO_TRIGGER = 25;
    const uint_fast8_t PINO_ECHO = 26;
    //declaracao da variavel que armazena a distancia do obstaculo
    const uint_fast8_t DISTANCIA_OBSTACULO = 25;
    //declaracao das variaveis que armazenam a velocidade de giro e de reta dos motores do robo
    const uint_fast8_t VELOCIDADE = 80;
    //declaracao da variavel que armazena o tempo de espera entre leituras do sensor
    const uint_fast8_t ESPERA = 60;
    //declaracao da variavel que armazena o tempo que os movimentos de desvio irao durar
    const unsigned int ESPERA_MOVIMENTO = 870;
    const unsigned int ROTACIONA_90 = ESPERA_MOVIMENTO;
    const unsigned int ROTACIONA_180 = ESPERA_MOVIMENTO * 2;
    int distancia;
    VespaMotors motores;

    // Pilha
    const uint_fast8_t OBSTACULO_DIREITA = 1, OBSTACULO_ESQUERDA = 2;
    const uint_fast8_t PARA_FRENTE = 0, PARA_TRAS = 1; 
    public:

    AntiColisaoHelper();
    ~AntiColisaoHelper();
    
    int sensor_ultrassonico();
    void verificaObstaculos();
    void andaPorUmTempo(const uint_fast8_t,  const uint_fast8_t);
    void giraRobo(const uint_fast8_t velocidade, const uint_fast8_t velocidade2, const uint_fast8_t tempo_espera);
};  


#endif