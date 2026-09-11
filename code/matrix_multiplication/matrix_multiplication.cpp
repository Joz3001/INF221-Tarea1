#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <filesystem>
#include <cmath>
#include <windows.h> // para la memoria
#include <psapi.h>

using namespace std;
namespace fs = std::filesystem;

void naiveMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n);
void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n);

// funcion simple para sacar la memoria usada en Windows
long long getMem() {
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    return (long long)info.WorkingSetSize;
}

// lee el txt y arma la matriz
bool cargarMatriz(const string& ruta, vector<vector<int>>& matriz, int& n) {
    ifstream in(ruta);
    if (!in) return false;
    
    vector<int> temp;
    int num;
    while (in >> num) temp.push_back(num);
    in.close();

    n = sqrt(temp.size());
    matriz.assign(n, vector<int>(n, 0));
    
    size_t idx = 0; // Cambiado a size_t para evitar el warning de compilacion
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (idx < temp.size()) matriz[i][j] = temp[idx++];
        }
    }
    return true;
}

int main() {
    string in_dir = "data/matrix_input/";
    string out_csv = "data/measurements/resultados.csv";
    string out_dir = "data/matrix_output/";

    // crear carpetas si no existen
    if (!fs::exists("data/measurements")) fs::create_directory("data/measurements");
    if (!fs::exists(out_dir)) fs::create_directory(out_dir);
    ofstream csv(out_csv);
    if (!csv) {
        cout << "Error con " << out_csv << endl;
        return 1;
    }

    csv << "Archivo,Tamanio,Naive_ms,Strassen_ms,Memoria_KB\n";
    cout << "Iniciando procesamiento de matrices por lotes..." << endl;

    for (const auto& entry : fs::directory_iterator(in_dir)) {
        string path1 = entry.path().string();
        string fname1 = entry.path().filename().string();
        
        if (entry.is_regular_file() && fname1.find("_1.txt") != string::npos) {
            
            // buscar la pareja _2.txt
            string fname2 = fname1;
            fname2.replace(fname2.find("_1.txt"), 6, "_2.txt");
            string path2 = in_dir + fname2;

            int n1, n2;
            vector<vector<int>> A, B;
            
            if (!cargarMatriz(path1, A, n1) || !cargarMatriz(path2, B, n2)) continue;

            int n = n1;
            vector<vector<int>> C_naive(n, vector<int>(n, 0));
            vector<vector<int>> C_strassen(n, vector<int>(n, 0));

            string base = fname1.substr(0, fname1.find("_1.txt"));
            long long mem_antes = getMem();

            // medir naive
            auto t1 = chrono::high_resolution_clock::now();
            naiveMatrixMultiplication(A, B, C_naive, n);
            auto t2 = chrono::high_resolution_clock::now();
            double t_naive = chrono::duration<double, milli>(t2 - t1).count();

            // medir strassen
            t1 = chrono::high_resolution_clock::now();
            strassen(A, B, C_strassen, n);
            t2 = chrono::high_resolution_clock::now();
            double t_strassen = chrono::duration<double, milli>(t2 - t1).count();

            long long mem_despues = getMem();
            long long mem_usada = (mem_despues - mem_antes) / 1024; // Pasar a KB

            csv << base << "," << n << "," << t_naive << "," << t_strassen << "," << mem_usada << "\n";

            // guardar la matriz multiplicada en el output exigido
            ofstream out_txt(out_dir + base + "_out.txt");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    out_txt << C_naive[i][j];
                    if (j < n - 1) out_txt << " ";
                }
                out_txt << "\n";
            }
            out_txt.close();

            cout << base << " listo | Memoria: " << mem_usada << " KB\n";
        }
    }

    csv.close();
    cout << "\nTermino el procesamiento de matrices. Archivos generados en data/measurements/resultados.csv y en data/matrix_output\n";
    return 0;
}