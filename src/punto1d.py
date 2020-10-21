import os
import pandas as pd
import  matplotlib
import matplotlib.pyplot as plt
import numpy as np
matplotlib.use('TkAgg')

data_path = './data/'
data_directories = [dir for dir in os.listdir(data_path)]
data_directories.remove('.DS_Store')
print('Las carpetas con archivos de simulaciones que hay en el sistema son: ')
for i in range(len(data_directories)):
    print(str(i+1) + '). ' + data_directories[i])
chosen_dir = int(input('Escoja el numero de la carpeta que desea usar. E.g.: 1\n')) -1
try:
    selected_path = os.path.join(data_path + data_directories[chosen_dir] + '/')
except:
    print('Directorio no disponible o no existente')
    exit()
archivos_carpeta = [arch for arch in os.listdir(selected_path) if arch.endswith('.dat')]
if(len(archivos_carpeta) != 2):
    print('El analisis debe realizarse para el caso especifico de dos particulas.')
    print('Intente volver a correr el programa para solo dos particulas.')
    exit()
particula1 = pd.read_csv(os.path.join(selected_path + archivos_carpeta[0])) 
particula2 = pd.read_csv(os.path.join(selected_path + archivos_carpeta[1])) 

px_total = particula1['px'] + particula2['px']
py_total = particula1['py'] + particula2['py']

tiempo = np.arange(0,10000*0.0001,0.0001)
plt.figure('Grafica de conservacion de momento en el eje x durante el primer choque', figsize=(7,5))
plt.plot(tiempo, particula1[0:10000]['px'], 'r', label = 'momento Particula1')
plt.plot(tiempo, particula2[0:10000]['px'], 'b', label = 'momento Particula2')
plt.plot(tiempo, px_total[0:10000], 'g', label = 'momento total x')
plt.legend()
plt.xlabel('Tiempo (s)')
plt.ylabel(r'$P_x$')
plt.title('Grafica de conservacion de momento en el eje x durante el primer choque')

plt.figure('Grafica de conservacion de momento en el eje y durante el primer choque', figsize=(7,5))
plt.plot(tiempo, particula1[0:10000]['py'], 'r', label = 'momento Particula1')
plt.plot(tiempo, particula2[0:10000]['py'], 'b', label = 'momento Particula2')
plt.plot(tiempo, py_total[0:10000], 'g', label = 'momento total y')
plt.legend(loc=7, bbox_to_anchor=(0.5, 0., 0.5, 0.5))
plt.xlabel('Tiempo (s)')
plt.ylabel(r'$P_y$')
plt.title('Grafica de conservacion de momento en el eje y durante el primer choque')

energiaPotencialTotal = particula1['Ev'] + particula2['Ev']
energiaCineticaTotal = particula1['Ek'] + particula2['Ek']
energiaTotal = energiaPotencialTotal + energiaCineticaTotal

plt.figure('Grafica de conservacion de energia durante el primer choque', figsize=(7,5))
plt.plot(tiempo, energiaPotencialTotal[0:10000], 'r', label = 'Energia Potencial En El Tiempo')
plt.plot(tiempo, energiaCineticaTotal[0:10000], 'b', label = 'Energia Cinetica En El Tiempo')
plt.plot(tiempo, energiaTotal[0:10000], 'g', label = 'Energia Total')
plt.legend()
plt.xlabel('Tiempo (s)')
plt.ylabel(r'$E$')
plt.title('Grafica de conservacion de energia durante el primer choque')

plt.show()

