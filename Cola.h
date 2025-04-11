#ifndef COLA_H
#define COLA_H

#include "Lista.h"

template <typename T>
class Cola {
private:
    Lista<T> lista;  // implementar lista

public:
    // Agrega a la cola
    void encolar(const T& dato) { lista.agregar(dato); }
    
    // elimanar y devolver el primero de la cola
    T desencolar() {
        if (lista.estaVacia()) throw "Cola vacía";  // Verifica vacío
        
        // Obtiener el primero
        typename Lista<T>::Iterador it = lista.obtenerIterador();
        T primero = it.siguiente();
        
        lista.eliminar(primero);  // Elimina 
        return primero;           // Devuelve
    }
    
    // Devolver el primero sin eliminar
    T& frente() {
        if (lista.estaVacia()) throw "Cola vacía";
        
        typename Lista<T>::Iterador it = lista.obtenerIterador();
        return it.siguiente();  // Devolver el primero
    }
    
    // Verificar está vacía
    bool estaVacia() const { return lista.estaVacia(); }
};

#endif // COLA_H