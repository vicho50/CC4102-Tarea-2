#include <vector>
#include <tuple>
#include <random>
#include <set>

using Edge = std::tuple<int, int, int>; // (peso, nodo1, nodo2)

std::vector<Edge> generar_grafo(int n, int m, int peso_min = 1, int peso_max = 1000) {
    std::vector<Edge> edges;
    std::set<std::pair<int, int>> usados;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_nodo(0, n - 1);
    std::uniform_int_distribution<> dist_peso(peso_min, peso_max);

    while (edges.size() < m) {
        int u = dist_nodo(gen);
        int v = dist_nodo(gen);
        if (u == v) continue;
        auto par = std::minmax(u, v);
        if (usados.count(par)) continue;
        usados.insert(par);
        int peso = dist_peso(gen);
        edges.emplace_back(peso, par.first, par.second);
    }
    return edges;
}