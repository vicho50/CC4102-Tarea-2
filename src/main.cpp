#include <iostream>
#include <cassert>
#include "grafo.h"
#include "union_find.h"
#include "kruskal.h"

void pruebas_grafo() {
    Grafo g(3);
    g.agregarArista(0, 1, 4);
    g.agregarArista(1, 2, 7);

    auto aristas = g.obtenerAristas();
    assert(aristas.size() == 2);
    assert(g.numVertices() == 3);

    std::cout << "Pruebas de Grafo pasadas.\n";
}

void pruebas_union_find() {
    UnionFind uf(3);
    assert(uf.encontrar(0) == 0);
    assert(uf.encontrar(1) == 1);
    assert(uf.unir(0, 1));
    assert(uf.encontrar(0) == uf.encontrar(1));
    assert(!uf.unir(0, 1)); // Ya están unidos

    std::cout << "Pruebas de Union-Find pasadas.\n";
}

int main() {
    std::cout << "Ejemplo de uso de Grafo:\n";
    Grafo g(4);
    g.agregarArista(0, 1, 10);
    g.agregarArista(1, 2, 6);
    g.agregarArista(0, 2, 5);

    for (auto [u, v, peso] : g.obtenerAristas()) {
        std::cout << u << " - " << v << " (peso: " << peso << ")\n";
    }

    std::cout << "\nEjemplo de uso de Union-Find:\n";
    UnionFind uf(g.numVertices());
    for (auto [u, v, peso] : g.obtenerAristas()) {
        if (uf.unir(u, v))
            std::cout << "Unidos: " << u << " y " << v << "\n";
        else
            std::cout << "Ya conectados: " << u << " y " << v << "\n";
    }

    std::cout << "\nKruskal (arreglo ordenado):\n";
    auto [peso1, mst1] = kruskal_ordenado(g);
    for (auto [u, v, peso] : mst1)
        std::cout << u << " - " << v << " (peso: " << peso << ")\n";
    std::cout << "Peso total: " << peso1 << "\n";

    std::cout << "\nKruskal (heap clásico):\n";
    auto [peso2, mst2] = kruskal_heap(g);
    for (auto [u, v, peso] : mst2)
        std::cout << u << " - " << v << " (peso: " << peso << ")\n";
    std::cout << "Peso total: " << peso2 << "\n";

    // Ejecutar pruebas automáticas
    std::cout << "\nEjecutando pruebas automáticas...\n";
    pruebas_grafo();
    pruebas_union_find();

    std::cout << "Todas las pruebas pasaron correctamente.\n";
    return 0;
}