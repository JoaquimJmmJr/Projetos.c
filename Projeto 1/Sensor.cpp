#pragma once
#include <iostream>
#include "Componente.cpp"
using namespace std;

class Sensor : public Componente {
    public:
        // Construtor de Sensor, que chama o construtor da classe Componente
        Sensor(string nome): Componente(nome){}      

        virtual ~Sensor() {}  // Destrutor virtual

        bool setValor(int valor){
            Componente::setValor(valor); //reaproveita o método de componente para definir um valor
            return true;
        }

        bool getValor(){
            Componente::getValor();
            return true;
        }
        
        virtual void exibirDados() const {
            cout << "Estado: " << (ligado ? "Ligado" : "Desligado") << endl;
            cout << "Status de conexão: " << (conectado ? "Conectado" : "Desconectado") << endl;
            cout << endl;  // Espaçamento para melhor visualização
        }
};
