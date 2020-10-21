#include "../inc/Particle.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace  std;

//Definimos el constructor de la clase Particula.
//@param: x0: posicion inicial en x de la particula
//@param: y0: posicion inicial en y de la particula
//@param: vx0: velocidad inicial en x de la particula
//@param: vy0: velocidad inicial en y de la particula
//@param: m0: masa de la particula
//@param: r0: radio de la particula
//@param: ID0: identificador unico de la particula.
Particle::Particle(double x0, double y0, double vx0, double vy0, double m0, double r0, int ID0, string path):
x(x0), y(y0), vx(vx0), vy(vy0), m(m0), r(r0), ID(ID0){

    //Creamos el archivo
    string filename = path;
    filename.append("/Particula" + to_string(ID) + ".dat");
    archivo.open(filename);
    //Linea que indica el encabezado del archivo.
    archivo << "x,y,vx,vy,v,ax,ay,px,py,Fx,Fy,Ek,Ev,m,r"<<endl;

    //Definimos fuerzas y aceleraciones iniciales en x,y
    Fx = 0.0;
    Fy = 0.0;
    ax = Fx/m;
    ay = Fy/m;

    //Definimos la velocidad al cuadrado
    v = vx*vx + vy*vy;

    //Asignamos los momentos
    px = vx*m;
    py = vy*m;

    //Asignamos las energias cinetica y potencial.
    E_k = m * v/2;
    E_v = 0.0;
}

//Getters de los atributos de la clase.
//Retorna la masa de la particula
double Particle::get_m(){
    return m;
}
//Retorna el radio de la particula
double Particle::get_r(){
    return r;
}
//Retorna la posicion en x de la particula
double Particle::get_x(){
    return x;
}
//Retorna la posicion en y de la particula
double Particle::get_y(){
    return y;
}
//Retorna la velocidad en x de la particula
double Particle::get_vx(){
    return vx;
}
//Retorna la velocidad en y de la particula
double Particle::get_vy(){
    return vy;
}
//Retorna el momento en x de la particula
double Particle::get_px(){
    return px;
}
//Retorna el momento en y de la particula
double Particle::get_py(){
    return py;
}
//Retorna la energia potencial de la particula
double  Particle::get_Ev(){
    return E_v;
}
//Retorna la energia cinetica de la particula
double Particle::get_Ek(){
    return E_k;
}

//Metodo para asignar las paredes del recipiente.
//@param: anchoMin0: Valor minimo del recipiente en x.
//@param: anchoMax0: Valor maximo del recipiente en x.
//@param: altoMin0: Valor minimo del recipiente en y (base).
//@param: altoMax0: Valor maximo del recipiente en y (altura).
void Particle::asignarLimitesPared(double anchoMin0, double anchoMax0, double altoMin0, double altoMax0){
    anchoMin = anchoMin0;
    anchoMax = anchoMax0;
    altoMin = altoMin0;
    altoMax = altoMax0;
}
//Revisa que la particula no se vaya a salir de la pared en la que esta contenida. 
//Cuando la posicion actual de la particula (medida en el centro) sumado con su radio sobrepasa o es menor a los limites de la pared, se invierten las velocidades.
//Al invertir las velocidades, la particula rebota.
void Particle::revisarLimitesPared(){
    if((x+r) >= anchoMax|| (x-r) <= anchoMin){
        vx = -vx;
    }
    if((y+r) >= altoMax|| (y-r) <= altoMin){
        vy = -vy;
    }
}

//Metodo para obtener la distancia entre dos particulas
//@param: x1: Posicion en x de la particula 1.
//@param: y1: Posicion en y de la particula 1.
//@param: x2: Posicion en x de la particula 2.
//@param: y1: Posicion en y de la particula 2.
double Particle::distancia(double x1, double y1, double x2, double y2){
    double distancia = 0.0;
    double deltaX = x1-x2;
    double deltaY = y1-y2;
    distancia = sqrt(deltaX*deltaX+deltaY*deltaY);
    return distancia;
}

