/*
 * Algoritmo implementado basándose en:
 * Erickson, J. (2019). Algorithms.
 */

#include <vector>

using namespace std;

// Multiplicación
void naiveMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}