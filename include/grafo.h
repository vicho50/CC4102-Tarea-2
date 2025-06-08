#pragma once
#include <vector>
#include <tuple>

class Grafo {
public:
    Grafo(int n);
    void agregarArista(int u, int v, int peso);
    std::vector<std::tuple<int, int, int>> obtenerAristas() const;
    int numVertices() const;
private:
    int n;
    std::vector<std::tuple<int, int, int>> aristas;
};