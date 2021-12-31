#include "AntiColisao.h"
#include "Variaveis.h"

void AntiColisao::setup_anti_colisao() {
    pinMode(PINO_TRIGGER, OUTPUT); //configuracao do pino trigger como saida
    pinMode(PINO_ECHO, INPUT); //configuracao do pino echo como entrada
    digitalWrite(PINO_TRIGGER, LOW); //inicia o pino trigger com o nivel logico baixo
}

void AntiColisao::loop_anti_colisao() {

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

// Anda para frente ou para trás
inline void AntiColisao::andaPorUmTempo(const uint_fast8_t sentido,  const uint_fast8_t espera_movimento)
{
    if(sentido == PARA_FRENTE) {
        motores.forward(VELOCIDADE); 
    } else {
        motores.backward(VELOCIDADE);
    }
    
    delay(espera_movimento);
}

// Gira o robô para os lados e verifica se tem obstáculos 
void AntiColisao::verificaObstaculos() 
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
inline void AntiColisao::giraRobo(const uint_fast8_t velocidade, const uint_fast8_t velocidade2, const uint_fast8_t tempo_espera)
{   
    delay(ESPERA);
    motores.turn(velocidade, velocidade2);
    delay(tempo_espera); //matem o movimento do robo
    motores.stop(); //para os motores do robo
    delay(ESPERA);
}

//funcao para a leitura do sensor
inline int AntiColisao::sensor_ultrassonico() 
{
    //realiza o pulso de 10 microsegundos no trigger do sensor
    digitalWrite(PINO_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(PINO_TRIGGER, LOW);

    //mede o pulso em microsegundos retornado para o echo do sensor
    //e converte o tempo para distancia divindo por 58
    return pulseIn(PINO_ECHO, HIGH) / 58;
}