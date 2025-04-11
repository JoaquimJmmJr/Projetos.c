#include <iostream>
#include "Sensor.cpp"          // Inclui as classes de sensores
#include "Atuador.cpp"         // Inclui a classe base Atuador
//Atuadores:
#include "Ventilador.cpp"      // Inclui a classe Ventilador
#include "Umidificador.cpp"    // Inclui a classe Umidificador
#include "Desumidificador.cpp" // Inclui a classe Desumidificador
#include "Lampada.cpp"         // Inclui a classe Lampada
//Sensores:
#include "Temperatura.cpp"
#include "Luminosidade.cpp"
#include "Umidade.cpp"
using namespace std;

class Sala {
private:
    Atuador *atuadores[12];
    Sensor *sensores[9];

public:
    Sala(){} //Construtor padrão (sem parâmetros)
    Sala(string temperatura, string luminosidade,string umidade, 
    string ventilador, string lampada, string umidificador, string desumidificador ) {

        // Inicializar os sensores e atuadores como ponteiros
        sensores[0] = new Temperatura("Sensor de Temperatura 1");
        sensores[1] = new Luminosidade("Sensor de Luminosidade 1");
        sensores[2] = new Umidade("Sensor de Umidade 1");

        sensores[3] = new Temperatura("Sensor de Temperatura 2");
        sensores[4] = new Luminosidade("Sensor de Luminosidade 2");
        sensores[5] = new Umidade("Sensor de Umidade 2");

        sensores[6] = new Temperatura("Sensor de Temperatura 3");
        sensores[7] = new Luminosidade("Sensor de Luminosidade 3");
        sensores[8] = new Umidade("Sensor de Umidade 3");

        //Inicializando os atuadores
        atuadores[0] = new Ventilador();        //atuador de temperatura 1
        atuadores[1] = new Lampada();           //atuador de luminosidade 1
        atuadores[2] = new Umidificador();      //atuador de umidade 1
        atuadores[3] = new Desumidificador();   //atuador de umidade

        atuadores[4] = new Ventilador();
        atuadores[5] = new Lampada();
        atuadores[6] = new Umidificador();
        atuadores[7] = new Desumidificador();

        atuadores[8] = new Ventilador();
        atuadores[9] = new Lampada();
        atuadores[10] = new Umidificador();
        atuadores[11] = new Desumidificador();
       
        // Pode inicializar mais sensores e atuadores conforme necessário   
    }

    //Limpar o lixo de memória de atuadores e sensores
    ~Sala() {
    // desaloca a memória de sensores
        for (int i = 0; i < 9; i++) {
            if (sensores[i] != nullptr) {
                delete sensores[i];
            }
        }
    // desaloca a memória de atuadores
        for (int i = 0; i < 12; i++) {
            if (atuadores[i] != nullptr) {
                delete atuadores[i];
            }
        }
    }

