#include "grafo.h"

Grafo::Grafo(int n) : n(n) {}

void Grafo::agregarArista(int u, int v, int peso) {
    aristas.push_back({u, v, peso});
}

std::vector<std::tuple<int, int, int>> Grafo::obtenerAristas() const {
    return aristas;
}

int Grafo::numVertices() const {
    return n;
}