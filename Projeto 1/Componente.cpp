#include <iostream>
#pragma once
using namespace std;

class Componente {
protected:
    bool ligado;
    bool conectado;
    int valor;
    string nome;

public:
    //Inicialização do componente
    Componente(string nome) : ligado(false), conectado(false),/*valor(0),*/ nome{nome} {}

    //Método para conectar (Componente)
    bool conectar() {
        conectado = true;
        return conectado;
    }

    //Método para deconectar (Componente)
    bool desconectar() {
        conectado = false;
        return conectado;
    }

    //Método para ligar (Componente)
    bool ligar() {
        ligado = true;
        return ligado;
    }

    //Método para desligar (Componente)
    bool desligar() {
        ligado = false;
        return ligado;
    }

    //Método para definir o valor
    bool setValor(int valor) {
        this->valor = valor;
        return true;
    }

    //Método para obter o valor
    int getValor() const {
        return valor;
    }

    string getNome(){
        return nome;
    }
};