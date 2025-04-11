#include "Lista.h"

// Destructor - libera toda la memoria de la lista
template <typename T>
Lista<T>::~Lista() {
    NodoLista* actual = cabeza;  // Comienza desde la cabeza
    
    // Recorre todos los nodos
    while (actual != nullptr) {
        NodoLista* siguiente = actual->siguiente;  // Guarda referencia al siguiente
        delete actual;          // Libera el nodo actual
        actual = siguiente;     // Avanza al siguiente nodo
    }
}

// Agrega un nuevo elemento al final de la lista
template <typename T>
void Lista<T>::agregar(const T& dato) {
    // Crea un nuevo nodo con el dato
    NodoLista* nuevoNodo = new NodoLista(dato);
    
    // Si la lista está vacía
    if (cola == nullptr) {
        cabeza = cola = nuevoNodo;  // El nuevo nodo es cabeza y cola
    } else {
        cola->siguiente = nuevoNodo;  // El actual último apunta al nuevo
        cola = nuevoNodo;            // El nuevo nodo es ahora la cola
    }
    tamano++;  // Incrementa el tamaño
}

// Elimina un elemento específico de la lista
template <typename T>
void Lista<T>::eliminar(const T& dato) {
    NodoLista* anterior = nullptr;  // Nodo anterior al actual
    NodoLista* actual = cabeza;     // Comienza desde la cabeza
    
    // Busca el nodo con el dato a eliminar
    while (actual != nullptr && actual->dato != dato) {
        anterior = actual;          // Guarda el nodo anterior
        actual = actual->siguiente; // Avanza al siguiente
    }
    
    // Si encontró el nodo
    if (actual != nullptr) {
        // Si es el primer nodo
        if (anterior == nullptr) {
            cabeza = actual->siguiente;  // La cabeza ahora es el siguiente
        } else {
            // El anterior salta al siguiente del actual
            anterior->siguiente = actual->siguiente;
        }
        
        // Si era el último nodo
        if (actual == cola) {
            cola = anterior;  // La cola ahora es el anterior
        }
        
        delete actual;  // Libera memoria
        tamano--;       // Reduce el tamaño
    }
}

// Verifica si un elemento está en la lista
template <typename T>
bool Lista<T>::contiene(const T& dato) const {
    NodoLista* actual = cabeza;  // Comienza desde la cabeza
    
    // Recorre la lista
    while (actual != nullptr) {
        if (actual->dato == dato) {
            return true;  // Encontró el dato
        }
        actual = actual->siguiente;  // Avanza al siguiente
    }
    return false;  // No encontró el dato
}