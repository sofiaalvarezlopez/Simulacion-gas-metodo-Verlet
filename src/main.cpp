#include "../inc/Particle.h"
#include "../inc/animacion.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <chrono>
#include <ctime>  
#include <string>
#include <cstdio>
using namespace  std;

int main(int argc, char *argv[]){
    //Tomamos un tiempo inicial para crear la carpeta de la simulacion actual, donde se almacenan los datos
    auto start = std::chrono::system_clock::now();
    std::time_t startTime = std::chrono::system_clock::to_time_t(start);

    //Creacion de los directorios necesarios para la simulacion
    string filename = "data/";
    filename.append(ctime(&startTime));
    filename.erase(filename.find_last_not_of(" \n\r\t") + 1);
    mkdir("data", 0777);
    mkdir(filename.c_str(), 0777);

    //Primer argumento recibido por consola. Corresponde al numero de particulas a simular.
    int numParticulas = std::stoi(argv[1]);
    //Creacion del arreglo, de tamanio numParticulas, donde se almacenan las particulas de la simulacion.
    Particle *particulas[numParticulas];

    //Si se tienen dos particulas, se crea la simulacion con los valores dados en el enunciado.
    if(numParticulas == 2){
        Particle *particula1 = new Particle(-10.0, 4.0, 40.0, 0.0, 10.0, 5.0, 1, filename);
        particula1->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        Particle *particula2 = new Particle(0.0, 0.0, 0.0, 0.0, 10.0, 5.0, 2, filename);
        particula2->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        //Particle *particula3 = new Particle(0.0, 10.0, -1.0, 2.0, 10.0, 5.0);
        //particula3->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        particulas[0] = particula1;
        particulas[1] = particula2;
        //particulas[2] = particula3;
    //
    }else{
        double masa = 10.0;
        double radio = 4.0;
        double limiteP = 50.0;
        double limiteV = 100.0;
        srand48(286+177);
        for(int i = 0; i<numParticulas; i++){
            Particle *particulai = new Particle(limiteP*(drand48()-0.5), limiteP*(drand48()-0.5), limiteV*(drand48()-0.5), limiteV*(drand48()-0.5), masa, radio, i, filename);
            particulai->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
            particulas[i] = particulai;
        }
    }

    double tiempo = 0.0;
    double deltaTiempo = 0.0001;
    double tmax = std::stof(argv[2]);

    const int iteraciones = 100;

    StartAnim();

    int it = 0;
    while(tiempo < tmax){

        if(it%iteraciones == 0){
            StartCuadro();
        }
        double px = 0.0;
        double py = 0.0;
        for (int i = 0; i < numParticulas; i++){
            for(int j = i + 1; j < numParticulas; j++){
                particulas[i]->fuerzaParticula(*particulas[i], *particulas[j]);
            }

            //cout<<"Velocidad " << particulas[i]->get_vx() << " " << particulas[i]->get_vy() <<endl;

            //cout<<"Moviendo particula " << i <<endl;
            particulas[i]->moverParticula(tiempo, deltaTiempo, it);

            particulas[i]->revisarLimitesPared();

            px += particulas[i]->get_px();
            py += particulas[i]->get_py();

            if(it%iteraciones == 0){
                //cout<<"Entro y se mueve"<<endl;
                GetPoint(particulas[i]->get_x(), particulas[i]->get_y(), particulas[i]->get_r());
            }
            //cout<<i<<" momentoX "<< particulas[i]->get_px() << " momentoY "<< particulas[i]->get_py()<<endl; 
            //cout<<i<<" vX "<< particulas[i]->get_vx() << " vY "<< particulas[i]->get_vy()<<endl; 
        }


        //outfile << px << ',' << py << endl;

        if(it%iteraciones == 0){
            EndCuadro();
        }

        it++;
        tiempo += deltaTiempo;
    }

    for (int i = 0; i<numParticulas; i++){
        particulas[i]->cerrarArchivo();
    }
}