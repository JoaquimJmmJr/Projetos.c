#include <iostream>
#pragma once
#include "Comandos.cpp"  
using namespace std;

class ControlesDeVoo : public Comandos {
    public:
        //Construtor para definir o nome do componente
        ControlesDeVoo(string nome) : Comandos(nome){}

        virtual ~ControlesDeVoo() {}

        //Método de set do valor
        bool setValor(int valor){
            Comandos::setValor(valor); //reaproveita o método de componente para definir um valor
            return true;
        }

};
