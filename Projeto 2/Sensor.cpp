#pragma once
#include <iostream>
#include "Comandos.cpp"
using namespace std;

class Sensor : public Comandos {
    public:
        // Construtor de Sensor que chama o construtor da classe Comandos
        Sensor(string nome): Comandos(nome){}      

        virtual ~Sensor() {}  // Destrutor virtual

        bool setValor(int valor){
            Comandos::setValor(valor); //reaproveita o método de Comandos para definir um valor
            return true;
        }

        bool getValor(){
            Comandos::getValor();
            return true;
        }

        bool ligar()  {
            if (!conectado) {
                conectar(); // Certificando de conectar antes de ligar
            }
            Comandos::ligar();
            cout << "Sensor " << nome << " está operacional." << endl;
            return ligado;
        }

        bool desligar() {
            Comandos::desligar();
            desconectar(); // Desconecta ao desligar
            cout << "Sensor " << nome << " foi desativado." << endl;
            return ligado;
        }        
};
