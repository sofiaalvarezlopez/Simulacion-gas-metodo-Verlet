#include "../inc/Particle.h"


//Definimos el constructor
Particle::Particle(double x0, double y0, double vx0, double vy0, double m0, double r0):
x(x0), y(y0), vx(vx0), vy(vy0), m(m0), r(r0){

    //Definimos aceleraciones iniciales
    Fx = 0.0;
    Fy = 0.0;
    ax = Fx/m;
    ay = Fy/m;

    //Definimos la velocidad al cuadrado
    v = vx*vx + vy*vy;

    //Asignamos los momentos
    px = vx*m;
    py = vy*m;

    //Asignamos las energias
    E_k = m * v/2;
    E_v = 0.0;
}

//Metodo para asignar las paredes del recipiente
void Particle::asignarLimitesPared(double anchoMin0, double anchoMax0, double altoMin0, double altoMax0){
    anchoMin = anchoMin0;
    anchoMax = anchoMax0;
    altoMin = altoMin0;
    altoMax = altoMax0;
}

void Particle::revisarLimitesPared(){

}
