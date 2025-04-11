#ifndef NODOGRAFO_H
#define NODOGRAFO_H

#include "Lista.h"

// Plantilla para nodo de grafo con dato tipo T y peso de arista tipo U
template <typename T, typename U>
class NodoGrafo {
private:
    T dato;  // Dato almacenado en el nodo
    
    // Lista de nodos adyacentes (destinos de las aristas)
    Lista<NodoGrafo<T, U>*> adyacentes;
    
    // Lista de pesos de las aristas (paralela a adyacentes)
    Lista<U> pesos;

public:
    // Constructor con dato inicial
    NodoGrafo(const T& dato) : dato(dato) {}
    
    // Obtiene el dato almacenado
    T obtenerDato() const { return dato; }
    
    // Establece un nuevo dato
    void establecerDato(const T& nuevoDato) { dato = nuevoDato; }
    
    // Agrega una arista a otro nodo con un peso
    void agregarArista(NodoGrafo<T, U>* destino, U peso) {
        adyacentes.agregar(destino);  // Agrega el nodo destino
        pesos.agregar(peso);          // Agrega el peso correspondiente
    }
    
    // Elimina una arista a un nodo destino específico
    void eliminarArista(NodoGrafo<T, U>* destino) {
        // Busca la posición del destino
        int pos = 0;
        typename Lista<NodoGrafo<T, U>*>::Iterador itAdy = adyacentes.obtenerIterador();
        
        while (itAdy.tieneSiguiente()) {
            if (itAdy.siguiente() == destino) {
                break;  // Encontró el destino
            }
            pos++;
        }
        
        // Si encontró el destino, elimina de ambas listas
        if (pos < adyacentes.obtenerTamano()) {
            // Elimina el nodo destino
            adyacentes.eliminar(destino);
            
            // Busca el peso correspondiente
            typename Lista<U>::Iterador itPesos = pesos.obtenerIterador();
            U pesoAEliminar;
            
            for (int i = 0; i <= pos && itPesos.tieneSiguiente(); i++) {
                pesoAEliminar = itPesos.siguiente();
            }
            
            // Elimina el peso
            pesos.eliminar(pesoAEliminar);
        }
    }
    
    // Obtiene la lista de nodos adyacentes
    const Lista<NodoGrafo<T, U>*>& obtenerAdyacentes() const { return adyacentes; }
    
    // Obtiene la lista de pesos de las aristas
    const Lista<U>& obtenerPesos() const { return pesos; }
};

#endif // NODOGRAFO_H