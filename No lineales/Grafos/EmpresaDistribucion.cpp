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
 * Problema 3
- En este problema se utilizará Dijkstra dado de que se inicia desde UN ORIGEN,
- Las subveciones (de gastos mínimos) se almacenan en un vector
- El coste mínimo debe se proporcional
- Empezar desde el más barato hasta que se acabe la cantidad
**/

void EmpresaDistribucion(const GrafoP<int>& G, const GrafoP<int>::vertice ciudad_org, vector<int> subvenciones, vector<int> capacidad)
{
    vector<GrafoP<int>::vertice> dij;
    cout << Dijkstra(G,ciudad_org,dij) << endl;
}

int main()
{
    GrafoP<int> G("Data/grafo-3.txt");
    cout << G << endl;
    vector<int> subvenciones = {0, 30, 25, 40};
    vector<int> capacidad = {0, 20, 20, 20};
    EmpresaDistribucion(G,0,subvenciones,capacidad);
}