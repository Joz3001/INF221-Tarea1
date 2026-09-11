#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <filesystem> 
#include <algorithm> // para std::sort
#include <windows.h> // para la memoria
#include <psapi.h>

using namespace std;
namespace fs = std::filesystem;

void quickSort(vector<int>& arr, int low, int high);
void mergeSort(vector<int>& arr, int left, int right);
void patienceSort(vector<int>& arr);

// funcion para sacar la memoria usada en windows
long long getMem() {
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    return (long long)info.WorkingSetSize;
}

int main() {
    string in_dir = "data/array_input/";
    string out_csv = "data/measurements/resultados.csv"; 
    string out_dir = "data/array_output/";

    // crear carpetas si no existen
    if (!fs::exists("data/measurements")) fs::create_directory("data/measurements");
    if (!fs::exists(out_dir)) fs::create_directory(out_dir);

    ofstream csv(out_csv);
    if (!csv) {
        cout << "Fallo al crear " << out_csv << endl;
        return 1;
    }

    // header del csv
    csv << "Archivo,Tamanio,MergeSort_ms,QuickSort_ms,PatienceSort_ms,StdSort_ms,Memoria_KB\n";

    for (const auto& entry : fs::directory_iterator(in_dir)) {
        string path = entry.path().string();
        string fname = entry.path().filename().string();
        
        if (entry.is_regular_file() && path.find(".txt") != string::npos) {
            
            ifstream in(path);
            vector<int> data;
            int x;
            while (in >> x) data.push_back(x);
            in.close();

            vector<int> v_merge = data;
            vector<int> v_quick = data;
            vector<int> v_pat = data;
            vector<int> v_std = data;

            long long mem_antes = getMem();

            // medimos merge
            auto t1 = chrono::high_resolution_clock::now();
            mergeSort(v_merge, 0, v_merge.size() - 1);
            auto t2 = chrono::high_resolution_clock::now();
            double t_merge = chrono::duration<double, milli>(t2 - t1).count();

            // medimos quick
            t1 = chrono::high_resolution_clock::now();
            quickSort(v_quick, 0, v_quick.size() - 1);
            t2 = chrono::high_resolution_clock::now();
            double t_quick = chrono::duration<double, milli>(t2 - t1).count();

            // medimos patience
            t1 = chrono::high_resolution_clock::now();
            patienceSort(v_pat);
            t2 = chrono::high_resolution_clock::now();
            double t_pat = chrono::duration<double, milli>(t2 - t1).count();

            // medimos std::sort
            t1 = chrono::high_resolution_clock::now();
            sort(v_std.begin(), v_std.end());
            t2 = chrono::high_resolution_clock::now();
            double t_std = chrono::duration<double, milli>(t2 - t1).count();

            long long mem_despues = getMem();
            long long mem_usada = (mem_despues - mem_antes) / 1024; // pasar a KB

            csv << fname << "," << data.size() << "," 
                << t_merge << "," << t_quick << "," << t_pat << "," << t_std << "," << mem_usada << "\n";

            // guardar el txt ordenado final
            string base = fname.substr(0, fname.find(".txt"));
            ofstream out_txt(out_dir + base + "_out.txt");
            for (size_t i = 0; i < v_std.size(); i++) {
                out_txt << v_std[i];
                if (i != v_std.size() - 1) out_txt << " ";
            }
            out_txt.close();

            cout << fname << " listo | Mem: " << mem_usada << " KB\n";
        }
    }

    csv.close();
    cout << "\nTermino el sorting, archivos generados en data/measurements/resultados.csv y en data/array_output.\n";
    return 0;
}