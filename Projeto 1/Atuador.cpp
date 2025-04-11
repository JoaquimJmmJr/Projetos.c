#include <iostream>
#pragma once
#include "Componente.cpp"  // Inclui a classe Componente
using namespace std;

class Atuador : public Componente {
    public:
        //Construtor para definir o nome do componente
        Atuador(string nome) : Componente(nome) {}

        virtual ~Atuador() {}

        //Método de set do valor
        bool setValor(int valor){
            Componente::setValor(valor); //reaproveita o método de componente para definir um valor
            return true;
        }

};
