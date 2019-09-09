#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"
#include "Cabeceras/Propio/DijkstraInv.hpp"

using namespace std;

/*
7. Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre
N ciudades españolas utilizando el tren (primer grafo) y el autobús (segundo grafo).
Ambos grafos representan viajes entre las mismas N ciudades. 
Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades
concretas del grafo, origen y destino, en las siguientes condiciones:
 - La ciudad origen sólo dispone de transporte por tren.
 - La ciudad destino sólo dispone de transporte por autobús.
 - El sector del taxi, bastante conflictivo en nuestros problemas, sigue en huelga,
por lo que únicamente es posible cambiar de transporte en dos ciudades del
grafo, cambio1 y cambio2, donde las estaciones de tren y autobús están
unidas.
Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre
las ciudades Origen y Destino en estas condiciones. 
*/

/**
 * Problema 7
- ORIGEN -T-> CAMBIO 1 -B-> DESTINO
- ORIGEN ---> CAMBIO 2 -B-> DESTINO
- Dijkstra -- SUMA -- Dijkstra inverso
**/

template <typename tCoste>
tCoste costesTransporte(GrafoP<tCoste> &Gtren, GrafoP<tCoste> &Gbus, typename GrafoP<tCoste>::vertice origen,
                        typename GrafoP<tCoste>::vertice destino, typename GrafoP<tCoste>::vertice c1, typename GrafoP<tCoste>::vertice c2,
                        typename GrafoP<tCoste>::vertice &x, vector<typename GrafoP<tCoste>::vertice> &ruta1,
                        vector<typename GrafoP<tCoste>::vertice> &ruta2)
{
    size_t n = Gtren.numVert();
    vector<tCoste> dij(n);
    vector<tCoste> inv(n);
    tCoste res;
    dij = Dijkstra(Gtren, origen, ruta1);
    inv = DijkstraInv(Gbus, destino, ruta2);
    matriz<typename GrafoP<tCoste>::vertice> P;
    res = min(suma(dij[c1], inv[c1]), suma(dij[c2], inv[c2]));
    if (dij[c1] + inv[c1] < dij[c2] + inv[c2])
        x = c1;
    else
        x = c2;
    return res;
}

int main()
{
    GrafoP<int> GB("Data/grafo-bus2.txt");
    GrafoP<int> GT("Data/grafo-tren2.txt");

    typename GrafoP<int>::vertice origen = 3, destino = 5, cambio = 5, c1 = 1, c2 = 2, x;
    vector<typename GrafoP<int>::vertice> ruta1, ruta2;
    int res = costesTransporte(GT, GB, origen, destino, c1, c2, x, ruta1, ruta2);
    cout << res << endl;
}