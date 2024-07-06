#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>

using namespace std;

struct Ciudadano {
    string dni;
    string nombresApellidos;
    string nacionalidad;
    string lugarNacimiento;
    string direccion;
    string telefonoReferencia;
    string correoElectronico;
    string estadoCivil;
};

const int MAX_REHASH = 100;

class CuckooHash {
private:

    struct Bucket {
        string key;
        Ciudadano value;
        bool occupied;

        Bucket() : occupied(false) {}
    };

    vector<Bucket> table1, table2;
    int size;

    int hash1(const string& key);
    int hash2(const string& key);

public:
    CuckooHash(int size);
    bool insert(const string& key, const Ciudadano& value);
    bool search(const string& key, Ciudadano& value);
    bool remove(const string& key);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};

CuckooHash::CuckooHash(int size) : size(size) {
    table1.resize(size);
    table2.resize(size);
}

int CuckooHash::hash1(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % size;
    }
    return hash;
}

int CuckooHash::hash2(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 37 + c) % size;
    }
    return hash;
}

bool CuckooHash::insert(const string& key, const Ciudadano& value) {
    int h1 = hash1(key);
    int h2 = hash2(key);
    for (int i = 0; i < MAX_REHASH; ++i) {
        if (!table1[h1].occupied) {
            table1[h1].key = key;
            table1[h1].value = value;
            table1[h1].occupied = true;
            return true;
        } else if (!table2[h2].occupied) {
            table2[h2].key = key;
            table2[h2].value = value;
            table2[h2].occupied = true;
            return true;
        } else {
            swap(table1[h1], table2[h2]);
            h1 = hash1(table1[h1].key);
            h2 = hash2(table2[h2].key);
        }
    }
    return false;
}

bool CuckooHash::search(const string& key, Ciudadano& value) {
    int h1 = hash1(key);
    if (table1[h1].occupied && table1[h1].key == key) {
        value = table1[h1].value;
        return true;
    }
    int h2 = hash2(key);
    if (table2[h2].occupied && table2[h2].key == key) {
        value = table2[h2].value;
        return true;
    }
    return false;
}

bool CuckooHash::remove(const string& key) {
    int h1 = hash1(key);
    if (table1[h1].occupied && table1[h1].key == key) {
        table1[h1].occupied = false;
        return true;
    }
    int h2 = hash2(key);
    if (table2[h2].occupied && table2[h2].key == key) {
        table2[h2].occupied = false;
        return true;
    }
    return false;
}

void CuckooHash::saveToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }
    for (const auto& bucket : table1) {
        if (bucket.occupied) {
            file.write(reinterpret_cast<const char*>(&bucket.value), sizeof(Ciudadano));
        }
    }
    for (const auto& bucket : table2) {
        if (bucket.occupied) {
            file.write(reinterpret_cast<const char*>(&bucket.value), sizeof(Ciudadano));
        }
    }
    file.close();
}

void CuckooHash::loadFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "No se pudo abrir el archivo para leer." << endl;
        return;
    }
    Ciudadano ciudadano;
    while (file.read(reinterpret_cast<char*>(&ciudadano), sizeof(Ciudadano))) {
        insert(ciudadano.dni, ciudadano);
    }
    file.close();
}

// Datos para generar ciudadanos aleatorios
vector<string> nom = {"Juan", "Gabriel", "Angie", "Pepe", "Francisco", "Miguel", "Flor", "Alexandra", "Edwin", "Gustavo", "Daniel", "Fabricio", "Ana", "Lucia", "Leonardo", "Maria",
                      "Angie", "Guissel", "Andrea", "Ariana", "Natalia", "Brenda", "Walter", "Melissa", "Hugo", "Claudia", "Claudio", "Diego", "Roberto"};

vector<string> ape = {"Alvarez", "Cruz", "Montoya", "Quispe", "Sanchez", "Acuña", "Rodriguez", "Nuñez", "Romero", "Lopez", "Gonzalez", "Martinez", "Acosta", "Rojas", "Ortis",
                      "Torres", "Cardozo", "Ramirez", "Gomez"};

vector<string> estCivi = {"Soltero", "Casado", "Viudo", "Divorciado"};

vector<string> tipoDirec = {"Av.", "Jr.", "Calle"};

vector<string> Av = {"Javier Prado", "Arequipa", "28 de Julio", "Abancay", "Arenales", "Aviacion", "Argentina", "Angamos", "Brasil", "Canada", "La Molina", "Universitaria",
                      "Nicolas Ayllon", "Mexico", "Metropolitana", "Naranjal", "Nicolas Arriola", "Petit Thouars", "Primavera"};

