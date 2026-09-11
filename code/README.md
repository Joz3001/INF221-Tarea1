# Documentación

## Entrega
La entrega se realiza vía **aula.usm.cl** en formato `.zip`. Este directorio contiene todo el código fuente en C++ y los scripts en Python utilizados para la experimentación.

---

## Multiplicación de matrices
Algoritmos implementados: Fuerza Bruta (Naive) y Strassen.

### Programa principal
El archivo `matrix_multiplication.cpp` es el orquestador de los experimentos de matrices. 
- **Funcionalidad:** Lee los pares de matrices desde la carpeta de inputs, ejecuta ambos algoritmos (Naive y Strassen) y mide tanto el tiempo de ejecución (usando `std::chrono`) como el consumo de memoria en Windows (mediante `psapi.h`).
- **Salida:** Genera un archivo `.csv` en la carpeta `measurements` con los tiempos y la memoria utilizada. Además, guarda las matrices resultantes en la carpeta correspondiente de `output`.

### Scripts
- `matrix_generator.py`: Genera los datasets de prueba (matrices dispersas, diagonales y densas) según los tamaños y dominios especificados en el enunciado.
- `plot_generator.py`: Lee los datos del `.csv` generado por el programa principal y utiliza la librería Matplotlib de Python para generar los gráficos de rendimiento comparativo, los cuales se exportan en formato `.png` a la carpeta `plots`.

---

## Ordenamiento de arreglo unidimensional
Algoritmos implementados: MergeSort, QuickSort (optimizado con partición de 3 vías), PatienceSort y std::sort.

### Programa principal
El archivo `sorting.cpp` se encarga de probar los algoritmos de ordenamiento.
- **Funcionalidad:** Lee los arreglos generados (ascendentes, descendentes y aleatorios), realiza copias de los mismos para asegurar igualdad de condiciones, y mide los tiempos de ejecución y variaciones de RAM (Working Set Size) para cada algoritmo.
- **Salida:** Registra los resultados de métricas en un `.csv` dentro de la carpeta `measurements` y escribe los arreglos ya ordenados en archivos de texto dentro de la carpeta `output`.

### Scripts
- `array_generator.py`: Crea los arreglos unidimensionales de diferentes distribuciones y dominios para estresar los algoritmos, guardándolos en la carpeta de input.
- `plot_generator.py`: Procesa el `.csv` de resultados de ordenamiento y genera gráficos lineales con escala logarítmica para visualizar y comparar el crecimiento de $O(n \log n)$ frente a los peores casos, guardándolos en la carpeta `plots`.