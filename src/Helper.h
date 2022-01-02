#ifndef HELPER
#define HELPER

#include <stack>
#include "Variaveis.h"

int sensor_ultrassonico();
void verificaObstaculos(VespaMotors &, std::stack<uint_fast8_t> &);
void andaPorUmTempo(VespaMotors &, const uint_fast8_t &, const uint_fast8_t &);
void giraRobo(VespaMotors &motores, const uint_fast8_t &velocidade, const uint_fast8_t &velocidade2, const uint_fast8_t &tempo_espera);

#endif