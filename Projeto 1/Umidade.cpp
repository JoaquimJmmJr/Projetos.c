#pragma once
#include "Sensor.cpp"
#include <iostream>
#include <stdlib.h> //biblioteca para usar o gerador de números aleatórios
#include <time.h>   //biblioteca do tempo que servirá de semente
using namespace std;

class Umidade : public Sensor {
private:
    float umidadeRelativa;
    float umidadeRelativa2;
    float umidadeRelativa3;

public:
    Umidade() : Sensor(nome) {}
    Umidade(string nome) : Sensor(nome), umidadeRelativa(getUmidadeRelativa()), umidadeRelativa2(getUmidadeRelativa2()),umidadeRelativa3(getUmidadeRelativa3()) {}

    void setUmidadeRelativa(float umidadeRelativa) {
        umidadeRelativa = umidadeRelativa;
    }
    
    float getUmidadeRelativa() {
        return umidadeRelativa;
    }

    float getUmidadeRelativa2() {
        return umidadeRelativa2;
    }

    float getUmidadeRelativa3() {
        return umidadeRelativa3;
    }

    virtual void atualizarUmidade() {
        srand((time(NULL)));  //inicializa o gerador de números aleatórios com o tempo
        umidadeRelativa = rand() % 100; //Umidade entre 0 e 100% 
    }

    virtual void atualizarUmidade2() {
        srand((time(NULL)));  //inicializa o gerador de números aleatórios com o tempo
        umidadeRelativa2 = rand() % 90; //Umidade entre 0 e 90% 
    }

    virtual void atualizarUmidade3() {
        srand((time(NULL)));  //inicializa o gerador de números aleatórios com o tempo
        umidadeRelativa3 = rand() % 80; //Umidade entre 0 e 80%
    }
};

