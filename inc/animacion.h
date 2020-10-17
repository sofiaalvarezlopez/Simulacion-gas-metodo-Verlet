#include <iostream>
using namespace std;
void StartAnim(){

  cout<<"unset key"<<endl;
  cout<<"set xrange [-50:50]"<<endl;
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