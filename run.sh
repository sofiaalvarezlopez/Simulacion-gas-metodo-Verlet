#!/bin/bash
echo Escriba el numero de particulas
read particulas
echo Escriba el tiempo que desea correr la simulacion
read tiempo
make
./Simulacion $particulas $tiempo | gnuplot