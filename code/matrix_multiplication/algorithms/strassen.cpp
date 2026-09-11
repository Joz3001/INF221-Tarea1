/*
 * Algoritmo implementado basándose en:
 * Erickson, J. (2019). Algorithms.
 */

#include <vector>

using namespace std;

// Función auxiliar para sumar matrices
void addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Función auxiliar para restar matrices
void subMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    // Optimizacion
    if (n <= 64) { 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return;
    }

    int mitad = n / 2;
    vector<int> inner(mitad, 0);
    
    // Declaración de las 4 submatrices para A B y C
    vector<vector<int>> A11(mitad, inner), A12(mitad, inner), A21(mitad, inner), A22(mitad, inner);
    vector<vector<int>> B11(mitad, inner), B12(mitad, inner), B21(mitad, inner), B22(mitad, inner);
    vector<vector<int>> C11(mitad, inner), C12(mitad, inner), C21(mitad, inner), C22(mitad, inner);
    
    // Matrices temporales para los 7 productos de Strassen
    vector<vector<int>> P1(mitad, inner), P2(mitad, inner), P3(mitad, inner), P4(mitad, inner);
    vector<vector<int>> P5(mitad, inner), P6(mitad, inner), P7(mitad, inner);
    vector<vector<int>> temp_a(mitad, inner), temp_b(mitad, inner);

    // Dividir A y B en 4 submatrices cada una
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }
    }

    // Calcular
    addMatrix(A11, A22, temp_a, mitad);    // temp_a = A11 + A22
    addMatrix(B11, B22, temp_b, mitad);    // temp_b = B11 + B22
    strassen(temp_a, temp_b, P1, mitad);  // P1 = (A11 + A22) * (B11 + B22)

    addMatrix(A21, A22, temp_a, mitad);
    strassen(temp_a, B11, P2, mitad);      // P2 = (A21 + A22) * B11

    subMatrix(B12, B22, temp_b, mitad);
    strassen(A11, temp_b, P3, mitad);      // P3 = A11 * (B12 - B22)

    subMatrix(B21, B11, temp_b, mitad);
    strassen(A22, temp_b, P4, mitad);      // P4 = A22 * (B21 - B11)

    addMatrix(A11, A12, temp_a, mitad);
    strassen(temp_a, B22, P5, mitad);      // P5 = (A11 + A12) * B22

    subMatrix(A21, A11, temp_a, mitad);
    addMatrix(B11, B12, temp_b, mitad);
    strassen(temp_a, temp_b, P6, mitad);  // P6 = (A21 - A11) * (B11 + B12)

    subMatrix(A12, A22, temp_a, mitad);
    addMatrix(B21, B22, temp_b, mitad);
    strassen(temp_a, temp_b, P7, mitad);  // P7 = (A12 - A22) * (B21 + B22)

    // submatrices de C
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C11[i][j] = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C12[i][j] = P3[i][j] + P5[i][j];
            C21[i][j] = P2[i][j] + P4[i][j];
            C22[i][j] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    }

    // Ensamblar la matriz final C
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }
    }
}