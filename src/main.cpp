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


    //Primer argumento recibido por consola. Corresponde al numero de particulas a simular.
    int numParticulas = std::stoi(argv[1]);
    //Creacion del arreglo, de tamanio numParticulas, donde se almacenan las particulas de la simulacion.
    Particle *particulas[numParticulas];

    //Si se tienen dos particulas, se crea la simulacion con los valores dados en el enunciado.
    if(numParticulas == 2){
        //Creacion de los directorios necesarios para la simulacion
        string filename = "data/2Particulas/";
        filename.append(ctime(&startTime));
        filename.erase(filename.find_last_not_of(" \n\r\t") + 1);
        mkdir("data", 0777);
        mkdir("data/2Particulas", 0777);
        mkdir(filename.c_str(), 0777);
        Particle *particula1 = new Particle(-10.0, 4.0, 40.0, 0.0, 10.0, 5.0, 1, filename);
        particula1->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        Particle *particula2 = new Particle(0.0, 0.0, 0.0, 0.0, 10.0, 5.0, 2, filename);
        particula2->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        //Particle *particula3 = new Particle(0.0, 10.0, -1.0, 2.0, 10.0, 5.0);
        //particula3->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
        particulas[0] = particula1;
        particulas[1] = particula2;
        //particulas[2] = particula3;
    //Si el numero de particulas a generar es diferente de dos, las posiciones y velocidad se generan de manera aleatoria con unos limites.
    }else{
        //Creacion de los directorios necesarios para la simulacion
        string num = to_string(numParticulas);
        string filename = "data/";
        filename.append(num);
        filename.append("Particulas/");
        mkdir("data", 0777);
        mkdir(filename.c_str(), 0777);
        filename.append(ctime(&startTime));
        filename.erase(filename.find_last_not_of(" \n\r\t") + 1);
        mkdir(filename.c_str(), 0777);
        //Masa y radio de cada particula
        double masa = 10.0;
        double radio = 4.0;
        //Limites para la posicion y velocidad de la particula.
        double limiteP = 50.0;
        double limiteV = 100.0;
        srand48(628+717);
        //Se crea el numero de particulas especificadas por el usuario y se ponen los limites de la pared.
        for(int i = 0; i<numParticulas; i++){
            Particle *particulai = new Particle(limiteP*(drand48()-0.5), limiteP*(drand48()-0.5), limiteV*(drand48()-0.5), limiteV*(drand48()-0.5), masa, radio, i, filename);
            particulai->asignarLimitesPared(-50.0, 50.0, -50.0, 50.0);
            particulas[i] = particulai;
        }
    }
    //Tiempo que ha transcurrido en la simulacion
    double tiempo = 0.0;
    //Pasos temporales que recorre nuestra simulacion
    double deltaTiempo = 0.0001;
    //Tiempo, especificado por el usuario, que corresponde a la duracion de la simulacion.
    double tmax = std::stof(argv[2]);
    //Cada 100 iteraciones, mandamos por pipe a gnuplot.
    const int iteraciones = 100;

    StartAnim();

    int it = 0;
    while(tiempo < tmax){
        //Cada 100 iteraciones, mandamos por pipe a gnuplot, por lo que debemos empezar un nuevo cuadro.
        if(it%iteraciones == 0){
            StartCuadro();
        }
        //Calculamos las fuerzas sobre cada particula i.
        for (int i = 0; i < numParticulas; i++) {
            //Empezamos a calcular las fuerzas que siente i por cada particula i + 1, pues no tiene sentido calcular la fuerza consigo mismo.
            for(int j = i + 1; j < numParticulas; j++) {

                particulas[i]->fuerzaParticula(*particulas[i], *particulas[j]);
            }
            //Despues de haber calculado todas las fuerzas que siente la particula i debido al resto de particulas, movemos la particula
            particulas[i]->moverParticula(deltaTiempo, it);
            //Revisamos que la particula no se salga de la caja. Cuando choca con esta, invertimos su velocidad. 
            particulas[i]->revisarLimitesPared();

            if(it%iteraciones == 0){
                //Pasar las particulas a gnuplot
                GetPoint(particulas[i]->get_x(), particulas[i]->get_y(), particulas[i]->get_r());
            }
        }
        //Fin del cuadro actual pintado.
        if(it%iteraciones == 0){
            EndCuadro();
        }
        //Avanzamos en el ciclo.
        it++;
        tiempo += deltaTiempo;
    }
    //Cerramos el archivo que se crea para cada una de las particulas. 
    for (int i = 0; i<numParticulas; i++){
        particulas[i]->cerrarArchivo();
    }
}