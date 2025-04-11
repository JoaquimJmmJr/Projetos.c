#include <iostream>
#include "Atuador.cpp"
using namespace std;

class Lampada : public Atuador {
private:
    int nivelBrilho;  
    int limiarClaridade = 300;

public:
    // Construtor que inicializa o nome e o brilho
    Lampada() : Atuador("Lampada"){}

    bool setBrilho(int luminosidadeAtual) {
        setValor(luminosidadeAtual);
        luminosidadeAtual = getValor();  
        if (luminosidadeAtual >= limiarClaridade) {  // Claridade alta, desligar a lâmpada
            //cout << "Lâmpada: desligada (luminosidade alta).\n";
            this->desligar();
            this->desconectar();
            return false;
        } else {  // Claridade baixa, ligar a lâmpada
            //cout << "Lâmpada: ligada (luminosidade baixa).\n";
            this->ligar();
            this->conectar();
            return true;
        }
    }

};
