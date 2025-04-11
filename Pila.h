#ifndef PILA_H
#define PILA_H

#include "Lista.h"

// Plantilla para pila genérica (LIFO)
template <typename T>
class Pila {
private:
    Lista<T> lista;  // Usa lista implementada

public:
    // Agrega un elemento a la cima de la pila
    void apilar(const T& dato) { lista.agregar(dato); }
    
    // Remueve y devuelve el elemento de la cima
    T desapilar() {
        if (lista.estaVacia()) throw "Pila vacía";  // Verifica vacío
        
        //  lista simple, se recorre para encontrar el último
        typename Lista<T>::Iterador it = lista.obtenerIterador();
        T ultimo;
        
        // Recorre hasta el final
        while (it.tieneSiguiente()) {
            ultimo = it.siguiente();  // Guarda cada elemento hasta el último
        }
        
        lista.eliminar(ultimo);  // Elimina el último elemento
        return ultimo;          // Devuelve el elemento eliminado
    }
    
    // Devuelve el elemento en la cima sin removerlo
    T& cima() {
        if (lista.estaVacia()) throw "Pila vacía";
        
        typename Lista<T>::Iterador it = lista.obtenerIterador();
        T* ultimo = nullptr;
        
        // Recorre hasta el final
        while (it.tieneSiguiente()) {
            ultimo = &it.siguiente();  // Guarda dirección de cada elemento
        }
        return *ultimo;  // Devuelve el último elemento
    }
    
    // Verifica si la pila está vacía
    bool estaVacia() const { return lista.estaVacia(); }
};

#endif // PILA_H