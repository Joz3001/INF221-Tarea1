import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs('../data/plots', exist_ok=True)

df = pd.read_csv("../data/measurements/resultados.csv") # se cambio el a.txt
promedios = df.groupby('Tamanio').mean(numeric_only=True)

plt.figure(figsize=(10, 6))
plt.plot(promedios.index, promedios['Naive_ms'], marker='o', label='Fuerza Bruta (Naive)')
plt.plot(promedios.index, promedios['Strassen_ms'], marker='s', label='Strassen')

plt.title('Rendimiento: Multiplicación de Matrices')
plt.xlabel('Dimensión de la Matriz (N x N)')
plt.ylabel('Tiempo de Ejecución (ms)')
plt.legend()
plt.grid(True)

plt.savefig('../data/plots/matrices_tiempo.png')
print("¡Gráfico de matrices listo en data/plots/!") 