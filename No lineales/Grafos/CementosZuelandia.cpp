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

/**
 * Problema 4
- Considerar el viaje de ida y de vuelta
- Dijkstra y Dijkstra inverso (en ese orden)
- Desde la capital, hacer Dijkstra, el paso intermedio será ¿multiplicar? y sumar, hacer Dijkstra inverso hacia la capital
**/

template <typename tCoste>
int CementosZuelandia(const GrafoP<tCoste> &G, const typename GrafoP<tCoste>::vertice ciudad_org, vector<int> cantidad)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    vector<vertice> Camino;
    vector<int> Costes, CostesInverso;

    Costes = Dijkstra(G,ciudad_org,Camino);
    CostesInverso = DijkstraInv(G,ciudad_org,Camino);

    int kilometros = 0;
    for(int i = 0; i < cantidad.size(); ++i)
    {
        if(cantidad[i] > 0)
        {
            kilometros += Costes[i] + CostesInverso[i] * cantidad[i];
        }
    }
    return kilometros;
}

int main()
{
    GrafoP<int> G("Data/grafo-3.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> v;
    const GrafoP<int>::vertice ciudad_org = 0;
    vector<int> cantidad(G.numVert(), 0);
    
    // ¿Qué ciudades contienen cantidades de cemento? Ej: Ciudad 1 y 3
    cantidad[1] = 8;
    cantidad[3] = 3;

    // Llamar función CementosZuelandia
    cout << "\nCantidad de kilómetros recorridos: " << CementosZuelandia(G, ciudad_org, cantidad) << " km" << endl;
}