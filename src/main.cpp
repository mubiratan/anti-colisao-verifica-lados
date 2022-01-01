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
#include "Variaveis.h"

TaskHandle_t Task1;

void Task1code( void * pvParameters ) {
  while(true) {
      digitalWrite(LED_Vespa, HIGH);
      delay(700);
      digitalWrite(LED_Vespa, LOW);
      delay(700);
  }
}

void setup() {
  pinMode(LED_Vespa, OUTPUT);
  pinMode(PINO_TRIGGER, OUTPUT); //configuracao do pino trigger como saida
  pinMode(PINO_ECHO, INPUT); //configuracao do pino echo como entrada
  digitalWrite(PINO_TRIGGER, LOW); //inicia o pino trigger com o nivel logico baixo

  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500);

}

// Task 2
void loop() {
  AntiColisao antiColisao;
  antiColisao.loop_anti_colisao();  
}