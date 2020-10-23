# Programa de simulacion de gas haciendo uso del metodo de verlet
## Juan Daniel Castrellon(201729285) - Maria Sofia Alvarez(201729031)

Para correr el programa, correr en consola el comando ./run.sh, donde se mostraran las opciones
disponibles. Estas son:
1. La opción 1 corre el comando make.
2. La opción 2 corre el comando make clean. Este le pregunta al usuario si desea, también, eliminar los datos de simulación que hay en la carpeta ./data
3. La opción 3 corre la simulación realizada en C++. Aquí, se le pide al usuario el número de partículas que desea simular y el tiempo durante el cual desea correr la simulación. Con la opción 3, se corre el comando ./Simulacion num_particulas tiempo | gnuplot, con el fin de graficar la información recolectada. **Nota:** Antes de correr la simulación, es necesario correr el comando make.
4. La opción 4 corre el script de python para mostrar las gráficas de conservación de momento y energía en el caso de dos partículas (python src/punto1d.py). **Nota:** La simulación debe correrse, por lo menos, por un segundo. La gráfica muestra únicamente el primer choque.
5. La opción 5 corre el script de python para mostrar la gráfica de distribución de velocidades cuadráticas para 50 partículas (python src/punto2g.py). **Nota:** Es necesario correr la simulación con exactamente 50 partículas para ver el funcionamiento de la gráfica y por un tiempo de, por lo menos, 1 segundo.

* Los archivos *.dat seran almacenados en la carpeta ./data/<num_particulas>Particulas/<fecha en que se corrio el ejecutable>
* Las imagenes seran almacenadas en la carpeta ./images/<num_particulas>Particulas/<fecha en que se corrio el ejecutable>
* En la carpeta images se encuentran las gráficas para algunos ejemplos de la simulación corriendo:
a) Para dos partículas, con 50 segundos.
b) Para 50 partículas, con 30 segundos. 
