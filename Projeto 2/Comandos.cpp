#include <iostream>
#pragma once
using namespace std;

class Comandos {
protected:
    bool ligado;
    bool conectado;
    int valor;
    string nome;

public:
    //Inicialização do Comandos
    Comandos(string nome) : ligado(false), conectado(false),nome{nome} {}

    //Método para conectar (Comandos)
    bool conectar() {
        conectado = true;
        return conectado;
    }

    //Método para deconectar (Comandos)
    bool desconectar() {
        conectado = false;
        return conectado;
    }

    //Método para ligar (Comandos)
    bool ligar() {
        ligado = true;
        return ligado;
    }

    //Método para desligar (Comandos)
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