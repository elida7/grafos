#ifndef GRAFO_H
#define GRAFO_H

#include <unordered_map>
#include <utility>  // Para std::pair
#include <limits>   // Para std::numeric_limits
#include "NodoGrafo.h"
#include "Lista.h"
#include "Pila.h"
#include "Cola.h"

// Plantilla para grafo con nodos tipo T y pesos de aristas tipo U
template <typename T, typename U>
class Grafo {
private:
    Lista<NodoGrafo<T, U>*> nodos;  // Lista de todos los nodos del grafo

public:
    // Constructor por defecto
    Grafo() = default;
    
    // Destructor - libera toda la memoria de los nodos
    ~Grafo() {
        typename Lista<NodoGrafo<T, U>*>::Iterador it = nodos.obtenerIterador();
        
        while (it.tieneSiguiente()) {
            delete it.siguiente();  // Libera cada nodo
        }
    }
    
    // Busca un nodo por su dato 
    NodoGrafo<T, U>* buscarNodo(const T& dato) const {
        typename Lista<NodoGrafo<T, U>*>::Iterador it = nodos.obtenerIterador();
        
        while (it.tieneSiguiente()) {
            NodoGrafo<T, U>* nodo = it.siguiente();
            if (nodo->obtenerDato() == dato) {
                return nodo;  // Devuelve el nodo si lo encuentra
            }
        }
        return nullptr;  // No encontró el nodo
    }
    
    // Agrega un nuevo nodo al grafo
    void agregarNodo(const T& dato) {
        if (!buscarNodo(dato)) {  // Evita duplicados
            nodos.agregar(new NodoGrafo<T, U>(dato));  // Crea y agrega nuevo nodo
        }
    }
    
    // Agrega una arista entre dos nodos con un peso
    void agregarArista(const T& origen, const T& destino, U peso, bool dirigido = false) {
        NodoGrafo<T, U>* nodoOrigen = buscarNodo(origen);
        NodoGrafo<T, U>* nodoDestino = buscarNodo(destino);
        
        // Si ambos nodos existen
        if (nodoOrigen && nodoDestino) {
            // Agrega arista del origen al destino
            nodoOrigen->agregarArista(nodoDestino, peso);
            
            // Si no es dirigido, agrega arista inversa
            if (!dirigido) {
                nodoDestino->agregarArista(nodoOrigen, peso);
            }
        }
    }
    
    // Recorrido en anchura (BFS) desde un nodo inicial
    Lista<T> recorridoEnAnchura(const T& inicio) const {
        Lista<T> resultado;    // Almacena el orden de recorrido
        Lista<T> visitados;    // Nodos ya visitados
        Cola<NodoGrafo<T, U>*> cola;  // Cola para BFS
        
        NodoGrafo<T, U>* nodoInicio = buscarNodo(inicio);
        if (!nodoInicio) return resultado;  // Si no existe, devuelve vacío
        
        cola.encolar(nodoInicio);          // Encola el nodo inicial
        visitados.agregar(inicio);         // Marca como visitado
        
        while (!cola.estaVacia()) {
            NodoGrafo<T, U>* actual = cola.desencolar();  // Saca el primero
            resultado.agregar(actual->obtenerDato());    // Agrega al resultado
            
            // Recorre todos los adyacentes
            typename Lista<NodoGrafo<T, U>*>::Iterador it = actual->obtenerAdyacentes().obtenerIterador();
            
            while (it.tieneSiguiente()) {
                NodoGrafo<T, U>* adyacente = it.siguiente();
                T datoAdyacente = adyacente->obtenerDato();
                
                // Si no ha sido visitado
                if (!visitados.contiene(datoAdyacente)) {
                    visitados.agregar(datoAdyacente);  // Marca como visitado
                    cola.encolar(adyacente);          // Encola el adyacente
                }
            }
        }
        
        return resultado;
    }
    
