#include <iostream>
#include "Atuador.cpp"
using namespace std;

class Ventilador: public Atuador{      //herdará da classe "Atuador"
    private:
    int valor_entrada;                 
    int valor_saida;

    public:
    Ventilador() : Atuador("Ventilador") {} //Construtor
    
    bool setVelocidade(int valor_entrada){      
        setValor(valor_entrada);
        valor_saida = getValor();          
            if (valor_saida == 0) {
            cout << "Ventilador está desligado." << endl;
            this->desligar();
            return false;
            }
            else if (valor_saida==1){ 
                cout << "Velocidade: mínima" << endl;
                return true;  //velocidade foi setada
            }
            else if (valor_saida==2){ 
                cout << "Velocidade: média" << endl;
                return true;  //velocidade foi setada
            }
            else if (valor_saida==3){ 
                cout << "Velocidade: máxima" << endl;
                return true;  //velocidade foi setada
            }
            else{
                //se a velocidade for maior do que a velocidade maxima retornamos "false" para o set
                return false; //velocidade não foi setada
            }
    }

    bool setValor(int novoValor) {
        // Implementação do método setValor
        if (novoValor >= 0 && novoValor <= 100) {  
            this->valor = novoValor;
            return true;
        }
        return false;
    }
};