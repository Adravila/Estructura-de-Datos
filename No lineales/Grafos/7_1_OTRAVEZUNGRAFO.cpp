#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"

using namespace std;

/*
1. Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente.
Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje más caro
posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino
del viaje.
Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente
el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo. 
*/

template <typename tCoste>
matriz<tCoste> viajeCaro(GrafoP<tCoste> &G, typename GrafoP<tCoste>::vertice& org, typename GrafoP<tCoste>::vertice& des)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    //typename GrafoP<tCoste>::INFINITO infinito;
    matriz<tCoste> costes(G.numVert());
    matriz<vertice> camino(G.numVert());

    costes = Floyd(G,camino);

    for(vertice v = 0; v < costes.dimension(); ++v)
    {
        for(vertice w = 0; w < costes.dimension(); ++w)
        {
            if (costes[org][des] < costes[v][w] && costes[v][w] != 999)
            {
                des = w;
                org = v;
            }
        }
    }
    return costes;
}

int main()
{
    GrafoP<int> G("Data/grafo-2.txt");
    std::cout << G << endl;

    GrafoP<int>::vertice v = 0, w = 0;
    cout << viajeCaro(G,v,w) << endl;
    cout << "Origen: " << v << " y Destino: " << w << endl;
}