#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "Grafo.h"

using namespace std;

// Ciudades disponibles
vector<string> ciudades = {
    "Maracaibo", 
    "Machiques",
    "Villa del Rosario",
    "San Francisco",
    "La Ca#ada"
};

// Función para inicializar el grafo con datos por defecto
void inicializarGrafo(Grafo<string, int>& grafo) {
    // Agregar ciudades
    for (const auto& ciudad : ciudades) {
        grafo.agregarNodo(ciudad);
    }
    
    // Establecer conexiones
    grafo.agregarArista("Maracaibo", "Machiques", 110);
    grafo.agregarArista("Maracaibo", "Villa del Rosario", 65);
    grafo.agregarArista("Villa del Rosario", "Machiques", 45);
    grafo.agregarArista("Maracaibo", "San Francisco", 15);
    grafo.agregarArista("San Francisco", "La Ca#ada", 10);
    grafo.agregarArista("La Ca#ada", "Villa del Rosario", 30);
}

// Función para mostrar el menú principal
void mostrarMenu() {
    cout << "\n=== SISTEMA DE RUTAS DEL ZULIA ===" << endl;
    cout << "1. Mostrar todas las ciudades" << endl;
    cout << "2. Mostrar recorrido BFS (Busqueda en Amplitud) desde una ciudad" << endl;
    cout << "3. Mostrar recorrido DFS (Busqueda en Profundidad) desde una ciudad" << endl;
    cout << "4. Agregar nueva ciudad" << endl;
    cout << "5. Conectar ciudades" << endl;
    cout << "6. Mostrar ruta mas corta entre ciudades" << endl;
    cout << "7. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para mostrar todas las ciudades numeradas
void mostrarTodasCiudades() {
    cout << "\n=== CIUDADES DISPONIBLES ===" << endl;
    for (int i = 0; i < ciudades.size(); ++i) {
        cout << (i + 1) << ". " << ciudades[i] << endl;
    }
    cout << "---------------------------" << endl;
}

// Función para seleccionar ciudad por número
string seleccionarCiudadPorNumero() {
    int seleccion;
    while (true) {
        cout << "Seleccione el numero de la ciudad: ";
        cin >> seleccion;
        limpiarBuffer();
        
        if (seleccion >= 1 && seleccion <= ciudades.size()) {
            return ciudades[seleccion - 1];
        } else {
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    }
}

// Función para mostrar un recorrido
void mostrarRecorrido(const string& titulo, const Lista<string>& recorrido) {
    cout << "\n" << titulo << ":" << endl;
    auto it = recorrido.obtenerIterador();
    while (it.tieneSiguiente()) {
        cout << it.siguiente();
        if (it.tieneSiguiente()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    Grafo<string, int> grafoCiudades;
    
    // Inicializar con datos por defecto
    inicializarGrafo(grafoCiudades);
    
    cout << "====================================" << endl;
    cout << "  SISTEMA DE RUTAS DEL ESTADO ZULIA" << endl;
    cout << "====================================" << endl;
    cout << "Ciudades cargadas por defecto:" << endl;
    mostrarTodasCiudades();
    cout << "====================================" << endl;

    int opcion = 0;
    while (true) {
        mostrarMenu();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: { // Mostrar todas las ciudades
                mostrarTodasCiudades();
                break;
            }
            
            case 2: { // Mostrar BFS
                mostrarTodasCiudades();
                cout << "Seleccione ciudad de inicio:" << endl;
                string inicio = seleccionarCiudadPorNumero();
                
                auto bfs = grafoCiudades.recorridoEnAnchura(inicio);
                if (bfs.obtenerTamano() == 0) {
                    cout << "No hay conexiones desde esta ciudad." << endl;
                } else {
                    mostrarRecorrido("Recorrido en Anchura (BFS)", bfs);
                }
                break;
            }
            
            case 3: { // Mostrar DFS
                mostrarTodasCiudades();
                cout << "Seleccione ciudad de inicio:" << endl;
                string inicio = seleccionarCiudadPorNumero();
                
                auto dfs = grafoCiudades.recorridoEnProfundidad(inicio);
                if (dfs.obtenerTamano() == 0) {
                    cout << "No hay conexiones desde esta ciudad." << endl;
                } else {
                    mostrarRecorrido("Recorrido en Profundidad (DFS)", dfs);
                }
                break;
            }
            
            case 4: { // Agregar ciudad
                string ciudad;
                cout << "Ingrese el nombre de la nueva ciudad: ";
                getline(cin, ciudad);
                
                if (ciudad.empty()) {
                    cout << "Error: El nombre no puede estar vacio." << endl;
                } else {
                    grafoCiudades.agregarNodo(ciudad);
                    ciudades.push_back(ciudad);
                    cout << "Ciudad '" << ciudad << "' agregada exitosamente." << endl;
                }
                break;
            }
            
            case 5: { // Conectar ciudades
                mostrarTodasCiudades();
                cout << "=== NUEVA CONEXION ===" << endl;
                cout << "Seleccione ciudad origen:" << endl;
                string origen = seleccionarCiudadPorNumero();
                cout << "Seleccione ciudad destino:" << endl;
                string destino = seleccionarCiudadPorNumero();
                
                int distancia;
                cout << "Ingrese distancia en km: ";
                cin >> distancia;
                limpiarBuffer();
                
                if (distancia <= 0) {
                    cout << "Error: La distancia debe ser mayor que cero." << endl;
                } else {
                    grafoCiudades.agregarArista(origen, destino, distancia);
                    cout << "Conexion agregada: " << origen << " <-> " << destino 
                         << " (" << distancia << " km)" << endl;
                }
                break;
            }
            
            case 6: {  mostrarTodasCiudades();
                cout << "\n=== CALCULAR RUTA MAS CORTA ===" << endl;
                
                cout << "Seleccione ciudad de origen:" << endl;
                string origen = seleccionarCiudadPorNumero();
                cout << "Seleccione ciudad destino:" << endl;
                string destino = seleccionarCiudadPorNumero();
            
                auto resultado = grafoCiudades.rutaMasCortaBFS(origen, destino);
            
                if (resultado.first.estaVacia()) {
                    cout << "\nNo existe ruta entre " << origen << " y " << destino << endl;
                } else {
                    cout << "\nRuta optima encontrada:" << endl;
                    cout << "Distancia total: " << resultado.second << " km" << endl;
                    cout << "Camino recomendado: ";
                    
                    auto it = resultado.first.obtenerIterador();
                    while (it.tieneSiguiente()) {
                        cout << it.siguiente();
                        if (it.tieneSiguiente()) cout << " -> ";
                    }
                    //cout << endl;
                }
                break;

            }
            
            case 7: // Salir
                cout << "Saliendo del sistema..." << endl;
                return 0;
            
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    }

    return 0;
}