import os
import pandas as pd
import  matplotlib
import matplotlib.pyplot as plt
import numpy as np
#matplotlib.use('TkAgg')

#Directorio donde guardamos los datos capturados
data_path = './data/50Particulas/'
#Listamos todos los directorios que hay en la carpeta data_path
try:
    data_directories = os.listdir(data_path)
except:
    print("No ha generado datos con 50 moleculas")
    exit()

try:
    data_directories.remove('.DS_Store')
except:
    pass
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

num_particulas = len(archivos_carpeta)
dataParticles = []
for i in range(num_particulas):
    df = pd.read_csv(selected_path + archivos_carpeta[i])
    dataParticles.append(df)

velocidades = pd.DataFrame({'v': dataParticles[0]['v']**2})
for i in range(1, num_particulas):
    velocidades['v'+str(i+1)] = dataParticles[i]['v']**2

v2 = velocidades.loc[len(velocidades)-10000:]
media_velocidades = v2.mean()
try:
    os.mkdir('./images/')
except:
    pass

try:
    os.mkdir('./images/50Particulas/')
except:
    pass

try:
    os.mkdir('./images/50Particulas' + selected_path[19:-1])
except:
    pass

plt.figure('Distribucion Velocidades Cuadraticas con v^2', figsize=(7,5))
plt.hist(media_velocidades, edgecolor='black', bins =15)
plt.savefig('./images/50Particulas/' + selected_path[19:-1] + '/Dist_V2.png')

cinetica = pd.DataFrame({'Ek': dataParticles[0]['Ek']})
for i in range(1, num_particulas):
    cinetica['Ek'+str(i+1)] = dataParticles[i]['Ek']

cin = cinetica.loc[len(cinetica)-10000:]
media_cinetica = cin.mean()

plt.figure('Distribucion Velocidades Cuadraticas usando la energia cinetica E_k', figsize=(7,5))
plt.hist(media_cinetica, edgecolor='black', bins =15)
plt.savefig('./images/50Particulas/' + selected_path[19:-1] + '/Dist_V2_Con_Ek.png')
plt.show()

