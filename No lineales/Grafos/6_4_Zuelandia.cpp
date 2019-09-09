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
4. Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre
dos ciudades cualesquiera de un país llamado Zuelandia. El problema es sencillo pero
hay que tener en cuenta unos pequeños detalles:
a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas
y por tanto solo permiten un sentido de la circulación.
b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de
ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden
ser usadas para viajar.
c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que
también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser
usadas).
d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido
que absolutamente todos los viajes que se hagan por el país pasen por la capital
del mismo, donde se harán los controles de seguridad pertinentes.
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
• el grafo (matriz de costes) de Zuelandia en situación normal,
• la relación de las ciudades tomadas por los rebeldes,
• la relación de las carreteras cortadas por los rebeldes
• y la capital de Zuelandia, 
calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
zuelandesas en esta situación
*/

template <typename tCoste>
GrafoP<tCoste> zuelandia(GrafoP<tCoste> &G, vector<bool> ciudadesTomadas,
                         matriz<bool> carreterasTomadas, typename GrafoP<tCoste>::vertice capital)
{
    typedef typename GrafoP<tCoste>::vertice vertice;   // vértice
    int n = G.numVert();    // número de vértices
    GrafoP<tCoste> sol(n);  // Grafo ponderado solución

    // Reflejar en G ciudades tomadas por los rebeldes
    for (vertice i = 0; i < n; ++i)
    {
        if (ciudadesTomadas[i])
        {
            for (vertice v = 0; v < n; ++v)
            {
                G[i][v] = GrafoP<tCoste>::INFINITO;
                G[v][i] = GrafoP<tCoste>::INFINITO;
            }
        }
    }

    // Reflejar en G las carreteras que han sido cortadas por los rebeldes
    for (vertice v = 0; v < n; ++v)
    {
        for (vertice w = 0; w < n; ++w)
        {
            if (carreterasTomadas[v][w])
                G[v][w] = GrafoP<tCoste>::INFINITO;
        }
    }

    // Bonus: Si no tuvieramos en cuenta la ciudad capital podremos recorrer libremente
    // las distintas ciudades sin ningún impedimento, por lo que no necesitaríamos
    // hacer DijkstraInv y Dijkstra dado de que no hay ningún destino en concreto

    // matriz<vertice> Camino(n);
    // return Floyd(G,Camino);

    vector<GrafoP<int>::vertice> PDisj, PInv;
    vector<tCoste> CMHastacapital = DijkstraInv(G, capital, PInv);
    vector<tCoste> CMDesdecapital = Dijkstra(G, capital, PDisj);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
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
