#ifndef ANTI_COLISAO
#define ANTI_COLISAO

//adiciona a biblioteca de controle de motores ao codigo
#include <RoboCore_Vespa.h>
#include <stack>

static std::stack<uint_fast8_t> pilha{};

class AntiColisao 
{
    public:
    //declaracao do objeto "motores"
    VespaMotors motores;

    void loop_anti_colisao();
    void setup_anti_colisao();
    void verificaObstaculos();
    inline void giraRobo(const uint_fast8_t, const uint_fast8_t, const uint_fast8_t);
    inline void andaPorUmTempo(const uint_fast8_t, const uint_fast8_t);
    inline int sensor_ultrassonico();
};

#endif