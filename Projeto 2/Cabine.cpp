#include <iostream>
#include "Sensor.cpp"               
#include "ControlesDeVoo.cpp"       
//Atuadores:
#include "Motores.cpp"              
#include "Profundor.cpp"            
#include "Flaps.cpp"                
#include "Ailerons.cpp"             
//Sensores:
#include "Velocidade.cpp"
#include "Altimetro.cpp"
#include "Bussola.cpp"
#include "Radar.cpp"
using namespace std;

class Cabine {
private:
    ControlesDeVoo *atuadores[12];
    Sensor *sensores[9];

public:
    Cabine(){} //Construtor padrão (sem parâmetros)
    Cabine(string velocidade, string altimetro, string bussola, string radar, string motor, string ailerons, string profundor, string flaps) {

        // Inicializar os sensores e atuadores como ponteiros
        sensores[0] = new Velocidade("velocidade");
        sensores[1] = new Altimetro("altimetro");
        sensores[2] = new Bussola("bussola");
        sensores[3] = new Radar("radar");

        //Inicializando os atuadores
        atuadores[0] = new Motores("motor");            //atuador dos motores
        atuadores[1] = new Ailerons("ailerons");        //atuador dos ailerons
        atuadores[2] = new Profundor("profundor");      //atuador do profundor
        atuadores[3] = new Flaps("flaps");              //atuador dos flaps

        // Pode inicializar mais sensores e atuadores conforme necessário   
    }

    //Limpar o lixo de memória de atuadores e sensores
    ~Cabine() {
    // Desaloca a memória de sensores
        for (int i = 0; i < 9; i++) {
            if (sensores[i] != nullptr) {
                delete sensores[i];
            }
        }
    // Desaloca a memória de atuadores
        for (int i = 0; i < 12; i++) {
            if (atuadores[i] != nullptr) {
                delete atuadores[i];
            }
        }
    }

    //Atualiza sensores para a Subida
    void atualizarSensoresS() {   
        // Faz um cast dinâmico para garantir que sensores[0] seja do tipo Velocidade
        Velocidade* veloSensor = dynamic_cast<Velocidade*>(sensores[0]);
        // Faz um cast dinâmico para garantir que atuadores[0] seja do tipo Motores
        Motores* motores = dynamic_cast<Motores*>(atuadores[0]);

            if (veloSensor != nullptr && motores != nullptr) { // Verifica se ambos os casts foram bem-sucedidos
                if (motores->getPotenciaMotor() <= 70) {
                    veloSensor->conectar(); // Conecta o sensor de velocidade
                    veloSensor->ligar(); // Liga o sensor de velocidade
                    motores->ligar();    // Liga os motores
                    // Atualiza a velocidade com base na potência do motor
                    veloSensor->atualizarVelocidade1();
                    cout << "Velocidade: " << veloSensor->getVelocidade() << " Nós" << endl;
                } else if (motores->getPotenciaMotor() > 70) {
                    veloSensor->atualizarVelocidade2();
                    cout << "Velocidade: " << veloSensor->getVelocidade() << " Nós" << endl;
                }
                else {
                    cout << "Erro: Não foi possível acessar o sensor ou o motor." << endl;
                }
            }
    
            Altimetro* altSensor = dynamic_cast<Altimetro*>(sensores[1]);
            if (altSensor != nullptr) {
                if(((Altimetro*)sensores[1])->getAltitude() < 36000 && ((Velocidade*)sensores[0])->getVelocidade() < 170){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->atualizarAltitude1();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                    cout << "Decolagem iniciada!"<< endl;
                }
                else if(((Altimetro*)sensores[1])->getAltitude() < 36000 && ((Velocidade*)sensores[0])->getVelocidade() >= 170){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude2();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                    cout << "Subindo!"<< endl;
                }
                else if(((Altimetro*)sensores[1])->getAltitude() <= 36000 && ((Velocidade*)sensores[0])->getVelocidade() < 250){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude2();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                }
                else if((((Altimetro*)sensores[1])->getAltitude() >= 36000 && ((Velocidade*)sensores[0])->getVelocidade() >= 210) && ((Velocidade*)sensores[0])->getVelocidade() <= 250){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude1();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                    altSensor->altitudeCruzeiro();
                }
            } 
            else {
                cout << "Erro: Sensor de Altitude não encontrado." << endl;
            }
            
            Bussola* busSensor = dynamic_cast<Bussola*>(sensores[2]);
            if (busSensor != nullptr) {
                busSensor->conectar();
                busSensor->ligar();
                busSensor->atualizarOrientacao1();  // Atualiza a leitura da bussola
                cout << "Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                cout<<endl;
            } 
            else {
                cout << "Erro: Bussola não encontrada." << endl;
            }

            Radar* radSensor = dynamic_cast<Radar*>(sensores[3]);
            if (radSensor != nullptr) {
                if(((Altimetro*)sensores[1])->getAltitude() == 36000 && ((Velocidade*)sensores[0])->getVelocidade() == 250){
                    radSensor->conectar();
                    radSensor->ligar();
                    radSensor->objetoDetectado(); // Chama objetoDetectado antes de setColisao
                    cout << "Radar: " << radSensor->getColisao(); 
                }
            } 
            else {
                cout << "Erro: Radar não encontrado." << endl;
            }
    }