    void atualizarSensores() {   
            Temperatura* tempSensor = dynamic_cast<Temperatura*>(sensores[0]);
            if (tempSensor != nullptr) {
                tempSensor->atualizarTemperatura();  // Atualiza a leitura da temperatura
                
                // Exibe os valores de temperatura manualmente aqui
                cout << "Leitura do Sensor de Temperatura" << endl;
                cout << "Em graus Celsius: " << tempSensor->getTemperaturaEmC() << "°C" << endl;
                cout << "Em graus Kelvin: " << tempSensor->getTemperaturaEmK() << " °K" << endl;
                cout << "Em graus Fahrenheit: " << tempSensor->getTemperaturaEmF() << " °F" << endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
        

            Luminosidade* lumSensor = dynamic_cast<Luminosidade*>(sensores[1]);
            if (lumSensor != nullptr) {
                lumSensor->atualizarLuminosidade();  // Atualiza a leitura da luminosidade
                cout << "Leitura do Sensor de Luminosidade: " << lumSensor->getLuminosidade() << " lumens" << endl; 
                lumSensor->estaClaro();
                cout<<endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
            
            Umidade* umdSensor = dynamic_cast<Umidade*>(sensores[2]);
            if (umdSensor != nullptr) {
                umdSensor->atualizarUmidade();  // Atualiza a leitura da umidade
                cout << "Leitura do Sensor de Umidade: " << umdSensor->getUmidadeRelativa() << " %"<<endl;
                cout<<endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
    }

    void atualizarAtuadores() {              
        // Exemplo de lógica para o ventilador
        if (((Temperatura*)sensores[0])->getTemperaturaEmC() < 25) { // Essa sintáxe de "downcasting" permite pegar o valor do método dentro da classe "Temperatura.cpp" do sensor de Temperatura
            ((Ventilador*)atuadores[0])->setVelocidade(0);                  //"Ventilador está desligado."           
        } else if (((Temperatura*)sensores[0])->getTemperaturaEmC()>24 && ((Temperatura*)sensores[0])->getTemperaturaEmC()<=30) { // Temperatura entre 25°C e 30°C
           ((Ventilador*)atuadores[0])->ligar();                            // Liga o ventilador
           ((Ventilador*)atuadores[0])->setVelocidade(2);                   // "Velocidade: média"
        } else if (((Temperatura*)sensores[0])->getTemperaturaEmC()>30) { // Temperatura maior que 30 °C
           ((Ventilador*)atuadores[0])->ligar();                            // Liga o ventilador
           ((Ventilador*)atuadores[0])->setVelocidade(3);                   // "Velocidade: máxima"
        }

        // Exemplo de Lógica para a lâmpada
        if (((Luminosidade*)sensores[1])->getLuminosidade()<((Luminosidade*)sensores[1])->getLimiarClaridade()) {
            ((Lampada*)atuadores[1])->setBrilho(true); //Se a luminosidade for menor do que o limiar: liga a lampada
            cout << endl;
            cout << "Lâmpada = Ligado" << endl;
        } else {
            ((Lampada*)atuadores[1])->setBrilho(false); //Se a luminosidade for menor ou igual ao limiar: desliga a lampada
            cout << endl;
            cout << "Lâmpada = Desligado" << endl;
            
        }

        // Lógica para umidificador e desumidificador
        if  (((Umidade*)sensores[2])->getUmidadeRelativa() < 60) {
            ((Umidificador*)atuadores[2])->setConfiguracao(true);
            ((Desumidificador*)atuadores[3])->setConfiguracao(false);
            cout << endl;
            cout << "Umidificador = Ligado" << endl;
            cout << endl;
            cout << "Desumidificador = Desligado" << endl;
        } else if (((Umidade*)sensores[2])->getUmidadeRelativa() >= 60 && ((Umidade*)sensores[2])->getUmidadeRelativa() < 80) {
            ((Umidificador*)atuadores[2])->setConfiguracao(false);
            ((Desumidificador*)atuadores[3])->setConfiguracao(false);
            cout << endl;
            cout << "Umidificador = Desligado" << endl;
            cout << endl;
            cout << "Desumidificador = Desligado" << endl;
        } else if (((Umidade*)sensores[2])->getUmidadeRelativa() >= 80) {
            ((Umidificador*)atuadores[2])->setConfiguracao(false);
            ((Desumidificador*)atuadores[3])->setConfiguracao(true);
            cout << endl;
            cout << "Umidificador = Desligado" << endl;
            cout << endl;
            cout << "Desumidificador = Ligado" << endl;
        }
    } 

    void atualizarSensores2() {   
            Temperatura* tempSensor = dynamic_cast<Temperatura*>(sensores[3]);
            if (tempSensor != nullptr) {
                tempSensor->atualizarTemperatura2();  // Atualiza a leitura da temperatura
                
                // Exibe os valores de temperatura manualmente aqui
                cout << "Leitura do Sensor de Temperatura" << endl;
                cout << "Em graus Celsius: " << tempSensor->getTemperaturaEmC2() << "°C" << endl;
                cout << "Em graus Kelvin: " << tempSensor->getTemperaturaEmK2() << " °K" << endl;
                cout << "Em graus Fahrenheit: " << tempSensor->getTemperaturaEmF2() << " °F" << endl;
                cout << endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
        

            Luminosidade* lumSensor = dynamic_cast<Luminosidade*>(sensores[4]);
            if (lumSensor != nullptr) {
                lumSensor->atualizarLuminosidade2();  // Atualiza a leitura da luminosidade
                cout << "Leitura do Sensor de Luminosidade: " << lumSensor->getLuminosidade2() << " lumens" << endl; 
                lumSensor->estaClaro2();
                cout<<endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
            
            Umidade* umdSensor = dynamic_cast<Umidade*>(sensores[5]);
            if (umdSensor != nullptr) {
                umdSensor->atualizarUmidade2();  // Atualiza a leitura da umidade
                cout << "Leitura do Sensor de Umidade: " << umdSensor->getUmidadeRelativa2() << " %"<<endl;
                cout<<endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
    } 

    void atualizarAtuadores2() {              
        // Exemplo de lógica para o ventilador
        if (((Temperatura*)sensores[3])->getTemperaturaEmC2() < 25) { // Essa sintáxe de "downcasting" permite pegar o valor do método dentro da classe "Temperatura.cpp" do sensor de Temperatura
            ((Ventilador*)atuadores[4])->setVelocidade(0);                  //"Ventilador está desligado."           
        } else if (((Temperatura*)sensores[3])->getTemperaturaEmC2()>24 && ((Temperatura*)sensores[3])->getTemperaturaEmC2()<=30) { // Temperatura entre 25°C e 30°C
           ((Ventilador*)atuadores[4])->ligar();                            // Liga o ventilador
           ((Ventilador*)atuadores[4])->setVelocidade(2);                   // "Velocidade: média"
        } else if (((Temperatura*)sensores[3])->getTemperaturaEmC2()>30) { // Temperatura maior que 30 °C
           ((Ventilador*)atuadores[4])->ligar();                            // Liga o ventilador
           ((Ventilador*)atuadores[4])->setVelocidade(3);                   // "Velocidade: máxima"
        }

        // Exemplo de Lógica para a lâmpada
        if (((Luminosidade*)sensores[4])->getLuminosidade2()<((Luminosidade*)sensores[4])->getLimiarClaridade()) {
            ((Lampada*)atuadores[5])->setBrilho(true); //Se a luminosidade for menor do que o limiar: liga a lampada
            cout << endl;
            cout << "Lâmpada = Ligado" << endl;
        } else {
            ((Lampada*)atuadores[5])->setBrilho(false); //Se a luminosidade for menor ou igual ao limiar: desliga a lampada
            cout << endl;
            cout << "Lâmpada = Desligado" << endl;
            
        }

        // Lógica para umidificador e desumidificador
        if  (((Umidade*)sensores[5])->getUmidadeRelativa2() < 60) {
            ((Umidificador*)atuadores[6])->setConfiguracao(true);
            ((Desumidificador*)atuadores[7])->setConfiguracao(false);
            cout << endl;
            cout << "Umidificador = Ligado" << endl;
            cout << endl;
            cout << "Desumidificador = Desligado" << endl;
        } else if (((Umidade*)sensores[5])->getUmidadeRelativa2() >= 60 && ((Umidade*)sensores[5])->getUmidadeRelativa2() < 80) {
            ((Umidificador*)atuadores[6])->setConfiguracao(false);
            ((Desumidificador*)atuadores[7])->setConfiguracao(false);
            cout << endl;
            cout << "Umidificador = Desligado" << endl;
            cout << endl;
            cout << "Desumidificador = Desligado" << endl;
        } else if (((Umidade*)sensores[5])->getUmidadeRelativa2() >= 80) {
            ((Umidificador*)atuadores[6])->setConfiguracao(false);
            ((Desumidificador*)atuadores[7])->setConfiguracao(true);
            cout << endl;
            cout << "Umidificador = Desligado" << endl;
            cout << endl;
            cout << "Desumidificador = Ligado" << endl;
        }
    } 

    void atualizarSensores3() {   
            Temperatura* tempSensor = dynamic_cast<Temperatura*>(sensores[6]);
            if (tempSensor != nullptr) {
                tempSensor->atualizarTemperatura3();  // Atualiza a leitura da temperatura
                
                // Exibe os valores de temperatura manualmente aqui
                cout << "Leitura do Sensor de Temperatura" << endl;
                cout << "Em graus Celsius: " << tempSensor->getTemperaturaEmC3() << "°C" << endl;
                cout << "Em graus Kelvin: " << tempSensor->getTemperaturaEmK3() << " °K" << endl;
                cout << "Em graus Fahrenheit: " << tempSensor->getTemperaturaEmF3() << " °F" << endl;
                cout << endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
        

            Luminosidade* lumSensor = dynamic_cast<Luminosidade*>(sensores[7]);
            if (lumSensor != nullptr) {
                lumSensor->atualizarLuminosidade3();  // Atualiza a leitura da luminosidade
                cout << "Leitura do Sensor de Luminosidade: " << lumSensor->getLuminosidade3() << " lumens" << endl; 
                lumSensor->estaClaro3();
                cout<<endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
            
            Umidade* umdSensor = dynamic_cast<Umidade*>(sensores[8]);
            if (umdSensor != nullptr) {
                umdSensor->atualizarUmidade3();  // Atualiza a leitura da umidade
                cout << "Leitura do Sensor de Umidade: " << umdSensor->getUmidadeRelativa3() << " %"<<endl;
                cout<<endl;
            } 
            else {
                cout << "Erro: Sensor de temperatura não encontrado." << endl;
            }
    } 

    void atualizarAtuadores3() {              
        // Exemplo de lógica para o ventilador
        if (((Temperatura*)sensores[6])->getTemperaturaEmC3() < 25) { // Essa sintáxe de "downcasting" permite pegar o valor do método dentro da classe "Temperatura.cpp" do sensor de Temperatura
            ((Ventilador*)atuadores[8])->setVelocidade(0);                  //"Ventilador está desligado."           
        } else if (((Temperatura*)sensores[6])->getTemperaturaEmC3()>24 && ((Temperatura*)sensores[6])->getTemperaturaEmC3()<=30) { // Temperatura entre 25°C e 30°C
           ((Ventilador*)atuadores[8])->ligar();                            // Liga o ventilador
           ((Ventilador*)atuadores[8])->setVelocidade(2);                   // "Velocidade: média"
        } else if (((Temperatura*)sensores[6])->getTemperaturaEmC3()>30) { // Temperatura maior que 30 °C
           ((Ventilador*)atuadores[8])->ligar();                            // Liga o ventilador
           ((Ventilador*)atuadores[8])->setVelocidade(3);                   // "Velocidade: máxima"
        }

        // Exemplo de Lógica para a lâmpada
        if (((Luminosidade*)sensores[7])->getLuminosidade3()<((Luminosidade*)sensores[7])->getLimiarClaridade()) {
            ((Lampada*)atuadores[9])->setBrilho(true); //Se a luminosidade for menor do que o limiar: liga a lampada
            cout << endl;
            cout << "Lâmpada = Ligado" << endl;
        } else {
            ((Lampada*)atuadores[9])->setBrilho(false); //Se a luminosidade for menor ou igual ao limiar: desliga a lampada
            cout << endl;
            cout << "Lâmpada = Desligado" << endl;
            
        }

        // Lógica para umidificador e desumidificador
        if  (((Umidade*)sensores[8])->getUmidadeRelativa3() < 60) {
            ((Umidificador*)atuadores[10])->setConfiguracao(true);
            ((Desumidificador*)atuadores[11])->setConfiguracao(false);
            cout << endl;
            cout << "Umidificador = Ligado" << endl;
            cout << endl;
            cout << "Desumidificador = Desligado" << endl;
        } else if (((Umidade*)sensores[8])->getUmidadeRelativa3() >= 60 && ((Umidade*)sensores[8])->getUmidadeRelativa3() < 80) {
            ((Umidificador*)atuadores[10])->setConfiguracao(false);
            ((Desumidificador*)atuadores[11])->setConfiguracao(false);
            cout << endl;
            cout << "Umidificador = Desligado" << endl;
            cout << endl;
            cout << "Desumidificador = Desligado" << endl;
        } else if (((Umidade*)sensores[8])->getUmidadeRelativa3() >= 80) {
            ((Umidificador*)atuadores[10])->setConfiguracao(false);
            ((Desumidificador*)atuadores[11])->setConfiguracao(true);
            cout << endl;
            cout << "Umidificador = Desligado" << endl;
            cout << endl;
            cout << "Desumidificador = Ligado" << endl;
        }
    }    
};