#ifndef Particle_H
#define Particle_H

#include <iostream>
#include <vector>
#include <random>

class Particle{
    public:
        Particle();
        ~Particle();
        Particle(double x0, double y0, double vx0, double vy0, double m, double r);
        double Get_m();
        double Get_r();
    private:
        double m;
        double r;
        double x;
        double y;
        double t;
        double vx;
        double vy;
        double a;

};

#endif