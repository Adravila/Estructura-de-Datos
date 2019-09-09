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
2. Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que
minimiza la suma de las distancias mínimas a sus dos nodos más alejados. Definiremos
el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más
alejados del pseudocentro del grafo.
 Dado un grafo conexo representado mediante matriz de costes, implementa un
subprograma que devuelva la longitud de su diámetro.
*/

template <typename tCoste>
int Diametro(const GrafoP<tCoste> &G)
{
    int suma = 0;
    typedef typename GrafoP<tCoste>::vertice vertice;

    matriz<vertice> Camino(G.numVert());
    matriz<int> Costes(G.numVert());
    Costes = Floyd(G, Camino);
    for (int i = 0; i < Costes.dimension(); i++)
        sort(Costes[i].begin(), Costes[i].end());
    suma = 999;
    for (int j = 0; j < Costes.dimension(); j++)
    {
        if ((Costes[j][Costes.dimension() - 1] + Costes[j][Costes.dimension() - 2]) < suma)
        {
            suma = Costes[j][Costes.dimension() - 1] + Costes[j][Costes.dimension() - 2];
        }
    }
    return suma;
}

int main()
{
    GrafoP<int> G("Data/grafo-3.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> v;
    std::cout << "\nResultado Diámetro: " << Diametro(G) << endl;
}
