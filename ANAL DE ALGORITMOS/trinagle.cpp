#include <iostream>
#include <iomanip>

using namespace std;

int fib(int n) {
    return n < 2 ? n : fib(n - 1) + fib(n - 2);
}

void printTriangle(int n) {
    int maxWidth = to_string(fib(n)).length();
    for (int i = 0; i <= n; i++) {
        int spaces = maxWidth * (n - i);
        cout << setw(spaces) << "";
        for (int j = 0; j <= i; j++) {
        cout << setw(maxWidth) << fib(j) << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;
    printTriangle(n);
    return 0;
}
