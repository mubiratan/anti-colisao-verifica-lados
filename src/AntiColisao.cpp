#include "AntiColisao.h"

void AntiColisao::setup_anti_colisao() {

}

void AntiColisao::loop_anti_colisao() {

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
                verificaObstaculos();
                delay(ESPERA);

                // Enquanto tiver 2 obstáculos dos lados, continua andanda para trás
                while (pilha.size() == 2) {
                    pilha.pop();
                    pilha.pop();
                    delay(ESPERA);
                    andaPorUmTempo(PARA_TRAS, ESPERA_MOVIMENTO);
                    delay(ESPERA);
                    verificaObstaculos();
                }

                // Se a pilha estiver vazia, ou seja, sem obstáculos dos lados
                if (pilha.empty()) {
                    if (millis() % 2 == 0) { // Gira para direita
                        delay(ESPERA);
                        giraRobo(VELOCIDADE, -VELOCIDADE, ROTACIONA_90);
                        delay(ESPERA);
                        motores.forward(VELOCIDADE);
                    } else { // Vai para esquerda
                        delay(ESPERA);
                        giraRobo(-VELOCIDADE, VELOCIDADE, ROTACIONA_90);
                        delay(ESPERA);
                        motores.forward(VELOCIDADE);
                    }    
                } else if(pilha.top() == OBSTACULO_DIREITA) {
                    delay(ESPERA);
                    pilha.pop();
                    giraRobo(-VELOCIDADE, VELOCIDADE, ROTACIONA_90);
                    delay(ESPERA);
                    motores.forward(VELOCIDADE);     
                } else {
                    delay(ESPERA);
                    pilha.pop();
                    giraRobo(VELOCIDADE, -VELOCIDADE, ROTACIONA_90);
                    delay(ESPERA);
                    motores.forward(VELOCIDADE);     
                }                
            }
        } else { //caso a distancia do sensor não seja menor que o valor "DISTANCIA_OBSTACULO" na primeira verificacao

            motores.forward(VELOCIDADE); //mantem o robo andando para frente
        }
    }
}