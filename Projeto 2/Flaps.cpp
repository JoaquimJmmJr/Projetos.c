#include <iostream>
#include "ControlesDeVoo.cpp"
using namespace std;

class Flaps : public ControlesDeVoo {
private:
    int Posicao;

public:
    // Construtor que inicializa os Flaps
    Flaps(string nome) : ControlesDeVoo(nome), Posicao(0) {}

    void setPosicaoFlaps(int novaPosicao) {
        if (novaPosicao == 0) {  // Flaps Retraidos (Alinhado com a Asa, altas velocidades)
            Posicao = 0;
        } else if (novaPosicao == 1) {  // Flaps em 10°
            Posicao = 1;
        } else if (novaPosicao == 2) {  // Flaps em 20°
            Posicao = 2;
        } else if (novaPosicao == 3) {  // Flaps em 30°
            Posicao = 3;
        } else if (novaPosicao == 4) {  // Flaps em 40°
            Posicao = 4;
        }
    }

    int getPosicao() const {
        return Posicao;
    }

    string exibirPosicoes() const {
        string posicoes[5] = {"Flaps Retraidos (Alinhado com a Asa)", "Flaps em 10° (Consegue voar em velocidades mais baixas)", "Flaps em 20° (Consegue voar em velocidades mais baixas)", "Flaps em 30° (Consegue voar em velocidades mais baixas)", "Flaps em 40° (Consegue voar em velocidades mais baixas)"};
       return posicoes[Posicao];
    }
};

