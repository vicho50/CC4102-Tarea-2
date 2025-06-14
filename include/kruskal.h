#pragma once
#include "grafo.h"
#include <vector>
#include <tuple>

// Variante 1: arreglo ordenado + Union-Find sin optimizar
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_ordenado(const Grafo& g);

// Variante 2: heap clásico + Union-Find sin optimizar
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_heap(const Grafo& g);

// Variante 3: arreglo ordenado + Union-Find con optimización
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_ordenado_opt(const Grafo& g);

// Variante 4: heap clásico + Union-Find con optimización
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_heap_opt(const Grafo& g);
