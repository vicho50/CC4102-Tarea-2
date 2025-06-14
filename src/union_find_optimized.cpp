#include "union_find.h"

// Constructor de la clase UnionFind optimizada.
// Inicialmente, tenemos una la estructura con 'n' elementos, cada uno en su propio conjunto, 
// donde se le asigna a cada elemento como su propio padre (raíz del árbol),
// y se inicializa el tamaño de cada conjunto en 1 (todos los elementos están separados al inicio, árboles de tamaño 1)
UnionFind::UnionFind(int n) : padre(n), rango(n, 0) {
    for (int i = 0; i < n; ++i) 
        padre[i] = i;
}

// encontrar(x): buscar el nodo raíz del árbol que contiene a x. Se
// parte de x y se va subiendo por los padres hasta llegar a la raíz.
// En este caso, se realiza una optimización en esta función, para que todos los nodos 
// que se visitan durante esta búsqueda apunten directamente a la raíz,
// reduciendo el tiempo en futuras búsquedas.
int UnionFind::encontrar(int x) {
    if (padre[x] != x)
        padre[x] = encontrar(padre[x]);
    return padre[x];
}

// unir(x,y): une los árboles de x e y, haciendo que la raíz del árbol más pequeño apunte a la del más grande
bool UnionFind::unir(int x, int y) {
    int xr = encontrar(x);
    int yr = encontrar(y);
    if (xr == yr) 
        return false;
    if (tamaño[xr] < tamaño[yr]) {
        padre[xr] = yr;
        tamaño[yr] += tamaño[xr];
    } else {
        padre[yr] = xr;
        tamaño[xr] += tamaño[yr];
    }
    return true;
}
