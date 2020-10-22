#!/bin/bash
echo Escriba el numero de la opcion que desea correr [e.g. 1]
echo 1. make
echo 2. make clean
echo 3. Correr la simulacion de C++ con gnuplot
echo 4. Correr el script de python de conservacion de momento y energia.
echo 5. Correr el script de python para ver la velocidad cuadratrica media.

read line; 
    if [ "$line" -eq 1 ]; 
        then make;
    elif [ "$line" -eq 2 ]; 
        then make clean;
    elif [ "$line" -eq 3 ]; 
        then echo Escriba el numero de particulas 
             read particulas
             echo Escriba el tiempo que desea correr la simulacion
             read tiempo
             ./Simulacion "$particulas" "$tiempo" | gnuplot
    elif [ "$line"  -eq 4 ]; 
        then python3 ./src/punto1d.py
    elif [ "$line" -eq 5 ];
        then python3 ./src/punto2g.py
    else 
        echo Opcion no disponible;
    fi

