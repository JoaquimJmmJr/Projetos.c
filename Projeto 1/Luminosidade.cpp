#pragma once
#include "Sensor.cpp"
#include <iostream>
#include <stdlib.h> //biblioteca para usar o gerador de números aleatórios
#include <time.h>   //biblioteca do tempo que servirá de semente
using namespace std;

class Luminosidade : public Sensor {
private:
    int limiarClaridade;
    float valorLuminosidade;
    float valorLuminosidade2;
    float valorLuminosidade3;

public:
    Luminosidade() : Sensor(nome) {}
    Luminosidade(string nome) : Sensor(nome), limiarClaridade(300) {} // Exemplo de valor de limiar

    void setLimiarClaridade(int limiarClaridade) {
        this->limiarClaridade = limiarClaridade;
    }

    int getLimiarClaridade(){
        return limiarClaridade;
    }

    void setLuminosidade(float valor){
        this->valorLuminosidade = valor;
    }

    float getLuminosidade(){
        return valorLuminosidade;
    }

    float getLuminosidade2(){
        return valorLuminosidade2;
    }

    float getLuminosidade3(){
        return valorLuminosidade3;
    }

    virtual void atualizarLuminosidade() {
        srand((time(NULL)));  //inicializa o gerador de números aleatórios com o tempo
        valorLuminosidade = rand()%1001; //Luminosidade entre 0 e 1000 lumens
    }

    virtual void atualizarLuminosidade2() {
        srand((time(NULL)));  //inicializa o gerador de números aleatórios com o tempo
        valorLuminosidade2 = rand()%900; //Luminosidade entre 0 e 900 lumens
    }

    virtual void atualizarLuminosidade3() {
        srand((time(NULL)));  //inicializa o gerador de números aleatórios com o tempo
        valorLuminosidade3 = rand()%800; //Luminosidade entre 0 e 800 lumens
    }

    bool estaClaro() {
        if (valorLuminosidade < limiarClaridade) {
            cout << "Condição do ambiente: está escuro.\n";
            return false;
        } else {
            cout << "Condição do ambiente: está claro.\n";
            return true;
        }
    }
    bool estaClaro2() {
        if (valorLuminosidade2 < limiarClaridade) {
            cout << "Condição do ambiente: está escuro.\n";
            return false;
        } else {
            cout << "Condição do ambiente: está claro.\n";
            return true;
        }
    }
    bool estaClaro3() {
        if (valorLuminosidade3 < limiarClaridade) {
            cout << "Condição do ambiente: está escuro.\n";
            return false;
        } else {
            cout << "Condição do ambiente: está claro.\n";
            return true;
        }
    }
    
};

