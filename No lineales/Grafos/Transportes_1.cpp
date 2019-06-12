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
 * Problema 5
 * 1. Son tres matrices en la que representan el coste (en euros) del viaje a cada una de las distintas ciudades
 * de sus respectivos países. Estos viajes se recorreran en coche, tren o en avión.
 * 2. Hay que tener en cuenta de que el cliente no puede viajar en un determinado transporte, hay que tenerlo en
 * cuenta a la hora de crear una nueva matriz para agrupar y seleccionar los medios más baratos de recorrer
 * 3. Una vez creada la matriz de costes se debe tener hacer Dijkstra para que nos devuelva un vector de costes mínimo
- Ejemplo: Cádiz - San Fernando 1,4 (coste mínimo) bus, 1,6 tren
- Realizar Dijkstra
- Devuelve un vector de booleanos
- Simplemente hay que llegar (si tienes dinero para llegar devuelve true, en caso contrario false)
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
vector<bool> alcancePresupuesto(const GrafoP<tCoste> &GTren, const GrafoP<tCoste> &GAvion, const GrafoP<tCoste> &GCoche,
                                typename GrafoP<tCoste>::vertice origen, int presupuesto, int alergia)
{
    vector<bool> permitidos(GTren.numVert(), false);
    GrafoP<tCoste> G(GTren.numVert());
    switch (alergia)
    {
    case 1:
        G = agrupar(GTren, GAvion, G);
        break; // Mareos en el coche
    case 2:
        G = agrupar(GTren, GCoche, G);
        break; // Mareos en el avión
    default:
        G = agrupar(GCoche, GAvion, G);
        break; // Mareos en el tren
    }
    vector<typename GrafoP<tCoste>::vertice> camino;
    vector<tCoste> coste;
    coste = Dijkstra(G, origen, camino);
    for (int i = 0; i < G.numVert(); ++i)
    {
        if (coste[i] <= presupuesto)
        {
            permitidos[i] = true;
        }
    }

    return permitidos;
}

int main()
{
    GrafoP<int> GA("Data/grafo-avion.txt");
    GrafoP<int> GC("Data/grafo-bus.txt");
    GrafoP<int> GT("Data/grafo-tren.txt");
    typename GrafoP<int>::vertice origen = 0;
    int presupuesto = 550;
    int alergia = 2;
    vector<bool> permitidos = alcancePresupuesto(GA, GC, GT, origen, presupuesto, alergia);

    cout << "Está permitido viajar a las ciudades: ";
    for (int i = 1; i < permitidos.size(); ++i)
    {
        if (permitidos[i])
            cout << i << " ";
    }
    cout << endl;
}