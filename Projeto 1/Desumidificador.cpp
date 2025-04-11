#include <iostream>
#include "Atuador.cpp"
using namespace std;

class Desumidificador : public Atuador {
    private:
    int valor;
    float umidadeRelativa = 60;

    public:
        Desumidificador() : Atuador("Desumidificador") {}//Construtor 
        
        bool setConfiguracao(int valor){   
            setValor(valor);
            valor = getValor();                   
            if (valor <= umidadeRelativa){   //Desumidificador esta desligado 
                //cout<<"Desumidificador está desligado. (umidade baixa)"<<endl;     
                this->desligar();     
                this-> desconectar();                  
                return false;
            }
            else {             //Desumidificador foi ligado e setado
                //cout<<"Desumidificador está ligado. (umidade alta)"<<endl;   
                this->ligar();
                this-> conectar();
                return true;   //deumidificador foi setado
            }
        }
};
