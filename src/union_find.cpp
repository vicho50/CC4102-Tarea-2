#include "union_find.h"

UnionFind::UnionFind(int n) : padre(n), rango(n, 0) {
    for (int i = 0; i < n; ++i) padre[i] = i;
}

int UnionFind::encontrar(int x) {
    if (padre[x] != x)
        padre[x] = encontrar(padre[x]);
    return padre[x];
}

bool UnionFind::unir(int x, int y) {
    int xr = encontrar(x), yr = encontrar(y);
    if (xr == yr) return false;
    if (rango[xr] < rango[yr]) padre[xr] = yr;
    else {
        padre[yr] = xr;
        if (rango[xr] == rango[yr]) rango[xr]++;
    }
    return true;
}