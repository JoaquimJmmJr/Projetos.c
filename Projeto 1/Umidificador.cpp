#include <iostream>
#include "Atuador.cpp"
using namespace std;

class Umidificador: public Atuador{
    private:
    int valor;
    float umidadeRelativa = 60;

    public:
        Umidificador() : Atuador("Umidificador") {} //Construtor
   
        bool setConfiguracao(int valor){   
            setValor(valor);
            valor = getValor();                   
            if (valor >= umidadeRelativa){   //Umidificador esta desligado 
                //cout<<"Umidificador está desligado. (umidade alta)"<<endl;    
                this->desligar();    
                this-> desconectar();                    
                return false;
            }
            else {             //Umidificador foi ligado e setado
                //cout<<"Umidificador está ligado. (umidade baixa)"<<endl;
                this->ligar();
                this-> conectar();
                return true;  //umidificador foi setado
            }
        }
};