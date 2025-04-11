#include <iostream>
#include "ControlesDeVoo.cpp"
using namespace std;

class Motores : public ControlesDeVoo{
    private:
        int potenciaMotor; // Potência do motor (0 a 100%)

    public:
        // Construtor para inicializar a potência (opcional)
        Motores(string nome) : ControlesDeVoo(nome), potenciaMotor(0) {}

        // Método para definir a potência do motor
        void setPotenciaMotor(int novapotenciaMotor) {
                if (novapotenciaMotor < 0) {
                    potenciaMotor = 0;
                } else if (novapotenciaMotor > 100) {
                    potenciaMotor = 100;
                } else {
                potenciaMotor = novapotenciaMotor;
            }
        }

        // Método para obter a potência atual do motor
        int getPotenciaMotor() const {
            return potenciaMotor;
        }
};
