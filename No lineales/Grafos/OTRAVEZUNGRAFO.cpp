#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"

using namespace std;

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