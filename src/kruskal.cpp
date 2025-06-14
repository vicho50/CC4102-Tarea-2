#include "kruskal.h"
#include "union_find_not_optimized.h"
#include "union_find_optimized.h"
#include <algorithm>
#include <queue>

// Variante 1: arreglo ordenado + Union-Find sin optimizar
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_ordenado(const Grafo& g) {
    auto aristas = g.obtenerAristas();
    std::sort(aristas.begin(), aristas.end(),
        [](const auto& a, const auto& b) {
            return std::get<2>(a) < std::get<2>(b); // comparar por peso
        });

    UnionFind uf(g.numVertices());
    int peso_total = 0;
    std::vector<std::tuple<int, int, int>> mst;

    for (const auto& [u, v, peso] : aristas) {
        if (uf.unir(u, v)) {
            mst.push_back({u, v, peso});
            peso_total += peso;
        }
    }

    return {peso_total, mst};
}

// Variante 2: heap clásico + Union-Find sin optimizar
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_heap(const Grafo& g) {
    auto cmp = [](const std::tuple<int, int, int>& a,
                  const std::tuple<int, int, int>& b) {
        return std::get<2>(a) > std::get<2>(b);
    };

    std::priority_queue<
        std::tuple<int, int, int>,
        std::vector<std::tuple<int, int, int>>,
        decltype(cmp)
    > heap(cmp);

    for (const auto& arista : g.obtenerAristas())
        heap.push(arista);

    UnionFind uf(g.numVertices());
    int peso_total = 0;
    std::vector<std::tuple<int, int, int>> mst;

    while (!heap.empty() && mst.size() < g.numVertices() - 1) {
        auto [u, v, peso] = heap.top();
        heap.pop();

        if (uf.unir(u, v)) {
            mst.push_back({u, v, peso});
            peso_total += peso;
        }
    }

    return {peso_total, mst};
}

// Variante 3: arreglo ordenado + Union-Find con optimización
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_ordenado_opt(const Grafo& g) {
    auto aristas = g.obtenerAristas();
    std::sort(aristas.begin(), aristas.end(),
        [](const auto& a, const auto& b) {
            return std::get<2>(a) < std::get<2>(b);
        });

    UnionFindOpt uf(g.numVertices());
    int peso_total = 0;
    std::vector<std::tuple<int, int, int>> mst;

    for (const auto& [u, v, peso] : aristas) {
        if (uf.unir(u, v)) {
            mst.push_back({u, v, peso});
            peso_total += peso;
        }
    }

    return {peso_total, mst};
}

// Variante 4: heap clásico + Union-Find con optimización
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_heap_opt(const Grafo& g) {
    auto cmp = [](const std::tuple<int, int, int>& a,
                  const std::tuple<int, int, int>& b) {
        return std::get<2>(a) > std::get<2>(b);
    };

    std::priority_queue<
        std::tuple<int, int, int>,
        std::vector<std::tuple<int, int, int>>,
        decltype(cmp)
    > heap(cmp);

    for (const auto& arista : g.obtenerAristas())
        heap.push(arista);

    UnionFindOpt uf(g.numVertices());
    int peso_total = 0;
    std::vector<std::tuple<int, int, int>> mst;

    while (!heap.empty() && mst.size() < g.numVertices() - 1) {
        auto [u, v, peso] = heap.top();
        heap.pop();

        if (uf.unir(u, v)) {
            mst.push_back({u, v, peso});
            peso_total += peso;
        }
    }

    return {peso_total, mst};
}