vector<string> Jr = {"Los Pinos", "Los Robles", "Los Alamos", "Las Flores", "Las Rosas"};

vector<string> calle = {"San Martin", "Lima", "Bolivar", "Sucre", "Pizarro"};

vector<string> hosp = {"Rebagliati", "Almenara", "Loayza", "Sergio Bernales", "Dos de Mayo"};

string generarDNI() {
    string dni;
    for (int i = 0; i < 8; ++i) {
        dni += '0' + rand() % 10;
    }
    return dni;
}

string generarTelefono() {
    string telefono = "9";
    for (int i = 0; i < 8; ++i) {
        telefono += '0' + rand() % 10;
    }
    return telefono;
}

string generarDireccion(){
    int ale = rand() % 3;
    string direccion;
    if(ale == 0) {
        direccion = "Jr. " + Jr[rand() % Jr.size()];
    } else if(ale == 1) {
        direccion = "Av. " + Av[rand() % Av.size()];
    } else {
        direccion = "Calle " + calle[rand() % calle.size()];
    }
    return direccion;
}

Ciudadano generarCiudadano() {
    Ciudadano ciudadano;
    ciudadano.dni = generarDNI();
    ciudadano.nombresApellidos = nom[rand() % nom.size()] + " " + ape[rand() % ape.size()];
    ciudadano.nacionalidad = "Peruano/a";
    ciudadano.lugarNacimiento = "Hospital " + hosp[rand() % hosp.size()];
    ciudadano.direccion = generarDireccion();
    ciudadano.telefonoReferencia = generarTelefono();
    ciudadano.correoElectronico = ciudadano.nombresApellidos + to_string(rand() % 100) + "@gmail.com";
    ciudadano.estadoCivil = estCivi[rand() % estCivi.size()];
    return ciudadano;
}

void crearDatosIniciales(CuckooHash &cuckooHash) {
    for (int i = 0; i < 33000000; ++i) {
        Ciudadano ciudadano = generarCiudadano();
        cuckooHash.insert(ciudadano.dni, ciudadano);
        if ((i + 1) % 1000000 == 0) {
            cout << i + 1 << " ciudadanos insertados." << endl;
        }
    }
    cuckooHash.saveToFile("datos");
}

int main() {
    srand(time(0)); // Inicializar generador de números aleatorios

    CuckooHash cuckooHash(10000000); // Tamaño de la tabla de hash

    // Verificar si existe el archivo "datos"
    ifstream file("datos", ios::binary);
    if (!file) {
        cout << "Archivo 'datos' no encontrado. Creando archivo con 33 millones de registros..." << endl;
        crearDatosIniciales(cuckooHash);
    } else {
        cout << "Archivo 'datos' encontrado. Cargando datos..." << endl;
        cuckooHash.loadFromFile("datos");
    }
    file.close();

    int opcion;
    do {
        cout << "\nMenu:\n";
        cout << "1. Buscar datos por DNI\n";
        cout << "2. Insertar nuevos datos\n";
        cout << "3. Remover datos\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string dni;
            cout << "Ingrese el DNI a buscar: ";
            cin >> dni;
            Ciudadano value;
            if (cuckooHash.search(dni, value)) {
                cout << "DNI: " << value.dni << endl;
                cout << "Nombre: " << value.nombresApellidos << endl;
                cout << "Nacionalidad: " << value.nacionalidad << endl;
                cout << "Lugar de Nacimiento: " << value.lugarNacimiento << endl;
                cout << "Direccion: " << value.direccion << endl;
                cout << "Telefono: " << value.telefonoReferencia << endl;
                cout << "Correo: " << value.correoElectronico << endl;
                cout << "Estado Civil: " << value.estadoCivil << endl;
            } else {
                cout << "No se encontro un ciudadano con ese DNI." << endl;
            }
        } else if (opcion == 2) {
            Ciudadano nuevoCiudadano = generarCiudadano();
            cuckooHash.insert(nuevoCiudadano.dni, nuevoCiudadano);
            cuckooHash.saveToFile("datos");
            cout << "Nuevo ciudadano insertado y guardado en archivo." << endl;
        } else if (opcion == 3) {
            string dni;
            cout << "Ingrese el DNI a remover: ";
            cin >> dni;
            if (cuckooHash.remove(dni)) {
                cuckooHash.saveToFile("datos");
                cout << "Ciudadano removido y cambios guardados en archivo." << endl;
            } else {
                cout << "No se encontro un ciudadano con ese DNI." << endl;
            }
        }
    } while (opcion != 4);

    return 0;
}