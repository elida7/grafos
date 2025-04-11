Alumna: Cubaque Elida CI: 27418291
Materia: Estructuras Dinámicas de Datos


>>>>Sistema de Transporte del Estado Zulia usando Grafos no dirigidos ponderados
>> ejercicio 
Desarrollar un programa en C++ que modele las rutas de transporte entre 
ciudades del Zulia utilizando grafos, permitiendo calcular distancias y 
recorridos óptimos.

>> grafos 
Solución con Grafos
Nodos (Vértices): Representan ciudades (Maracaibo, Machiques, etc.)

Aristas: Representan carreteras/rutas entre las ciudades

Pesos: Distancias en kilómetros entre ciudades conectadas

DA una representación natural de redes de transporte y algoritmos eficientes para búsqueda de rutas
ademas es escalable por lo que se puede agregar nuevas ciudades o rutas 

>> Tipo de Grafo Implementado
No dirigido: Las rutas son bidireccionales 

Ponderado: Cada arista tiene un peso (distancia en km)

>>Estructuras de Datos Clave
         Componente	                     Estructura	                          Justificación
Almacenamiento de nodos     	Lista<NodoGrafo> (personalizada)	    Permite agregar/eliminar ciudades    dinámicamente
Conexiones entre nodos	        Listas de procimidad (con pesos)	    Representación eficiente de rutas y distancias
Ciudades visitadas          	Lista<T> (personalizada)	            Evita ciclos en los recorridos
Cola para BFS	                Cola<T> (personalizada)	            Implementación de búsqueda en anchura
Pila para DFS	                Pila<T> (personalizada)	            Implementación de búsqueda en profundidad

>>Algoritmos Implementados
>BFS (Breadth-First Search)  búsqueda en anchura

Propósito: Encontrar todas las ciudades alcanzables desde un origen

Complejidad: O(V + E) (V = nodos, E = aristas)

Uso: Mostrar rutas expandiéndose nivel por nivel

>DFS (Depth-First Search)  búsqueda en profundidad

Propósito: Explorar rutas profundas antes que las laterales

Complejidad: O(V + E)

Uso: Alternativa para análisis de conectividad

>>Funcionamiento del Programa
1. Inicialización
Se crea un grafo con ciudades predefinidas:

ciudades = {"Maracaibo", "Machiques", "Villa del Rosario", ...};
Se establecen conexiones con distancias:

agregarArista("Maracaibo", "Machiques", 100); // 110 km

2. Interacción con el Usuario
Menú principal con opciones numeradas

Selección por números (no requiere escribir nombres)

Validación de entradas para evitar errores

3. Ejemplo de Búsqueda
Usuario selecciona "Mostrar recorrido BFS"

Elige Maracaibo como origen (ingresando "1")

El programa muestra: 
Maracaibo -> Machiques -> Villa del Rosario -> San Francisco -> La Cañada

>>
Este proyecto demuestra que los grafos son ideales para modelar sistemas de transporte porque:
Representan fielmente la conectividad entre ciudades
Permiten algoritmos eficientes para búsqueda de rutas
Son escalables para incorporar nuevas localidades o carreteras
