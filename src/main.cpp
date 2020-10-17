#include "../inc/Particle.h"
#include "../inc/animacion.h"

using namespace  std;

int main(){
    int numParticulas = 2;
    Particle *particulas[numParticulas];

    Particle *particula1 = new Particle(-10.0, 4.0, 2.0, 0.0, 10.0, 5.0);
    particula1->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
    Particle *particula2 = new Particle(0.0, 0.0, 0.0, 0.0, 10.0, 5.0);
    particula2->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
    particulas[0] = particula1;
    particulas[1] = particula2;

    double tiempo = 0.0;
    double deltaTiempo = 0.001;
    double tmax = 60;

    const int iteraciones = 100;

    StartAnim();

    int it = 0;
    while(tiempo < tmax){

        if(it%iteraciones == 0){
            //StartCuadro();
        }

        for (int i = 0; i < numParticulas; i++){
            for(int j = 0; j < numParticulas; j++){
                if (i!=j)particulas[i]->fuerzaParticula(*particulas[i], *particulas[j]);
            }
            particulas[i]->moverParticula(tiempo, deltaTiempo, it);

            particulas[i]->revisarLimitesPared();

            if(it%iteraciones == 0){
                //GetPoint(particulas[i]->get_x(), particulas[i]->get_y(), particulas[i]->get_r());
            }
            cout<<i<<" momentoX "<< particulas[i]->get_px() << " momentoY "<< particulas[i]->get_py()<<endl; 
            cout<<i<<" vX "<< particulas[i]->get_vx() << " vY "<< particulas[i]->get_vy()<<endl; 

        }

        if(it%iteraciones == 0){
            //EndCuadro();
        }

        it++;
        tiempo += deltaTiempo;
    }
}