    // Recorrido en profundidad (DFS) desde un nodo inicial
    Lista<T> recorridoEnProfundidad(const T& inicio) const {
        Lista<T> resultado;    // Almacena el orden de recorrido
        Lista<T> visitados;    // Nodos ya visitados
        Pila<NodoGrafo<T, U>*> pila;  // Pila para DFS
        
        NodoGrafo<T, U>* nodoInicio = buscarNodo(inicio);
        if (!nodoInicio) return resultado;  // Si no existe, devuelve vacío
        
        pila.apilar(nodoInicio);          // Apila el nodo inicial
        visitados.agregar(inicio);         // Marca como visitado
        
        while (!pila.estaVacia()) {
            NodoGrafo<T, U>* actual = pila.desapilar();  // Saca el tope
            resultado.agregar(actual->obtenerDato());    // Agrega al resultado
            
            // Recorre todos los adyacentes
            typename Lista<NodoGrafo<T, U>*>::Iterador it = actual->obtenerAdyacentes().obtenerIterador();
            
            while (it.tieneSiguiente()) {
                NodoGrafo<T, U>* adyacente = it.siguiente();
                T datoAdyacente = adyacente->obtenerDato();
                
                // Si no ha sido visitado
                if (!visitados.contiene(datoAdyacente)) {
                    visitados.agregar(datoAdyacente);  // Marca como visitado
                    pila.apilar(adyacente);           // Apila el adyacente
                }
            }
        }
        
        return resultado;
    }
    
    // Ruta más corta usando BFS modificado para pesos
    std::pair<Lista<T>, U> rutaMasCortaBFS(const T& inicio, const T& fin) const {
        // Estructuras auxiliares
        std::unordered_map<T, U> distancias;
        std::unordered_map<T, T> predecesores;
        Lista<T> camino;
        U distanciaTotal = 0;
        
        // Inicialización de distancias
        typename Lista<NodoGrafo<T, U>*>::Iterador itNodos = nodos.obtenerIterador();
        while (itNodos.tieneSiguiente()) {
            T ciudad = itNodos.siguiente()->obtenerDato();
            distancias[ciudad] = std::numeric_limits<U>::max();
        }
        distancias[inicio] = 0;
        
        Cola<T> cola;
        cola.encolar(inicio);
        
        // BFS modificado para pesos
        while (!cola.estaVacia()) {
            T actual = cola.desencolar();
            
            NodoGrafo<T, U>* nodoActual = buscarNodo(actual);
            if (!nodoActual) continue;
            
            // Recorrer vecinos y pesos
            typename Lista<NodoGrafo<T, U>*>::Iterador itAdy = nodoActual->obtenerAdyacentes().obtenerIterador();
            typename Lista<U>::Iterador itPeso = nodoActual->obtenerPesos().obtenerIterador();
            
            while (itAdy.tieneSiguiente() && itPeso.tieneSiguiente()) {
                T vecino = itAdy.siguiente()->obtenerDato();
                U peso = itPeso.siguiente();
                
                if (distancias[actual] + peso < distancias[vecino]) {
                    distancias[vecino] = distancias[actual] + peso;
                    predecesores[vecino] = actual;
                    cola.encolar(vecino);
                }
            }
        }
        
        // Reconstruir camino si existe 
        if (distancias[fin] != std::numeric_limits<U>::max()) {
            distanciaTotal = distancias[fin];
            
            // camino en orden inverso
            std::vector<T> caminoInverso;
            T actual = fin;
            while (actual != inicio) {
                caminoInverso.push_back(actual);
                actual = predecesores[actual];
            }
            caminoInverso.push_back(inicio);
            
            // camino en orden correcto
            for (auto it = caminoInverso.rbegin(); it != caminoInverso.rend(); ++it) {
                camino.agregar(*it);
            }
        }
        
        return std::make_pair(camino, distanciaTotal);
    }
};

#endif // GRAFO_H