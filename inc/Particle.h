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

        //Getters
        double get_m();
        double get_r();
        double get_x();
        double get_y();
        double get_vx();
        double get_vy();
        double get_px();
        double get_py();

        //Metodo que obtiene la fuerza de una particula
        void fuerzaParticula(Particle &p1, Particle &p2);
        void fuerza0();
        double distancia(double x1, double y1, double x2, double y2);


        //Metodo para mover la particula
        void moverParticula(double tiempo, double deltaTiempo, int iteracion);

    private:
        //Definimos las variables de la particula
        double x;
        double y;
        double vx;
        double vy;
        double m;
        double r;

        double t;

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