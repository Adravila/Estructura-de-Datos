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

template <typename tCoste>
GrafoP<tCoste> zuelandia(GrafoP<tCoste> &G, vector<bool> ciudadesTomadas,
                         matriz<bool> carreterasTomadas, typename GrafoP<tCoste>::vertice capital)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    // Reflejar en G ciudades tomadas por los rebeldes
    for (vertice i = 0; i < G.numVert(); ++i)
    {
        if (ciudadesTomadas[i])
        {
            for (vertice v = 0; v < G.numVert(); ++v)
            {
                G[i][v] = GrafoP<tCoste>::INFINITO;
                G[v][i] = GrafoP<tCoste>::INFINITO;
            }
        }
    }

    // Reflejar en G las carreteras que han sido cortadas por los rebeldes
    for (vertice v = 0; v < G.numVert(); ++v)
    {
        for (vertice w = 0; w < G.numVert(); ++w)
        {
            if (carreterasTomadas[v][w])
                G[v][w] = GrafoP<tCoste>::INFINITO;
        }
    }

    // Bonus: Si no tuvieramos en cuenta la ciudad capital se podría
    // matriz<vertice> Camino(G.numVert());
    // return Floyd(G,Camino);
    
    vector<GrafoP<int>::vertice> PDisj, PInv;
    vector<tCoste> CMHastacapital = DijkstraInv(G, capital, PInv);
    vector<tCoste> CMDesdecapital = Dijkstra(G, capital, PDisj);

    GrafoP<tCoste> sol(G.numVert());
    
    for (size_t i = 0; i < G.numVert(); i++) {
        for (size_t j = 0; j < G.numVert(); j++) {
            if(i == j)
                sol[i][j] = 0;
            else
                sol[i][j] = suma(CMHastacapital[i], CMDesdecapital[j]);
        }
    }
    return sol;
}

int main()
{
    /**
     * Se utiliará una matriz de booleanos
     * Floyd para obtener la matriz de costes mínimos de cada vértice desde un origen a un destino
     * En el apartado D se realizará Dijsktra y Dijsktra inverso (Para todo origen -> Capital + Capital -> Para todo destino)
    **/

    GrafoP<int> G("Data/zuelandia.txt");
    std::cout << G;
    vector<GrafoP<int>::vertice> v;

    // Crear una matriz de booleanos que refleje las ciudades tomadas
    vector<bool> ciudadesTomadas(G.numVert(), false);
    // Los rebeldes toman las dos últimas ciudades
    ciudadesTomadas[G.numVert() - 1] = true;
    ciudadesTomadas[G.numVert() - 2] = true;

    // Carreteras tomadas (inicialimente como falso)
    matriz<bool> carrreterasCortadas(G.numVert(), false);
    // Los rebeldes explotaron el puente de A --> B
    carrreterasCortadas[3][1] = true;

    // Capital
    typename GrafoP<int>::vertice capital = 0;

    // Resultado
    std::cout << "\nResultado: " << zuelandia(G, ciudadesTomadas, carrreterasCortadas, capital) << endl;
}