    void atualizarAtuadoresS() {   
        Motores* motAtuador = dynamic_cast<Motores*>(atuadores[0]);
        Ailerons* aileAtuador = dynamic_cast<Ailerons*>(atuadores[1]);
        Profundor* profAtuador = dynamic_cast<Profundor*>(atuadores[2]);
        Flaps* flapAtuador = dynamic_cast<Flaps*>(atuadores[3]);

        if (((Velocidade*)sensores[0])->getVelocidade() < 170) {         //Downcasting para acessar o método específico da classe Velocidade
            ((Motores*)atuadores[0])->setPotenciaMotor(95);              //Downcasting para acessar o método específico da classe Motores (Potência de subida)
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl; 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(4);                  //"Flaps posição 4" 
            cout << flapAtuador->exibirPosicoes() <<endl; 
            ((Profundor*)atuadores[2])->setPosicao(1);                   //Profundor alinhado 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;    

        } else if (((Velocidade*)sensores[0])->getVelocidade()>=170 && ((Velocidade*)sensores[0])->getVelocidade()<=180) { // Velocidade entre 170 e 180 nós
            ((Motores*)atuadores[0])->setPotenciaMotor(95);
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(3);                  //"Flaps posição 3"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(2);                   //Profundor para cima, o avião sobe
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;

        } else if (((Velocidade*)sensores[0])->getVelocidade()>180 && ((Velocidade*)sensores[0])->getVelocidade()<=190) { // Velocidade entre 180 e 190 nós
            ((Motores*)atuadores[0])->setPotenciaMotor(95);              //Potência de subida
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(2);                  //"Flaps posição 2"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(2);                   //Profundor para cima, o avião sobe
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;
        }
        else if (((Velocidade*)sensores[0])->getVelocidade()>190 && ((Velocidade*)sensores[0])->getVelocidade()<=200) { // Velocidade entre 190 e 200 nós
            ((Motores*)atuadores[0])->setPotenciaMotor(95);              //Potência de subida
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(1);                  //"Flaps posição 1"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(2);                   //Profundor para cima, o avião sobe
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;
        }
         else if (((Velocidade*)sensores[0])->getVelocidade()>200 && ((Velocidade*)sensores[0])->getVelocidade()<250) {    // Velocidade entre 200 e 250 Nós
            ((Motores*)atuadores[0])->setPotenciaMotor(95);              //Potência de subida
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Radar*)sensores[3])->setColisao(19);                       //Objeto está distante
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(2);                   //Profundor alinhado, o avião para de subir
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;
        }
        else if (((Velocidade*)sensores[0])->getVelocidade()==250) {     //Velocidade igual a 250 Nós
            ((Motores*)atuadores[0])->setPotenciaMotor(65);              //Potência de subida
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Radar*)sensores[3])->setColisao(15);                       //Objeto está se aproximando 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(2);                   //Profundor alinhado, o avião para de subir
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;
        }
    } 

    //Atualiza sensores para a Subida
    void atualizarSensoresT(int i) {   
            Velocidade* veloSensor = dynamic_cast<Velocidade*>(sensores[0]);
            if (veloSensor != nullptr) {
                veloSensor->conectar(); // Conecta o sensor de velocidade
                veloSensor->ligar(); // Liga o sensor de velocidade
                veloSensor->atualizarVelocidade1();  // Atualiza a leitura da Velocidade
                cout << "Velocidade de cruzeiro: " << veloSensor->getVelocidade() << " Nós" << endl;
            } 
            else {
                cout << "Erro: Sensor de Velocidade não encontrado." << endl;
            }
        
            Altimetro* altSensor = dynamic_cast<Altimetro*>(sensores[1]);
            if (altSensor != nullptr) {
                altSensor->conectar();
                altSensor->ligar();
                altSensor->atualizarAltitude1();  // Atualiza a leitura da Altitude
                altSensor->altitudeCruzeiro();    // Altitude de cruzeiro
            } 
            else {
                cout << "Erro: Sensor de Altitude não encontrado." << endl;
            }
            
            Bussola* busSensor = dynamic_cast<Bussola*>(sensores[2]);
            if (busSensor != nullptr) {
                busSensor->conectar();
                busSensor->ligar();
                    if (i<10){
                        busSensor->atualizarOrientacao1();  // Atualiza a leitura da bussola
                        cout <<"Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                        cout << "Seguindo em frente!" << endl; 
                        cout << endl;
                    }
                    else if (i>=10 && i<20){
                        busSensor->atualizarOrientacao2();  // Atualiza a leitura da bussola
                        cout <<"Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                        cout << "Curva para a direita!" << endl; 
                        cout << endl;
                    }
                    else if (i>=20 && i<30){
                        busSensor->atualizarOrientacao1();  // Atualiza a leitura da bussola
                        cout <<"Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                        cout << "Seguindo em frente!" << endl; 
                        cout << endl;
                    }
                    else if (i>=30 && i<40){
                        busSensor->atualizarOrientacao2();  // Atualiza a leitura da bussola
                        cout <<"Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                        cout << "Curva para a direita!" << endl; 
                        cout << endl;
                    }
                    else if (i>=40 && i<50){
                        busSensor->atualizarOrientacao3();  // Atualiza a leitura da bussola
                        cout << "Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                        cout << "Curva para a esquerda!" << endl; 
                        cout << endl;
                       
                }
            } 
            else {
                cout << "Erro: Bussola não encontrada." << endl;
            }

            Radar* radSensor = dynamic_cast<Radar*>(sensores[3]);
            if (radSensor != nullptr) {
                if(((Altimetro*)sensores[1])->getAltitude() == 36000 && ((Velocidade*)sensores[0])->getVelocidade() == 250){
                    radSensor->conectar();
                    radSensor->ligar();
                    radSensor->objetoDetectado(); // Chama objetoDetectado antes de setColisao
                    cout << "Radar: " << radSensor->getColisao(); 
                }
            } 
            else {
                cout << "Erro: Radar não encontrado." << endl;
            }
    }

    void atualizarAtuadoresT(int i) {   
        Motores* motAtuador = dynamic_cast<Motores*>(atuadores[0]);
        Ailerons* aileAtuador = dynamic_cast<Ailerons*>(atuadores[1]);
        Profundor* profAtuador = dynamic_cast<Profundor*>(atuadores[2]);
        Flaps* flapAtuador = dynamic_cast<Flaps*>(atuadores[3]);

        if (i<10) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de cruzeiro
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl; 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0" 
            cout << flapAtuador->exibirPosicoes() <<endl; 
            ((Profundor*)atuadores[2])->setPosicao(1);                   //Profundor alinhado 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl; 
        }   
        else if (i >= 10 && i < 20) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de cruzeiro
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl; 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0" 
            cout << flapAtuador->exibirPosicoes() <<endl; 
            ((Profundor*)atuadores[2])->setPosicao(1);                   //Profundor alinhado 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(2);            //Aileron direito para cima, aileron esquerdo para baixo, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao curva para a direita" << endl;   
        }  
        else if (i >= 20 && i <30) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de cruzeiro
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl; 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0" 
            cout << flapAtuador->exibirPosicoes() <<endl; 
            ((Profundor*)atuadores[2])->setPosicao(1);                   //Profundor alinhado 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl; 
        }  
        else if (i >= 30 && i <40) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de cruzeiro
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl; 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0" 
            cout << flapAtuador->exibirPosicoes() <<endl; 
            ((Profundor*)atuadores[2])->setPosicao(1);                   //Profundor alinhado 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(2);            //Aileron direito para cima, aileron esquerdo para baixo, avião vira para a esquerda
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao curva para a direita" << endl;  
        } 
        else if (i >= 40 && i <50) { // Essa sintáxe de "downcasting" permite pegar o valor do método dentro da classe "Velocidade.cpp" do sensor de Velocidade
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de cruzeiro
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl; 
            ((Flaps*)atuadores[3])->setPosicaoFlaps(0);                  //"Flaps posição 0" 
            cout << flapAtuador->exibirPosicoes() <<endl; 
            ((Profundor*)atuadores[2])->setPosicao(1);                   //Profundor alinhado 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(0);            //Aileron esquerdo para cima, aileron direito para baixo, avião vira a esquerda
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao curva para a esquerda" << endl;    
        }    
    } 

    void atualizarSensoresD() {   
            Velocidade* veloSensor = dynamic_cast<Velocidade*>(sensores[0]);
            if (veloSensor != nullptr) {
                if(((Motores*)atuadores[0])->getPotenciaMotor() > 70){
                    veloSensor->conectar();
                    veloSensor->ligar();
                    veloSensor->atualizarVelocidade1();  // Atualiza a leitura da Velocidade
                    cout << "Velocidade: " << veloSensor->getVelocidade() << " Nós" << endl;
                }
                else if(((Motores*)atuadores[0])->getPotenciaMotor() <= 70 && ((Motores*)atuadores[0])->getPotenciaMotor() > 0){
                    veloSensor->conectar();
                    veloSensor->ligar();
                    veloSensor->atualizarVelocidade3();  // Atualiza a leitura da Velocidade
                    cout << "Velocidade: " << veloSensor->getVelocidade() << " Nós" << endl;
                }
                else if(((Motores*)atuadores[0])->getPotenciaMotor() == 0 && ((Velocidade*)sensores[0])->getVelocidade() > 0){
                    veloSensor->conectar();
                    veloSensor->ligar();
                    veloSensor->atualizarVelocidade3();  // Atualiza a leitura da Velocidade
                    cout << "Velocidade: " << veloSensor->getVelocidade() << " Nós" << endl;
                }
                else if(((Motores*)atuadores[0])->getPotenciaMotor() == 0 && ((Velocidade*)sensores[0])->getVelocidade() == 0){
                    veloSensor->desconectar();
                    veloSensor->desligar();
                    cout << "Ladies and gentlemen, já podem desafivelar os cintos."<< endl;
                }   
            } 
            else {
                cout << "Erro: Sensor de Velocidade não encontrado." << endl;
            }
        
            Altimetro* altSensor = dynamic_cast<Altimetro*>(sensores[1]);
            if (altSensor != nullptr) {
                if(((Altimetro*)sensores[1])->getAltitude() <= 36500 && ((Altimetro*)sensores[1])->getAltitude() > 28000){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude3();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                }
                else if(((Altimetro*)sensores[1])->getAltitude() <= 28000 && ((Altimetro*)sensores[1])->getAltitude() > 12000){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude4();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                }
                else if(((Altimetro*)sensores[1])->getAltitude() <=12000 && ((Altimetro*)sensores[1])->getAltitude() > 10000){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude3();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                }
                else if(((Altimetro*)sensores[1])->getAltitude() <= 10000 && ((Altimetro*)sensores[1])->getAltitude() >= 250){
                    altSensor->conectar();            // conecta o sensor de altitude
                    altSensor->ligar();               // Liga o sensor de altitude
                    altSensor->atualizarAltitude5();  // Atualiza a leitura da Altitude
                    cout << "Altitude: " << altSensor->getAltitude() << " Pés" << endl;
                    cout << "Senhores passageiros, preparar para o pouso."<< endl;
                }
                else if(((Altimetro*)sensores[1])->getAltitude() < 250){
                    Bussola* busSensor = dynamic_cast<Bussola*>(sensores[2]);
                    Radar* radSensor = dynamic_cast<Radar*>(sensores[3]);
                    //Desconectando e desligando todos os sensores
                    altSensor->desconectar();            
                    altSensor->desligar();               
                    busSensor->desconectar();
                    busSensor->desligar();
                    radSensor->desconectar();
                    radSensor->desligar();
                    cout << "Senhores passageiros, a águia pousou."<< endl;
                }
            } 
            else {
                cout << "Erro: Sensor de Altitude não encontrado." << endl;
            }
            
            Bussola* busSensor = dynamic_cast<Bussola*>(sensores[2]);
            if (busSensor != nullptr) {
                busSensor->conectar();
                busSensor->ligar();
                busSensor->atualizarOrientacao1();  // Atualiza a leitura da bussola
                cout << "Bussola: " << busSensor->getOrientacao() << "°"<<endl;
                cout<<endl;
            } 
            else {
                cout << "Erro: Bussola não encontrada." << endl;
            }
    }

    void atualizarAtuadoresD() {   
        Motores* motAtuador = dynamic_cast<Motores*>(atuadores[0]);
        Ailerons* aileAtuador = dynamic_cast<Ailerons*>(atuadores[1]);
        Profundor* profAtuador = dynamic_cast<Profundor*>(atuadores[2]);
        Flaps* flapAtuador = dynamic_cast<Flaps*>(atuadores[3]);

        if (((Velocidade*)sensores[0])->getVelocidade() > 210  && (((Altimetro*)sensores[1])->getAltitude() > 0)) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de descida (Velocidade começa a ser reduzida)
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(1);                  //"Flaps posição 10°"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para baixo 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;        
        }

        else if(((Velocidade*)sensores[0])->getVelocidade() > 200 && ((Velocidade*)sensores[0])->getVelocidade() <= 210 && (((Altimetro*)sensores[1])->getAltitude() > 0)){
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de descida (Velocidade começa a ser reduzida)
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(2);                  //"Flaps posição 20°"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para baixo 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;      
        }
        else if(((Velocidade*)sensores[0])->getVelocidade() > 180 && ((Velocidade*)sensores[0])->getVelocidade() <= 200 && (((Altimetro*)sensores[1])->getAltitude() > 0)){
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de descida (Velocidade começa a ser reduzida)
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(2);                  //"Flaps posição 30°"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para baixo 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;      
        }
        else if(((Velocidade*)sensores[0])->getVelocidade() > 160 && ((Velocidade*)sensores[0])->getVelocidade() <= 180 && (((Altimetro*)sensores[1])->getAltitude() > 0)){
            ((Motores*)atuadores[0])->setPotenciaMotor(70);              //Potência de descida (Velocidade começa a ser reduzida)
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(3);                  //"Flaps posição 30°"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para baixo 
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl;      
        }
        else if (((Velocidade*)sensores[0])->getVelocidade() == 160 && (((Altimetro*)sensores[1])->getAltitude() > 0)) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(75);
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(4);                  //"Flaps posição 0"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para cima
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl; 
        }
        else if (((Velocidade*)sensores[0])->getVelocidade() > 0 && (((Altimetro*)sensores[1])->getAltitude() == 0)) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(0);
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(4);                  //"Flaps posição 0"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para baixo
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl; 
        }
        else if (((Velocidade*)sensores[0])->getVelocidade() == 0 && (((Altimetro*)sensores[1])->getAltitude() == 0)) { 
            ((Motores*)atuadores[0])->setPotenciaMotor(0);
            cout <<"Potencia Motor: " << motAtuador->getPotenciaMotor() << "%" << endl;
            ((Flaps*)atuadores[3])->setPosicaoFlaps(4);                  //"Flaps posição 0"
            cout << flapAtuador->exibirPosicoes() <<endl;
            ((Profundor*)atuadores[2])->setPosicao(0);                   //Profundor para baixo
            cout << profAtuador->exibirPosicao() <<endl;
            ((Ailerons*)atuadores[1])->setPosicaoAilerons(1);            //Ailerons alinhados, avião segue reto
            cout << aileAtuador->exibirPosicoes() << endl << "Aviao segue em frente" << endl; 
        }
    } 
   
};