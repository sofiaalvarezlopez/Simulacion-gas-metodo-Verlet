import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data_path = './data/'
data_directories = [dir for dir in os.listdir(data_path)]
data_directories.remove('.DS_Store')
print('Las carpetas con archivos de simulaciones que hay en el sistema son: ')
for i in range(len(data_directories)):
    print(str(i+1) + '). ' + data_directories[i])
chosen_dir = int(input('Escoja el numero de la carpeta que desea usar. E.g.: 1\n')) -1

selected_path = os.path.join(data_path + data_directories[chosen_dir] + '/')
archivos_carpeta = [arch for arch in os.listdir(selected_path)]
particulas = [pd.read_csv(os.path.join(selected_path + particula)) for particula in archivos_carpeta]

px_total = particulas[0]['px']
print(px_total)

    #print('Directorio no disponible o no existente')
    #exit()

