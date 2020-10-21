#include <iostream>
using namespace std;
void StartAnim(){
  //Definiendo los parametros de la simulacion para pasar a gnuplot 
  cout<<"unset key"<<endl;
  //Limites en x
  cout<<"set xrange [-50:50]"<<endl;
  //Limites en y
  cout<<"set yrange [-50:50]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:60]"<<endl;
  cout<<"set isosamples 30"<<endl;

}

void StartCuadro(){
   cout<<"plot 0,0 ";
}

void GetPoint(double x, double y, double r){
	cout<<", "<<x<<"+"<<r<<"*cos(t),"<<y<<"+"<<r<<"*sin(t)";
}

void EndCuadro(){
   cout<<endl;
}