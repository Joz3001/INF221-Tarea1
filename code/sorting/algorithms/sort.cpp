/*
 * Algoritmo implementado basándose en los conceptos teóricos de:
 * Knuth, D. E. (1998). The art of computer programming, volume 3: sorting and searching.
 */

#include <algorithm>
#include <vector>

using namespace std; 

vector<int> sortArray(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    return arr;
}