//Metodo para calcular las fuerzas que siente una particula debido a otra.
void Particle::fuerzaParticula(Particle &p1, Particle &p2){
    //Calculamos la distancia entre ambas particulas
    double dist = distancia(p1.x, p1.y, p2.x, p2.y);
    //Verificacion de la condicion de colision:  dist < |p1.r + p2.r|
    double verificacion = p1.r + p2.r - dist;
    //Calculamos las fuerzas si se cumple la condicion de verificacion
    if(verificacion > 0.0){
        //Calculamos la fuerza normal que sienten las particulas al chocar
        // k = 100 N/m^3
        double fuerzaNormal = k*pow(verificacion,3);

        //Calculamos la fuerza en x, y que siente la particula 1 debido a la particula 2.
        p1.Fx -= fuerzaNormal*(p2.x - p1.x)/dist;
        p1.Fy -= fuerzaNormal*(p2.y - p1.y)/dist;

        //Calculamos la aceleracion resultante por la fuerza (2da ley de Newton).
        p1.ax += p1.Fx/p1.m;
        p1.ay += p1.Fy/p1.m;

        //Calculamos la fuerza en x, y que siente la particula 2 debido a la particula 1.
        //Es opuesta a la calculada previamente por accion reaccion (3ra ley de Newton).
        p2.Fx += fuerzaNormal*(p2.x - p1.x)/dist;
        p2.Fy += fuerzaNormal*(p2.y - p1.y)/dist;

        //Calculamos la aceleracion resultante por la fuerza (2da ley de Newton).
        p2.ax += p2.Fx/p2.m;
        p2.ay += p2.Fy/p2.m;

        //Calculamos la energia potencial realizando la integral de la fuerza.
        E_v =  k * pow(verificacion, 4)/4;
    }
}

//Metodo que hace que todas las fuerzas, aceleraciones y la energia potencial se vuelvan 0. Es decir, "reinicia" estos valores.
 void Particle::fuerza0(){
    Fx = 0.0;
    Fy = 0.0;

    ax = 0.0;
    ay = 0.0;

    E_v = 0.0;
}

//Metodo para mover la particula utilizando el algoritmo de Verlet. Se evoluciona el sistema usando un tiempo y un deltaTiempo determinados para evolucionar el sistema adecuadamente.
//@param deltaTiempo: evolucion del sistema en un intervalo de tiempo
//@param iteracion: Numero de la iteracion en la cual se esta
void Particle::moverParticula(double deltaTiempo, int iteracion){
    //Si estamos en la iteracion 0, la particula no se mueve.
    if(iteracion == 0) return;

    //Evolucion de la posicion de la particula usando el metodo de Verlet.
    x += vx*deltaTiempo + ax*deltaTiempo*deltaTiempo/2;
    y += vy*deltaTiempo + ay*deltaTiempo*deltaTiempo/2;

    //Evolucion de la velocidad de la particula usando el metodo de Verlet.
    vx += ax*deltaTiempo;
    vy += ay*deltaTiempo;

    //Calculamos la velocidad^2 para calcular posteriormente, la energia cinetica E_k
    v = vx*vx+vy*vy;
    E_k = m*v/2;

    //Calculamos el momento actual de la particula en x, y
    px=m*vx;
    py=m*vy;
    
    //Escribimos en el archivo los valores actuales de las variables que caracterizan a la particula.
    archivo << x << ',' << y << ',' << vx << ',' << vy << ',' << sqrt(v) << ',' << ax << ',' << ay << ',' 
    << px << ',' << py << ',' << Fx << ',' << Fy << ',' << E_k << ',' << E_v << ',' << m << ',' << r << endl;
    //Despues de mover la particula, es necesario que las fuerzas, aceleraciones y la energia potencial se vuelvan 0.
    //Esto, pues deben ser recalculadas cada vez que la particula se mueva con el fin de evolucionar el sistema fisico adecuadamente.
    fuerza0();
}


//Cerrar el archivo en que escribe la informacion
void Particle::cerrarArchivo(){
    archivo.close();
}

//Destructor de la clase
Particle::~Particle(){

}

//Conclusion ¿el momento se crea? 