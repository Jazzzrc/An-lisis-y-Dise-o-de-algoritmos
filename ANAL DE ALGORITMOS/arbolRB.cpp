#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Nodo {
    int valor;
    vector<Nodo*> hijos;
};

void InsertarRecursivo(Nodo* nodo, vector<int>& valores) {
    if (valores.empty()) return;

    nodo->valor = valores[0];
    valores.erase(valores.begin());

    while (!valores.empty()) {
        Nodo* nuevoHijo = new Nodo();
        InsertarRecursivo(nuevoHijo, valores);
        nodo->hijos.push_back(nuevoHijo);
    }
}

Nodo* Insertar(vector<int> valores) {
    Nodo* raiz = new Nodo();
    InsertarRecursivo(raiz, valores);
    return raiz;
}

void EliminarRecursivo(Nodo* nodo, int valor) {
    vector<Nodo*>::iterator it = find_if(nodo->hijos.begin(), nodo->hijos.end(), [valor](Nodo* n) { return n->valor == valor; });
    if (it != nodo->hijos.end()) {
        Nodo* nodoEliminar = *it;
        nodo->hijos.erase(it);
        for (Nodo* hijo : nodoEliminar->hijos) {
            nodo->hijos.push_back(hijo);
        }
        delete nodoEliminar;
    }
}

void Eliminar(Nodo* raiz, int valor) {
    EliminarRecursivo(raiz, valor);
}

void ImprimirRecursivo(Nodo* nodo, int nivel) {
    for (int i = 0; i < nivel; i++) {
        cout << "  ";
    }
    cout << nodo->valor << endl;
    for (Nodo* hijo : nodo->hijos) {
        ImprimirRecursivo(hijo, nivel + 1);
    }
}

void Imprimir(Nodo* raiz) {
    ImprimirRecursivo(raiz, 0);
}

int main() {
    vector<int> valores = {3, 1, 5, 0, 4, 8, 6, 7, 9, 2};
    Nodo* raiz = Insertar(valores);
    Imprimir(raiz);
    cout << "Eliminando el valor 8..." << endl;
    Eliminar(raiz, 8);
    Imprimir(raiz);
    return 0;
}
