import pandas as pd
import matplotlib.pyplot as plt
import os

# Asegurar que la carpeta exista
os.makedirs('../data/plots', exist_ok=True)

# Leer el archivo que creamos en C++
df = pd.read_csv("../data/measurements/resultados.csv") # se cambio el a.txt

# Agrupar los datos por tamaño de arreglo (promedio de las muestras)
promedios = df.groupby('Tamanio').mean(numeric_only=True)

# Crear el gráfico
plt.figure(figsize=(10, 6))
plt.plot(promedios.index, promedios['MergeSort_ms'], marker='o', label='Merge Sort')
plt.plot(promedios.index, promedios['QuickSort_ms'], marker='s', label='Quick Sort')
plt.plot(promedios.index, promedios['PatienceSort_ms'], marker='^', label='Patience Sort')
plt.plot(promedios.index, promedios['StdSort_ms'], marker='x', label='std::sort')

plt.title('Rendimiento de Algoritmos de Ordenamiento')
plt.xlabel('Cantidad de Elementos (n)')
plt.ylabel('Tiempo de Ejecución (ms)')
plt.legend()
plt.grid(True)
plt.xscale('log') # Escala log para que se vea bien la curva
plt.yscale('log')

# Guardar
plt.savefig('../data/plots/ordenamiento_tiempo.png')
print("¡Gráfico de ordenamiento listo en data/plots/!")