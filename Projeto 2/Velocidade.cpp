#pragma once
#include "Sensor.cpp"
#include <iostream>
using namespace std;

class Velocidade : public Sensor {
private:
    float VelocidadeAviao = 0;

public:
    Velocidade() : Sensor(nome) {}
    Velocidade(string nome): Sensor(nome), VelocidadeAviao(0) {}

    float getVelocidade() {
        if(ligado){
            return VelocidadeAviao;    
        }
        else{   
            return 0;
        }
        return 0;       
    }

    // Métodos para retornar a velocidade
    void atualizarVelocidade1(){
        if (ligado) {
            VelocidadeAviao = VelocidadeAviao;      // Velocidade recebe velocidade
            cout << "Sensor de velocidade está Ligado." << endl;
        } else {
            cout << "Sensor de velocidade está desligado." << endl;
        }
    }

    void atualizarVelocidade2(){ 
        if (ligado) {
            VelocidadeAviao = VelocidadeAviao + 10; // Atualiza a velocidade para decolagem
            cout << "Sensor de velocidade está Ligado." << endl;
        } else {
            cout << "Sensor de velocidade está desligado." << endl;
        }
    }

    void atualizarVelocidade3(){
        if (VelocidadeAviao == 0){
            VelocidadeAviao = VelocidadeAviao;
            cout << "Sensor de velocidade está Ligado." << endl;
        }
        else{
            VelocidadeAviao = VelocidadeAviao - 10; // Atualiza a velocidade para aterrisagem
    }
    }

};