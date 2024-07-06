#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int tamano_maximo = 100000;

int main() {
    int n;
    int array[tamano_maximo];

    unsigned seed = static_cast<unsigned>(time(0));
    srand(seed);

    cout << "Ingrese la cantidad de valores a ingresar en el arreglo" << endl;
    cin >> n;

    if (n <= 0 || n > tamano_maximo) {
        cout << "La cantidad ingresada no es valida" << endl;
        return 1;
    }

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1001;
    }

    cout << "Valores Generados: ";
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "El tiempo de ejecucion es: " << duration.count() << " microsegundos" << endl;

    return 0;
}