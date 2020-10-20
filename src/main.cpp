#include "../inc/Particle.h"
#include "../inc/animacion.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 

using namespace  std;

int main(int argc, char *argv[]){

    ofstream outfile;
    mkdir("./data", 0777);
    outfile.open("./data/momento.dat");
    outfile << "px,py" << endl;

    int numParticulas = std::stoi(argv[1]);

    //cout<<"Este es el num particulas "<< numParticulas<<endl;
    //cout<<"Este es el num arg "<< *argv[1] <<endl;
    Particle *particulas[numParticulas];

    if(numParticulas == 2){
        Particle *particula1 = new Particle(-10.0, 4.0, 40.0, 0.0, 10.0, 5.0);
        particula1->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        Particle *particula2 = new Particle(0.0, 0.0, 0.0, 0.0, 10.0, 5.0);
        particula2->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
//        Particle *particula3 = new Particle(0.0, 10.0, -1.0, 2.0, 10.0, 5.0);
//        particula3->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        particulas[0] = particula1;
        particulas[1] = particula2;
//        particulas[2] = particula3;
    }else{
        //cout<<"esta aca panilla"<<endl;
        double masa = 10.0;
        double radio = 4.0;
        double limiteP = 50.0;
        double limiteV = 100.0;
        srand48(286+177);
        for(int i = 0; i<numParticulas; i++){
            Particle *particulai = new Particle(limiteP*(drand48()-0.5), limiteP*(drand48()-0.5), limiteV*(drand48()-0.5), limiteV*(drand48()-0.5), masa, radio);
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


        outfile << px << ',' << py << endl;

        if(it%iteraciones == 0){
            EndCuadro();
        }

        it++;
        tiempo += deltaTiempo;
    }
    outfile.close();
}