#pragma once
#include "Sensor.cpp"
#include <iostream>
using namespace std;

class Bussola : public Sensor {
private:
    float orientacao;
    bool curvaDireita;
    bool curvaEsquerda;

public:
    Bussola() : Sensor(nome) {}
    Bussola(string nome) : Sensor(nome), orientacao(getOrientacao()) {}

    void setOrientacao(float orientacao) {
        if(ligado){
            this->orientacao = orientacao;
        }
        else{
            cout << "Sensor de bússola está desligado." << endl;
        }    
    }
    
    float getOrientacao() {
        if(ligado){
            return orientacao;
        }
        else{
            cout << "Sensor de bússola está desligado." << endl;
            return 0.0; // Retorna valor padrão quando desligado
        }       
    }

    virtual void atualizarOrientacao1() {
        if(ligado){
            orientacao = orientacao;     //Mantém a orientação da bussola (seguir em frente)
            curvaDireita = false;
            curvaEsquerda = false;
        }
        else{
            cout << "Sensor do bussola está desligado." << endl;
        }
        
    }

    virtual void atualizarOrientacao2() {
        if(ligado){
            orientacao = orientacao + 5; //Aumenta 5 graus à orientação da bussola (virar a direita)
            curvaDireita = true;
            curvaEsquerda = false;
        }
        else{
            cout << "Sensor do bussola está desligado." << endl;
        }  
    }

    virtual void atualizarOrientacao3() {
        if(ligado){
            orientacao = orientacao - 5; //Reduz 5 graus à orientação da bussola (virar a esquerda)
            curvaDireita = false;
            curvaEsquerda = true;
        }   
        else{
            cout << "Sensor do bussola está desligado." << endl;
        }
    }
};

