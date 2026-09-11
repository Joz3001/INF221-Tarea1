/*
 * Algoritmo implementado basándose en los conceptos teóricos de:
 * Knuth, D. E. (1998). The art of computer programming, volume 3: sorting and searching.
 */

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void patienceSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Pilas para el sort
    vector<vector<int>> piles;

    for (int x : arr) {
        // Encontrar la primera pila cuyo último elemento sea mayor o igual a x
        auto it = lower_bound(piles.begin(), piles.end(), x, 
            [](const vector<int>& pile, int val) {
                return pile.back() < val;
            });
        
        if (it == piles.end()) {
            // Si no hay ninguna pila, creamos una nueva
            piles.push_back({x});
        } else {
            // Si encontramos una pila, agregamos x a esa pila
            it->push_back(x);
        }
    }

    // merrge las pilas en un solo arreglo ordenado usando una cola de prioridad
    typedef pair<int, pair<int, int>> Node;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    for (size_t i = 0; i < piles.size(); i++) {
        pq.push({piles[i].back(), {i, piles[i].size() - 1}});
    }

    int idx = 0;
    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        
        arr[idx++] = curr.first;
        
        int pile_idx = curr.second.first;
        int elem_idx = curr.second.second;
        
        // si quedan, agregamos el siguiente elemento de la pila a la cola de prioridad
        if (elem_idx > 0) {
            pq.push({piles[pile_idx][elem_idx - 1], {pile_idx, elem_idx - 1}});
        }
    }
}