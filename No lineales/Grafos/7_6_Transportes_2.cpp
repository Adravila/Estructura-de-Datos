#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Propio/DijkstraInv.hpp"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"

using namespace std;

/* DUDAS
6. Al dueño de una agencia de transportes se le plantea la siguiente situación. La
agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades españolas
utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de
costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autobús
(por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide
que los taxis de toda España se encuentran en estos momentos en huelga general, lo que
implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que,
por casualidad, las estaciones de tren y autobús están unidas.

Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de
viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús,
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
*/

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
matriz<tCoste> costesTransporte(const GrafoP<tCoste> &GTren, const GrafoP<tCoste> &GBus, typename GrafoP<tCoste>::vertice cambio)
{

    size_t n = GTren.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;

    matriz<typename GrafoP<tCoste>::vertice> caminoTren, caminoBus;
    matriz<tCoste> costeGTren, costeGBus, costeFinal;

    costeGTren = Floyd(GTren, caminoTren);
    costeGBus = Floyd(GBus, caminoBus);

    for (vertice i = 0; i < n; ++i)
    {
        for (vertice j = 0; j < n; ++j)
        {
            if (costeGTren[i][j] < costeGBus[i][j])
                costeGTren[i][j] = costeGBus[i][j];
        }
    }

    costeFinal = costeGTren;

    vector<vertice> caminoDij, caminoDijInv;
    vector<tCoste> costeD, costeDI; 
    
    costeD = Dijkstra(GTren, cambio, caminoDij);
    costeDI = DijkstraInv(GBus, cambio, caminoDijInv);

    for (vertice i = 0; i < n; ++i)
    {
        for (vertice j = 0; j < n; ++j)
        {
            if(costeFinal[i][j] < suma(costeD[j], costeDI[i]))
                costeFinal[i][j] = suma(costeD[j], costeDI[i]);
        }
    }

    return costeFinal;
}

int main()
{
    GrafoP<int> GB("Data/grafo-bus2.txt");
    GrafoP<int> GT("Data/grafo-tren2.txt");
    
    typename GrafoP<int>::vertice cambio = 3;
    
    matriz<int> res = costesTransporte(GT, GB, cambio);
    cout << res << endl;
}