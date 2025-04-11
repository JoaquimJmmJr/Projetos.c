#pragma once
#include "Sensor.cpp"
#include <iostream>
using namespace std;

class Altimetro : public Sensor {
private:
    int limiarAltitude;
    float valorAltitude;

public:
    Altimetro() : Sensor(nome) {}
    Altimetro(string nome) : Sensor(nome), limiarAltitude(36000) {} // Exemplo de valor de limiar

    void setLimiarAltitude(int limiarAltitude) {
        this->limiarAltitude = limiarAltitude;
    }

    int getLimiarAltitude(){
        if(ligado){
            return limiarAltitude;
            cout << "Sensor de Altitude está Ligado." << endl;
        }
        else{
            cout << "Sensor de Altitude está desligado." << endl;
        } 
    }

    void setAltitude(float valorAltitude){
        this->valorAltitude = valorAltitude;
    }

    float getAltitude(){
        return valorAltitude;
    }

    virtual void atualizarAltitude1() {
        if(ligado){
            valorAltitude = valorAltitude;      //Mantém a altitude 
            cout << "Sensor de Altitude está Ligado." << endl;
        }
        else{
            cout << "Sensor de Altitude está desligado." << endl;
        } 
    }

    virtual void atualizarAltitude2() {
        if(ligado){
            valorAltitude = valorAltitude + 500; //Atualiza a altitude para subida  
            cout << "Sensor de Altitude está Ligado." << endl;
        }
        else{
            cout << "Sensor de Altitude está desligado." << endl;
        } 
        
    }

    virtual void atualizarAltitude3() {
        if(ligado){
           valorAltitude = valorAltitude - 500; //Atualiza a altitude para descida 
           cout << "Sensor de Altitude está Ligado." << endl;
        }
        else{
            cout << "Sensor de Altitude está desligado." << endl;
        } 
        
    }

    virtual void atualizarAltitude4() {
        if(ligado){
            valorAltitude = valorAltitude - 1000; //Atualiza a altitude para descida mais rápida
            cout << "Sensor de Altitude está Ligado." << endl;
        }
        else{
            cout << "Sensor de Altitude está desligado." << endl;
        } 
    }

    virtual void atualizarAltitude5() {
        if(ligado){
            valorAltitude = valorAltitude - 250; //Atualiza a altitude para descida mais lenta
            cout << "Sensor de Altitude está Ligado." << endl;
        }
        else{
            cout << "Sensor de Altitude está desligado." << endl;
        }         
    }

    bool altitudeCruzeiro() {
        if (valorAltitude < limiarAltitude) { //Se o valor for menor, não está na altitude de cruzeiro
            return false;
        } else {
            cout << "Altitude de Cruzeiro.\n";
            return true;
        }
    }
    
};


