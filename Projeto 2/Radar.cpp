#pragma once
#include "Sensor.cpp"
#include <iostream>
#include <stdlib.h> // Biblioteca para usar o gerador de números aleatórios
#include <time.h>   // Biblioteca do tempo que servirá de semente
using namespace std;

class Radar : public Sensor {
private:
    string colisao;
    string tipoObjeto; // Armazena o tipo de objeto detectado
    
public:
    Radar() : Sensor("Radar"), colisao(""), tipoObjeto("") {}

    Radar(string nome) : Sensor(nome), colisao(""), tipoObjeto("") {}

    // Gera um objeto aleatório e atualiza a descrição do tipo de objeto
    void objetoDetectado() {
        if (ligado) {
            int objeto = rand() % 3; // Gera um número aleatório para selecionar o tipo de objeto
            if (objeto == 0) {
                tipoObjeto = "Pássaro detectado";
            } else if (objeto == 1) {
                tipoObjeto = "Avião detectado";
            } else {
                tipoObjeto = "Balão detectado";
            }
        } else {
            cout << "Sensor do radar está desligado." << endl;
        }
    }

    // Define o valor e determina a mensagem de acordo com a distância
    string setColisao(int distancia) {
        if (ligado) {
            setValor(distancia); // Define o valor usando o setter da classe base
            valor = getValor();  // Atualiza a variável valor com o novo valor

            // Verifica o valor e retorna a mensagem apropriada
            if (valor < 9) {
                colisao = tipoObjeto + ", colisão iminente!\n";
            } else if (valor >= 9 && valor <= 18) {
                colisao = tipoObjeto + ", está se aproximando!\n";
            } else {
                colisao = tipoObjeto + ", está distante!\n";
            }
            return colisao;
        } else {
            cout << "Sensor do radar está desligado." << endl;
            return "Radar desligado.";
        }
    }

    string getColisao() const {
        return colisao;
    }
};
