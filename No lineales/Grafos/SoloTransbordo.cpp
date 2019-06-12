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
 * Problema 8
- 1. tren
- 2. bus
- 3. origen Dijkstra  --BUS [][] TREN -- Dijkstra Inverso -- DESTINO
- 4. origen Dijkstra  --TREN [][] BUS -- Dijkstra Inverso -- DESTINO
- Solución: Floyd
**/

int main()
{
    GrafoP<int> G("Data/grafo-3.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> v;
}