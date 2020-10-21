#ifndef Particle_H
#define Particle_H

#include <iostream>
#include <vector>
#include <random>
#include <fstream>

#include <string>

using namespace  std;

//Define los metodos y atributos que tendra la clase Particle.
class Particle{
    public:
        //En primer lugar, definimos los metodos constructores y destructores
        Particle();
        ~Particle();
        //Definimos el constructor de la clase Particula.
        //@param: x0: posicion inicial en x de la particula
        //@param: y0: posicion inicial en y de la particula
        //@param: vx0: velocidad inicial en x de la particula
        //@param: vy0: velocidad inicial en y de la particula
        //@param: m0: masa de la particula
        //@param: r0: radio de la particula
        //@param: ID0: identificador unico de la particula.
        Particle(double x0, double y0, double vx0, double vy0, double m0, double r0, int ID0, string path);
        
        //Metodos para asignar los limites del recipiente
        //@param: anchoMin0: Valor minimo del recipiente en x.
        //@param: anchoMax0: Valor maximo del recipiente en x.
        //@param: altoMin0: Valor minimo del recipiente en y (base).
        //@param: altoMax0: Valor maximo del recipiente en y (altura).
        void asignarLimitesPared(double anchoMin_, double anchoMax_, double altoMin_, double altoMax_);

        //Revisa que la particula no se vaya a salir de la pared en la que esta contenida. 
        //Cuando la posicion actual de la particula (medida en el centro) sumado con su radio sobrepasa o es menor a los limites de la pared, se invierten las velocidades.
        //Al invertir las velocidades, la particula rebota.
        void revisarLimitesPared();

        //Getters
        //Retorna la masa de la particula
        double get_m();
        //Retorna el radio de la particula
        double get_r();
        //Retorna la posicion en x de la particula
        double get_x();
        //Retorna la posicion en y de la particula
        double get_y();
        //Retorna la velocidad en x de la particula
        double get_vx();
        //Retorna la velocidad en y de la particula
        double get_vy();
        //Retorna el momento en x de la particula
        double get_px();
        //Retorna el momento en y de la particula
        double get_py();
        //Retorna la energia cinetica de la particula
        double get_Ek();
        //Retorna la energia potencial de la particula
        double get_Ev();

        //Metodo para calcular las fuerzas que siente una particula debido a otra.
        void fuerzaParticula(Particle &p1, Particle &p2);
        //Metodo que hace que todas las fuerzas, aceleraciones y la energia potencial se vuelvan 0. Es decir, "reinicia" estos valores.
        void fuerza0();
        //Metodo para obtener la distancia entre dos particulas
        //@param: x1: Posicion en x de la particula 1.
        //@param: y1: Posicion en y de la particula 1.
        //@param: x2: Posicion en x de la particula 2.
        //@param: y1: Posicion en y de la particula 2.
        double distancia(double x1, double y1, double x2, double y2);

        //Metodo para mover la particula utilizando el algoritmo de Verlet. Se evoluciona el sistema usando un tiempo y un deltaTiempo determinados para evolucionar el sistema adecuadamente.
        //@param deltaTiempo: evolucion del sistema en un intervalo de tiempo
        //@param iteracion: Numero de la iteracion en la cual se esta
        void moverParticula(double deltaTiempo, int iteracion);

        //Cerrar archivo
        void cerrarArchivo();

    private:
        //Definimos los atributos de la particula
        //Posicion en x de la particula
        double x;
        //Posicion en y de la particula
        double y;
        //Velocidad en x de la particula
        double vx;
        //Velocidad en y de la particula
        double vy;
        //Masa de la particula
        double m;
        //Radio de la particula
        double r;
        //Numero de identificacion de la particula
        int ID;

        //Atributo de archivo
        ofstream archivo;

        //Constante k de la fuerza en N/m^3
        const double k = 100;

        //Fuerza en x, y de la particula
        double Fx, Fy;
        //Aceleracion en x, y de la particula
        double ax, ay;

        //Definimos los limites en x del recipiente en que está la particula
        double anchoMin, anchoMax;
        //Definimos los limites en y del recipiente en que está la particula
        double altoMin, altoMax;

        //Magnitud de la velocidad al cuadrado
        double v;

        //Momentos en x,y de la particula
        double px, py;

        //Energia cinetica y potencial de la particula
        double E_k, E_v;
};

#endif