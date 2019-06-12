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
 * Problema 9
- Se debe realizar 4 viajes 
- Se debe realizar 2 veces Dijkstra en este ejercicio
**/

int main()
{
    GrafoP<int> G("Data/grafo-3.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> v;
}