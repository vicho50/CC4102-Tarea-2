#pragma once
#include <vector>

class UnionFind {
public:
    UnionFind(int n);
    int encontrar(int x);
    bool unir(int x, int y);
private:
    std::vector<int> padre;
    std::vector<int> rango;
};
