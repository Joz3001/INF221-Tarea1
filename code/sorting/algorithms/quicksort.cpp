/*
 * Algoritmo implementado basándose en los conceptos teóricos de:
 * Knuth, D. E. (1998). The art of computer programming, volume 3: sorting and searching.
 */

#include <vector>
#include <algorithm>

using namespace std;

// Quicksort con partición de 3 vias
void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    // Tomamos el pivote del medio
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];

    int i = low;
    int lt = low;
    int gt = high;

    // Partición de 3 vías
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[lt]);
            i++;
            lt++;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }

    // Llamadas recursivas solo a los elementos que son menores y mayores
    quickSort(arr, low, lt - 1);
    quickSort(arr, gt + 1, high);
}