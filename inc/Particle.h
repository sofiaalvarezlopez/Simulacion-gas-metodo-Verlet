#ifndef Particle_H
#define Particle_H

#include <iostream>
#include <vector>
#include <random>

class Particle{
    public:
        //En primer lugar, definimos los metodos constructores y destructores
        Particle();
        ~Particle();
        Particle(double x0, double y0, double vx0, double vy0, double m0, double r0);
        
        //Metodos para asignar los limites del recipiente
        void asignarLimitesPared(double anchoMin_, double anchoMax_, double altoMin_, double altoMax_);
        void revisarLimitesPared();

        //Metodos para obtener las variables masa y radio
        double get_m();
        double get_r();

        //Metodo que obtiene la fuerza de una particula
        double guerzaParticula(Particle &p1, Particle &p2);
        double distancia(double x1, double y1, double x2, double y2);
    private:
        //Definimos las variables de la particula
        double m;
        double r;
        double x;
        double y;
        double t;
        double vx;
        double vy;

        //Constante k de la fuerza
        const double k = 100;

        //Definimos la fuerza de la particula
        double Fx, Fy;
        double ax, ay;

        //Definimos el recipiente en que está la particula
        double anchoMin, anchoMax;
        double altoMin, altoMax;

        //Magnitud Velocidad al cuadrado
        double v;

        //Momentos en x e y
        double px, py;

        //Energias cineticas y potencias
        double E_k, E_v;
};

#endif