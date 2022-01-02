#include <stack>
#include "AntiColisao.h"
#include "Variaveis.h"
#include "Helper.h"

void loop_anti_colisao() {
    VespaMotors motores;
    std::stack<uint_fast8_t> pilha{};
    int distancia;

    while(true) 
    {   
        delay(ESPERA); //aguarda o tempo de espera para leitura do sensor
        distancia = sensor_ultrassonico(); //armazena a distancia lida pelo sensor a variavel distancia

        //verifica se a distancia lida pelo sensor e menor ou igual ao valor configurado na variavel "DISTANCIA_OBSTACULO"
        if (distancia <= DISTANCIA_OBSTACULO) //se for verdadeiro
        {            
            delay(ESPERA); //aguarda o tempo de espera para leitura do sensor
            distancia = sensor_ultrassonico(); //atualiza a leitura do sensor

            //confirma se a distancia lida pelo sensor e menor ou igual ao valor configurado na variavel "DISTANCIA_OBSTACULO"
            if (distancia <= DISTANCIA_OBSTACULO) 
            {   
                motores.stop();          
                verificaObstaculos(motores, pilha);
                delay(ESPERA);

                // Enquanto tiver 2 obstáculos dos lados, continua andanda para trás
                while (pilha.size() == 2) {
                    pilha.pop();
                    pilha.pop();
                    delay(ESPERA);
                    andaPorUmTempo(motores, PARA_TRAS, ESPERA_MOVIMENTO);
                    delay(ESPERA);
                    verificaObstaculos(motores, pilha);
                    delay(ESPERA);
                }

                // Se a pilha estiver vazia, ou seja, sem obstáculos dos lados
                if (pilha.empty()) {
                    if (millis() % 2 == 0) { // Gira para direita
                        delay(ESPERA);
                        giraRobo(motores, VELOCIDADE, -VELOCIDADE, ROTACIONA_90);
                        delay(ESPERA);
                        motores.forward(VELOCIDADE);
                    } else { // Vai para esquerda
                        delay(ESPERA);
                        giraRobo(motores, -VELOCIDADE, VELOCIDADE, ROTACIONA_90);
                        delay(ESPERA);
                        motores.forward(VELOCIDADE);
                    }    
                } else if(pilha.top() == OBSTACULO_DIREITA) {
                    delay(ESPERA);
                    pilha.pop();
                    giraRobo(motores, -VELOCIDADE, VELOCIDADE, ROTACIONA_90);
                    delay(ESPERA);
                    motores.forward(VELOCIDADE);     
                } else {
                    delay(ESPERA);
                    pilha.pop();
                    giraRobo(motores, VELOCIDADE, -VELOCIDADE, ROTACIONA_90);
                    delay(ESPERA);
                    motores.forward(VELOCIDADE);     
                }                
            }
        } else { //caso a distancia do sensor não seja menor que o valor "DISTANCIA_OBSTACULO" na primeira verificacao
            motores.forward(VELOCIDADE); //mantem o robo andando para frente
        }
    }
}