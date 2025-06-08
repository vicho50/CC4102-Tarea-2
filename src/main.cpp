#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include "grafo.h"
#include "union_find.h"
#include "kruskal.h"
#include "graph_generator.h"

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
    std::ofstream resultados("resultados.csv");
    resultados << "n,m,algoritmo,tiempo_ms\n";
    std::vector<int> ns = {100, 500, 1000, 2000}; // Tamaños de grafo
    std::vector<double> densidades = {1.5, 2, 3}; // m = densidad * n

    for (int n : ns) {
        for (double dens : densidades) {
            int m = static_cast<int>(n * dens);
            for (int rep = 0; rep < 5; ++rep) { // Repetir 5 veces para cada n y m
                // Generar grafo aleatorio (vector de aristas)
                auto edges = generar_grafo(n, m);

                // Construir objeto Grafo con las aristas generadas
                Grafo g(n);
                for (const auto& [peso, u, v] : edges) {
                    g.agregarArista(u, v, peso);
                }

                // Algoritmo 1: Kruskal con arreglo ordenado
                auto start1 = std::chrono::high_resolution_clock::now();
                auto [peso1, mst1] = kruskal_ordenado(g);
                auto end1 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> dur1 = end1 - start1;
                resultados << n << "," << m << ",arreglo," << dur1.count() << "\n";

                // Algoritmo 2: Kruskal con heap
                auto start2 = std::chrono::high_resolution_clock::now();
                auto [peso2, mst2] = kruskal_heap(g);
                auto end2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> dur2 = end2 - start2;
                resultados << n << "," << m << ",heap," << dur2.count() << "\n";
            }
        }
    }
    resultados.close();

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

    // Medir tiempo de ejecución
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion = end - start;
    std::cout << "Tiempo: " << duracion.count() << " ms" << std::endl;

    // Ejecutar pruebas automáticas
    std::cout << "\nEjecutando pruebas automáticas...\n";
    pruebas_grafo();
    pruebas_union_find();

    std::cout << "Todas las pruebas pasaron correctamente.\n";
    return 0;
}