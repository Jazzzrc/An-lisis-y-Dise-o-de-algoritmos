#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstdint>

using namespace std;
using namespace std::chrono;


int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n;
    cout << "Ingrese el valor de n para calcular el termino n-esimo de la serie de Fibonacci: ";
    cin >> n;

    auto start = high_resolution_clock::now();
    int resultado = fibonacci(n);
    auto stop = high_resolution_clock::now();


    auto duration = duration_cast<microseconds>(stop-start);


    cout << "El termino n-esimo de la serie de Fibonacci es: " << resultado << endl;

    cout <<"\nTiempo ejecucion: " << duration.count()<<" microsegundos" <<endl;

    return 0;
}
