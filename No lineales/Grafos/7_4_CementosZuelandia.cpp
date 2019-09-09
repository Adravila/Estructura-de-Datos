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
4. Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”. Empresa
dedicada a la fabricación y distribución de cemento, sita en la capital de Zuelandia. Para
la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia)
dispones de una flota de camiones y de una plantilla de conductores zuelandeses.
El problema a resolver tiene que ver con el carácter del zuelandés. El zuelandés es
una persona que se toma demasiadas “libertades” en su trabajo, de hecho, tienes
fundadas sospechas de que tus conductores utilizan los camiones de la empresa para
usos particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los
kilómetros que recorren tus camiones. 
Todos los días se genera el parte de trabajo, en el que se incluyen el número de
cargas de cemento (1 carga = 1 camión lleno de cemento) que debes enviar a cada
cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay
que enviar cargas a todos los clientes, y además, puedes suponer razonablemente que tu
flota de camiones es capaz de hacer el trabajo diario.
Para la resolución del problema quizá sea interesante recordar que Zuelandia es un
país cuya especial orografía sólo permite que las carreteras tengan un sentido de
circulación.
Implementa una función que dado el grafo con las distancias directas entre las
diferentes ciudades zuelandesas, el parte de trabajo diario, y la capital de Zuelandia,
devuelva la distancia total en kilómetros que deben recorrer tus camiones en el día, para
que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la
empresa. 
*/

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

    tCoste kilometros = 0;
    for(vertice i = 0; i < cantidad.size(); ++i)
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