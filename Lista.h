#ifndef LISTA_H
#define LISTA_H

// Plantilla para lista genérica
template <typename T>
class Lista {
private:
    // Estructura interna para nodos de la lista
    struct NodoLista {
        T dato;                 // Dato almacenado en el nodo
        NodoLista* siguiente;   // Puntero al siguiente nodo
        
        // Constructor del nodo
        NodoLista(const T& dato) : dato(dato), siguiente(nullptr) {}
    };
    
    NodoLista* cabeza;  // Puntero al primer nodo
    NodoLista* cola;    // Puntero al último nodo
    int tamano;         // Cantidad de elementos en la lista

public:
    // Constructor - inicializa lista vacía
    Lista() : cabeza(nullptr), cola(nullptr), tamano(0) {}
    
    // Destructor - libera memoria de todos los nodos
    ~Lista();
    
    // Agrega un elemento al final de la lista
    void agregar(const T& dato);
    
    // Elimina un elemento específico de la lista
    void eliminar(const T& dato);
    
    // Verifica si un elemento está en la lista
    bool contiene(const T& dato) const;
    
    // Obtiene el tamaño actual de la lista
    int obtenerTamano() const { return tamano; }
    
    // Verifica si la lista está vacía
    bool estaVacia() const { return tamano == 0; }
    
    // Clase iterador para recorrer la lista
    class Iterador {
    private:
        NodoLista* actual;  // Nodo actual del iterador
        
    public:
        // Constructor del iterador
        Iterador(NodoLista* nodo) : actual(nodo) {}
        
        // Verifica si hay más elementos por recorrer
        bool tieneSiguiente() const { return actual != nullptr; }
        
        // Avanza al siguiente elemento y devuelve el actual
        T& siguiente() { 
            T& dato = actual->dato;     // Guarda el dato actual
            actual = actual->siguiente; // Avanza al siguiente nodo
            return dato;               // Devuelve el dato guardado
        }
    };
    
    // Obtiene un iterador para recorrer la lista
    Iterador obtenerIterador() const { return Iterador(cabeza); }
};

#include "Lista.cpp"
#endif // LISTA_H