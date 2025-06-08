#pragma once
#include "grafo.h"
#include <vector>
#include <tuple>

// Versión 1: usando arreglo de aristas ordenado
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_ordenado(const Grafo& g);

// Versión 2: usando heap clásico
std::pair<int, std::vector<std::tuple<int, int, int>>>
kruskal_heap(const Grafo& g);