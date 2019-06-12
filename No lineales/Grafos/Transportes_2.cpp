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
 * Problema 6
- RECOMENDACIÓN: Entender cómo se puede viajar
    1 Todo el viaje en tren
    2 Todo el viaje en bus
    3 Tren Dijkstra Inv --> CAMBIO --> Bus Dijkstra
    4 Bus Dijkstra Inv --> CAMBIO --> Tren Dijkstra

- Floyd 1 y 2
- ¿Hacer Floyd para 3 y 4? Floyd lo ha hecho todo
- De esas 4 opciones nos quedamos con el más barato
**/

template <typename tCoste>
GrafoP<tCoste> &agrupar(const GrafoP<tCoste> &G1, const GrafoP<tCoste> &G2, GrafoP<tCoste> &GN)
{
    for (int i = 0; i < G1.numVert(); ++i)
    {
        for (int j = 0; j < G1.numVert(); ++j)
        {
            if (G1[i][j] < G2[i][j])
            {
                GN[i][j] = G1[i][j];
            }
            else
            {
                GN[i][j] = G2[i][j];
            }
        }
    }
    return GN;
}

template <typename tCoste>
matriz<tCoste> costesTransporte(const GrafoP<tCoste> &GTren, const GrafoP<tCoste> &GBus)
{
    GrafoP<tCoste> G(GTren.numVert());
    G = agrupar(GBus, GTren, G);

    matriz<typename GrafoP<tCoste>::vertice> camino;
    matriz<tCoste> coste;
    coste =  Floyd(G,camino);

    return coste;
}

int main()
{
    GrafoP<int> GB("Data/grafo-bus2.txt");
    GrafoP<int> GT("Data/grafo-tren2.txt");
    matriz<int> res = costesTransporte(GT, GB);
    cout << res << endl;
}