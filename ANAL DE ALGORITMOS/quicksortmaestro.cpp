#include <iostream>
#include <vector>

using namespace std;

// Función para imprimir vectores
void imprimirVectores(const vector<int>& Maestro, const vector<int>& Esclavo) {
    cout << "Maestro:\tEsclavo:" << endl;
    for (size_t i = 0; i < Maestro.size(); ++i) {
        cout << Maestro[i] << "\t\t" << Esclavo[i] << endl;
    }
}

// Función para intercambiar elementos de dos vectores
void intercambiarElementos(vector<int>& vec1, vector<int>& vec2, int i, int j) {
    int temp = vec1[i];
    vec1[i] = vec1[j];
    vec1[j] = temp;

    temp = vec2[i];
    vec2[i] = vec2[j];
    vec2[j] = temp;
}

// Implementación del algoritmo Quicksort
void quicksort(vector<int>& Maestro, vector<int>& Esclavo, int inicio, int fin) {
    if (inicio < fin) {
        int pivote = Maestro[(inicio + fin) / 2];
        int i = inicio;
        int j = fin;

        while (i <= j) {
            while (Maestro[i] < pivote) {
                i++;
            }
            while (Maestro[j] > pivote) {
                j--;
            }
            if (i <= j) {
                intercambiarElementos(Maestro, Esclavo, i, j);
                i++;
                j--;
            }
        }

        quicksort(Maestro, Esclavo, inicio, j);
        quicksort(Maestro, Esclavo, i, fin);
    }
}

// Implementación del algoritmo MergeSort
void merge(vector<int>& Maestro, vector<int>& Esclavo, int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    vector<int> L1(n1), L2(n2);
    vector<int> R1(n1), R2(n2);

    for (int i = 0; i < n1; i++) {
        L1[i] = Maestro[inicio + i];
        R1[i] = Esclavo[inicio + i];
    }

    for (int j = 0; j < n2; j++) {
        L2[j] = Maestro[medio + 1 + j];
        R2[j] = Esclavo[medio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L1[i] <= L2[j]) {
            Maestro[k] = L1[i];
            Esclavo[k] = R1[i];
            i++;
        } else {
            Maestro[k] = L2[j];
            Esclavo[k] = R2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        Maestro[k] = L1[i];
        Esclavo[k] = R1[i];
        i++;
        k++;
    }

    while (j < n2) {
        Maestro[k] = L2[j];
        Esclavo[k] = R2[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& Maestro, vector<int>& Esclavo, int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;
        mergeSort(Maestro, Esclavo, inicio, medio);
        mergeSort(Maestro, Esclavo, medio + 1, fin);
        merge(Maestro, Esclavo, inicio, medio, fin);
    }
}

int main() {
    vector<int> Maestro = {4, 2, 5, 1, 3};
    vector<int> Esclavo = {40, 20, 50, 10, 30};

    // Imprimir vectores originales
    cout << "Vectores originales:" << endl;
    imprimirVectores(Maestro, Esclavo);
    cout << endl;

    // Ordenar utilizando Quicksort
    quicksort(Maestro, Esclavo, 0, Maestro.size() - 1);
    cout << "Vectores ordenados con Quicksort:" << endl;
    imprimirVectores(Maestro, Esclavo);
    cout << endl;

    // Restaurar vectores originales
    Maestro = {4, 2, 5, 1, 3};
    Esclavo = {40, 20, 50, 10, 30};

    // Ordenar utilizando MergeSort
    mergeSort(Maestro, Esclavo, 0, Maestro.size() - 1);
    cout << "Vectores ordenados con MergeSort:" << endl;
    imprimirVectores(Maestro, Esclavo);

    return 0;
}
