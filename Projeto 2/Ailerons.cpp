#include <iostream>
#include "ControlesDeVoo.cpp"
using namespace std;

class Ailerons: public ControlesDeVoo {
private:
    int posicaoDireito; // 0 = Para Baixo, 1 = Alinhado, 2 = Para Cima
    int posicaoEsquerdo;

public:
    // Construtor que inicializa ambos os ailerons para a posição alinhada (1)
    Ailerons(string nome) : ControlesDeVoo(nome), posicaoDireito(1), posicaoEsquerdo(1) {}

    void setPosicaoAilerons(int novaPosicao) {
        if (novaPosicao == 1) {         // Alinhado
            posicaoDireito = 1;
            posicaoEsquerdo = 1;
        } else if (novaPosicao == 2) {  // Para Direita
            posicaoDireito = 2;
            posicaoEsquerdo = 0;
        } else if (novaPosicao == 0) {  // Para Esquerda
            posicaoDireito = 0;
            posicaoEsquerdo = 2;
        }
    }

    int getPosicaoDireito() const {
        return posicaoDireito;
    }

    int getPosicaoEsquerdo() const {
        return posicaoEsquerdo;
    }

    string exibirPosicoes() const {
        string posicoes[3] = {"Para Baixo", "Alinhado", "Para Cima"};
        return "Aileron Direito: " + posicoes[posicaoDireito] + "\n" + "Aileron Esquerdo: " + posicoes[posicaoEsquerdo];
    }
};

