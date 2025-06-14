#pragma once
#include <vector>

class UnionFindOpt {
public:
    UnionFindOpt(int n);
    int encontrar(int x);
    bool unir(int x, int y);
private:
    std::vector<int> padre, rango;
};
