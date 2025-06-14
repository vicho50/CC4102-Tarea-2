#include "union_find.h"

// Constructor de la clase UnionFind no optimizada.
// Inicialmente, tenemos una la estructura con 'n' elementos, cada uno en su propio conjunto, 
// donde se le asigna a cada elemento como su propio padre (raíz del árbol),
// y se inicializa el tamaño de cada conjunto en 1 (todos los elementos están separados al inicio, árboles de tamaño 1)
UnionFind::UnionFind(int n) : padre(n), tamaño(n, 1) {
    for (int i = 0; i < n; ++i)
        padre[i] = i;
}

// encontrar(x): busca el nodo raíz del árbol que contiene a x. Se
// parte de x y se va subiendo por los padres hasta llegar a la raíz.
// No hay optimización en esta función.
int UnionFind::encontrar(int x) {
    while (padre[x] != x) {
        x = padre[x];
    }
    return x;
}

// unir(x,y): une los árboles de x e y, haciendo que la raíz del árbol más pequeño apunte a la del más grande.
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
