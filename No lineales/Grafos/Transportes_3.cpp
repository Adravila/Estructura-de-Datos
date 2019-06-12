#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"

using namespace std;

/**
 * Problema 7
- ORIGEN -T-> CAMBIO 1 -B-> DESTINO
- ORIGEN ---> CAMBIO 2 -B-> DESTINO
- Dijkstra -- SUMA -- Dijkstra inverso

**/

int main()
{
    GrafoP<int> G("Data/grafo-3.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> v;
}