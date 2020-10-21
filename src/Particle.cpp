#include "../inc/Particle.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace  std;

//Definimos el constructor
Particle::Particle(double x0, double y0, double vx0, double vy0, double m0, double r0, int ID0, string path):
x(x0), y(y0), vx(vx0), vy(vy0), m(m0), r(r0), ID(ID0){

    //Abrimos el archivo

    string filename = path;
    filename.append("/Particula" + to_string(ID) + ".dat");
    archivo.open(filename);

    archivo << "x,y,vx,vy,v,ax,ay,px,py,Fx,Fy,Ek,Ev,m,r"<<endl;

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

//Getters
double Particle::get_m(){
    return m;
}
double Particle::get_r(){
    return r;
}
double Particle::get_x(){
    return x;
}
double Particle::get_y(){
    return y;
}
double Particle::get_vx(){
    return vx;
}
double Particle::get_vy(){
    return vy;
}
double Particle::get_px(){
    return px;
}
double Particle::get_py(){
    return py;
}


//Metodo para asignar las paredes del recipiente
void Particle::asignarLimitesPared(double anchoMin0, double anchoMax0, double altoMin0, double altoMax0){
    anchoMin = anchoMin0;
    anchoMax = anchoMax0;
    altoMin = altoMin0;
    altoMax = altoMax0;
}

void Particle::revisarLimitesPared(){
    if((x+r) >= anchoMax|| (x-r) <= anchoMin){
        vx = -vx;
    }
    if((y+r) >= altoMax|| (y-r) <= altoMin){
        vy = -vy;
    }
}

//Metodo para obtener la distancia
double Particle::distancia(double x1, double y1, double x2, double y2){
    double distancia = 0.0;
    double deltaX = x1-x2;
    double deltaY = y1-y2;
    distancia = sqrt(deltaX*deltaX+deltaY*deltaY);
    return distancia;
}

//Metodo para calcular fuerzas
void Particle::fuerzaParticula(Particle &p1, Particle &p2){
    double dist = distancia(p1.x, p1.y, p2.x, p2.y);
    double verificacion = p1.r + p2.r - dist;

    if(verificacion > 0.0){
        double fuerzaNormal = k*pow(verificacion,3);
        //cout<<"se chocaron"<<endl;
        //Calculamos las componentes x e y del vector fuerza
        p1.Fx -= fuerzaNormal*(p2.x - p1.x)/dist;
        p1.Fy -= fuerzaNormal*(p2.y - p1.y)/dist;

        p1.ax += p1.Fx/p1.m;
        p1.ay += p1.Fy/p1.m;

        p2.Fx += fuerzaNormal*(p2.x - p1.x)/dist;
        p2.Fy += fuerzaNormal*(p2.y - p1.y)/dist;

        p2.ax += p2.Fx/p2.m;
        p2.ay += p2.Fy/p2.m;

        E_v = - k * pow(verificacion, 4)/4;
    }
}

void Particle::fuerza0(){
    Fx = 0.0;
    Fy = 0.0;

    ax = 0.0;
    ay = 0.0;

    E_v = 0.0;
}

//Metodo para mover la particula
void Particle::moverParticula(double tiempo, double deltaTiempo, int iteracion){
    t = tiempo;

    if(iteracion == 0) return;

    x += vx*deltaTiempo + ax*deltaTiempo*deltaTiempo/2;
    y += vy*deltaTiempo + ay*deltaTiempo*deltaTiempo/2;

    vx += ax*deltaTiempo;
    vy += ay*deltaTiempo;

    v = vx*vx+vy*vy;
    E_k = m*v/2;

    px=m*vx;
    py=m*vy;
    
    archivo << x << ',' << y << ',' << vx << ',' << vy << ',' << sqrt(v) << ',' << ax << ',' << ay << ',' 
    << px << ',' << py << ',' << Fx << ',' << Fy << ',' << E_k << ',' << E_v << ',' << m << ',' << r << endl;

    fuerza0();
}


//Cerrar outstream
void Particle::cerrarArchivo(){
    archivo.close();
}

//Destructor
Particle::~Particle(){

}

//Conclusion ¿el momento se crea? 