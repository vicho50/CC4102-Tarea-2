#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include "grafo.h"
#include "union_find_not_optimized.h"
#include "union_find_optimized.h"
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
    UnionFindBasico uf(3);
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
    std::vector<int> ns = {100, 500, 1000, 2000};  // Tamaños de grafo
    std::vector<double> densidades = {1.5, 2, 3};  // m = densidad * n

    for (int n : ns) {
        for (double dens : densidades) {
            int m = static_cast<int>(n * dens);
            for (int rep = 0; rep < 5; ++rep) {
                auto edges = generar_grafo(n, m);
                Grafo g(n);
                for (const auto& [peso, u, v] : edges) {
                    g.agregarArista(u, v, peso);
                }

                // Variante 1: arreglo ordenado + Union-Find sin optimizar
                auto t1 = std::chrono::high_resolution_clock::now();
                auto [peso1, mst1] = kruskal_ordenado(g);
                auto t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> d1 = t2 - t1;
                resultados << n << "," << m << ",arreglo_no_opt," << d1.count() << "\n";

                // Variante 2: heap clásico + Union-Find sin optimizar
                auto t3 = std::chrono::high_resolution_clock::now();
                auto [peso2, mst2] = kruskal_heap(g);
                auto t4 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> d2 = t4 - t3;
                resultados << n << "," << m << ",heap_no_opt," << d2.count() << "\n";

                // Variante 3: arreglo ordenado + Union-Find con optimización)
                auto t5 = std::chrono::high_resolution_clock::now();
                auto [peso3, mst3] = kruskal_ordenado_opt(g);
                auto t6 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> d3 = t6 - t5;
                resultados << n << "," << m << ",arreglo_opt," << d3.count() << "\n";

                // Variante 4: heap clásico + Union-Find con optimización
                auto t7 = std::chrono::high_resolution_clock::now();
                auto [peso4, mst4] = kruskal_heap_opt(g);
                auto t8 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> d4 = t8 - t7;
                resultados << n << "," << m << ",heap_opt," << d4.count() << "\n";
            }
        }
    }
    resultados.close();

    std::cout << "Experimentos completados. Resultados en 'resultados.csv'.\n";

    // Ejecutar pruebas
    std::cout << "\nEjecutando pruebas automáticas...\n";
    pruebas_grafo();
    pruebas_union_find();
    std::cout << "Todas las pruebas pasaron correctamente.\n";

    return 0;
}

