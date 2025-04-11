#include <iostream>
#include "ControlesDeVoo.cpp"
using namespace std;

class Profundor : public ControlesDeVoo {
private:
    int posicao; // 0 = Para Baixo, 1 = Alinhado, 2 = Para Cima

public:
    // Construtor que inicializa o profundor na posição neutra
    Profundor(string nome) : ControlesDeVoo(nome), posicao(1) {}

    void setPosicao(int novaPosicao) {
        if (novaPosicao >= 0 && novaPosicao <= 2) {
            //posição 0 = Para Baixo
            //posição 1 = Alinhado
            //posição 2 = Para cima
            posicao = novaPosicao;
        } else {
            cout << "Posição inválida. Escolha 0 (Para Baixo), 1 (Alinhado), ou 2 (Para Cima)." << endl;
        }
    }

    int getPosicao() const {
        return posicao;
    }

    string exibirPosicao() const {
        string posicoes[3] = {"Para Baixo (Avião desce)", "Alinhado (mantém a altitude)", "Para Cima (Avião sobe)"};
        return "Profundor está na posição: " + posicoes[posicao];
    }
};
