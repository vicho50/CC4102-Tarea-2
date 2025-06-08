import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('resultados.csv')
for dens in df['m']/df['n'].unique():
    sub = df[df['m']/df['n'] == dens]
    for alg in ['arreglo', 'heap']:
        datos = sub[sub['algoritmo'] == alg].groupby('n')['tiempo_ms'].mean()
        plt.plot(datos.index, datos.values, label=f'{alg} dens={dens:.1f}')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.legend()
plt.show()