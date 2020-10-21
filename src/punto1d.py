import os
import pandas as pd
import  matplotlib
import matplotlib.pyplot as plt
import numpy as np
matplotlib.use('TkAgg')

#Directorio donde guardamos los datos capturados
data_path = './data/'
#Listamos todos los directorios que hay en la carpeta data_path
data_directories = os.listdir(data_path)
data_directories.remove('.DS_Store')
#Listamos las carpetas que contienen los datos de las simulaciones 
print('Las carpetas con archivos de simulaciones que hay en el sistema son: ')
for i in range(len(data_directories)):
    print(str(i+1) + '). ' + data_directories[i])
#Se pide al usuario que escriba el numero de la carpeta con los datos que desea simular
chosen_dir = int(input('Escoja el numero de la carpeta que desea usar. E.g.: 1\n')) -1
selected_path, archivos_carpeta = '', []
try:
    #Intentamos buscar la carpeta elegida y listamos los archivos cuya extension sea .dat
    selected_path = os.path.join(data_path + data_directories[chosen_dir] + '/')
    archivos_carpeta = [arch for arch in os.listdir(selected_path) if arch.endswith('.dat')]
except:
    #Si el directorio no existe, el programa finaliza
    print('Directorio no disponible o no existente')
    exit()
#Si la longitud de los archivos que hay en la carpeta es diferente de dos, el programa finaliza.
#Solo necesitamos calcular el momento en el caso de dos particulas chocando
if(len(archivos_carpeta) != 2):
    print('El analisis debe realizarse para el caso especifico de dos particulas.')
    print('Intente volver a correr el programa para solo dos particulas.')
    exit()
#Leemos los datos para la particula 1 y la particula 2
particula1 = pd.read_csv(os.path.join(selected_path + archivos_carpeta[0])) 
particula2 = pd.read_csv(os.path.join(selected_path + archivos_carpeta[1])) 

#Encontramos el momento total en x,y sumando sus correspondientes componentes. 
px_total = particula1['px'] + particula2['px']
py_total = particula1['py'] + particula2['py']

#El tiempo que tarda la simulacion en completarse es de 1 segundo
tiempo = np.arange(0,10000*0.0001,0.0001)

#Grafica del momento en el eje x. Tomamos hasta 10000 para que sea consistente con el tiempo y corresponda unicamente al primer choque
plt.figure('Grafica de conservacion de momento en el eje x durante el primer choque', figsize=(7,5))
plt.plot(tiempo, particula1[0:10000]['px'], 'r', label = 'momento Particula1')
plt.plot(tiempo, particula2[0:10000]['px'], 'b', label = 'momento Particula2')
plt.plot(tiempo, px_total[0:10000], 'g', label = 'momento total x')
plt.legend()
plt.xlabel('Tiempo (s)')
plt.ylabel(r'$P_x$')
plt.title('Grafica de conservacion de momento en el eje x durante el primer choque')

#Grafica del momento en el eje y. Tomamos hasta 10000 para que sea consistente con el tiempo y corresponda unicamente al primer choque
plt.figure('Grafica de conservacion de momento en el eje y durante el primer choque', figsize=(7,5))
plt.plot(tiempo, particula1[0:10000]['py'], 'r', label = 'momento Particula1')
plt.plot(tiempo, particula2[0:10000]['py'], 'b', label = 'momento Particula2')
plt.plot(tiempo, py_total[0:10000], 'g', label = 'momento total y')
plt.legend(loc=7, bbox_to_anchor=(0.5, 0., 0.5, 0.5))
plt.xlabel('Tiempo (s)')
plt.ylabel(r'$P_y$')
plt.title('Grafica de conservacion de momento en el eje y durante el primer choque')

#Encontramos la energia potencial total
energiaPotencialTotal = particula1['Ev'] + particula2['Ev']
#Encontramos la energia cinetica total
energiaCineticaTotal = particula1['Ek'] + particula2['Ek']
#Encontramos la energia mecanica total
energiaTotal = energiaPotencialTotal + energiaCineticaTotal

#Grafica de la energia. Tomamos hasta 10000 para que sea consistente con el tiempo y corresponda unicamente al primer choque
plt.figure('Grafica de conservacion de energia durante el primer choque', figsize=(7,5))
plt.plot(tiempo, energiaPotencialTotal[0:10000], 'r', label = 'Energia Potencial En El Tiempo')
plt.plot(tiempo, energiaCineticaTotal[0:10000], 'b', label = 'Energia Cinetica En El Tiempo')
plt.plot(tiempo, energiaTotal[0:10000], 'g', label = 'Energia Total')
plt.legend()
plt.xlabel('Tiempo (s)')
plt.ylabel(r'$E$')
plt.title('Grafica de conservacion de energia durante el primer choque')

plt.show()

