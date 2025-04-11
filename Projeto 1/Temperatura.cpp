#pragma once
#include "Sensor.cpp"
#include <iostream>
#include <stdlib.h> //biblioteca para usar o gerador de números aleatórios
#include <time.h>   //biblioteca do tempo que servirá de semente
using namespace std;

class Temperatura : public Sensor {
private:
    float TemperaturaEmC;
    float TemperaturaEmC2;
    float TemperaturaEmC3;
    float TemperaturaEmK;
    float TemperaturaEmF;

public:
    Temperatura() : Sensor(nome) {}
    Temperatura(string nome): Sensor(nome), TemperaturaEmC(0), TemperaturaEmK(0), TemperaturaEmF(0) {}

    // Métodos para retornar a temperatura em diferentes escalas
    float getTemperaturaEmC() {
        return TemperaturaEmC;           
    }
    
    float getTemperaturaEmK() {
        TemperaturaEmK = TemperaturaEmC + 273.15;
        return TemperaturaEmK;
    }

    float getTemperaturaEmF() {
        TemperaturaEmF = (TemperaturaEmC * 1.8) + 32;
        return TemperaturaEmF;
    }

    float getTemperaturaEmC2() {
        return TemperaturaEmC2;           
    }
    
    float getTemperaturaEmK2() {
        TemperaturaEmK = TemperaturaEmC2 + 273.15;
        return TemperaturaEmK;
    }

    float getTemperaturaEmF2() {
        TemperaturaEmF = (TemperaturaEmC2 * 1.8) + 32;
        return TemperaturaEmF;
    }


    float getTemperaturaEmC3() {
        return TemperaturaEmC3;           
    }
    
    float getTemperaturaEmK3() {
        TemperaturaEmK = TemperaturaEmC3 + 273.15;
        return TemperaturaEmK;
    }

    float getTemperaturaEmF3() {
        TemperaturaEmF = (TemperaturaEmC3 * 1.8) + 32;
        return TemperaturaEmF;
    }

    void atualizarTemperatura(){
        srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual
        TemperaturaEmC = rand() % 41; // Gera uma temperatura entre 0 e 40°C
        cout<<endl;
    }

    void atualizarTemperatura2(){
        srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual
        TemperaturaEmC2 = rand() % 15 + 21; // Gera uma temperatura entre 21 e 35°C
        cout<<endl;
    }

    void atualizarTemperatura3(){
        srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual
        TemperaturaEmC3 = rand() % 9 + 13; // Gera uma temperatura entre 11 e 21°C
        cout<<endl;
    }
};