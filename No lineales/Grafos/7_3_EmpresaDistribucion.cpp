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
 * Problema 3
- En este problema se utilizará Dijkstra dado de que se inicia desde UN ORIGEN,
- Las subveciones (de gastos mínimos) se almacenan en un vector
- El coste mínimo debe se proporcional
- Empezar desde el más barato hasta que se acabe la cantidad
**/

template <typename tCoste>
vector<tCoste> distribuirProductos(const GrafoP<tCoste> &G, size_t cantProd,
                                   const typename GrafoP<tCoste>::vertice centrDistrib, vector<size_t> &capCiud,
                                   const vector<double> &subvencion, tCoste &minCosteTotal)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    vector<tCoste> cantAlmaCiu(G.numVert(), 0); //un vector que mostrara cuantos productos hemos almacenado en cada ciudad
    vector<tCoste> vCostesMin(G.numVert(), 0);  //un vector que contendrá los costes min para ir desde el almacen principal a todas las ciudades
    vector<vertice> vCaminMin(G.numVert(), 0);  //vector P de dijkstra

    tCoste costeMin; //el coste min del viaje en cada iteracion
    vertice j;       //en esta variable guardaremos el vertice hacia el que sale mas barato enviar los productos en cada iteracion

    vCostesMin = Dijkstra(G, centrDistrib, vCaminMin); //calculamos el coste minimo para transportar una unidad desde centro distr a cualquier ciudad

    //aplicamos la subvencion a los costes min
    for (vertice i = 0; i < G.numVert(); i++)
        vCostesMin[i] -= vCostesMin[i] * subvencion[i];

    while (cantProd > 0) //damos viajes hasta que nos quedemos sin productos
    {
        costeMin = GrafoP<tCoste>::INFINITO; //reiniciamos el coste min para buscar la siguiente ciudad que nos salga mas barato enviar

        for (vertice i = 0; i < G.numVert(); i++) //iteramos buscando la ciudad que nos proporciona un coste mas barato y que tenga hueco y la almacenamos en j
            if (vCostesMin[i] < costeMin && cantAlmaCiu[i] != capCiud[i])
            {
                j = i;
                costeMin = vCostesMin[i];
            }

        if (cantProd > capCiud[j] - cantAlmaCiu[j]) //si la cantidad a repartir es mayor que lo que cabe en el almacen(lo que cabe-lo que hay)
        {
            cantProd -= capCiud[j] - cantAlmaCiu[j];                      //llenamos el almacen y le restamos el num de prod a cantProd
            minCosteTotal += vCostesMin[j] * capCiud[j] - cantAlmaCiu[j]; //al numero de prod que hemos guardado lo multiplicamos por el precio de envio unitario y se lo añadimos al total
            cantAlmaCiu[j] = capCiud[j];                                  //llenamos el almacen de esa ciudad
        }
        else //si el almacen posee mas capacidad de lo que tenemos
        {
            cantAlmaCiu[j] = cantProd;
            minCosteTotal += vCostesMin[j] * cantProd;
            cantProd -= cantProd; //ponemos el el stock disponible a 0 ya que vamos a vaciarlo en el almacen j
        }
    }

    return cantAlmaCiu;
}

template <typename tCoste>
tCoste DistribuirProducto(GrafoP<tCoste> G, typename GrafoP<tCoste>::vertice origen,
                          size_t cant,
                          const vector<double> &subvenciones, const vector<size_t> &capacidades, vector<size_t> &envio)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    size_t n = G.numVert();
    //Primero hay que calcular los costes con la subvencion. Se hace en G (para eso se recibe por copia)
    for (vertice i = 0; i < n; i++)
    {
        for (vertice j = 0; j < n; j++)
        {
            if (G[i][j] != GrafoP<tCoste>::INFINITO)
                G[i][j] = G[i][j] *
                          (1 - subvenciones[j]);
        }
    }
    cout << "Grafo tras subvenciones: " << G << endl;
    //Ahora determinaremos los costes mínimos desde origen hasta las otras ciudades => Dijkstra
    vector<vertice> verticesDij(n);
    vector<tCoste> vecDij = Dijkstra(G, origen, verticesDij);
    cout << "VEC DIJ: " << endl;
    for (vertice i = 0; i < n; i++)
    {
        cout << " " << vecDij[i];
    }
    cout << endl;
    //A continuación, se determinan cuantas unidades enviar a cada ciudad:
    tCoste acum = 0;
    while (cant > 0)
    {
        tCoste minimo = GrafoP<tCoste>::INFINITO;
        vertice v;
        for (vertice i = 0; i < n; i++)
        {
            if (i != origen && envio[i] == 0 && vecDij[i] < minimo)
            {
                minimo = i;
                v = i;
            }
        }
        //Una vez seleccionada la ciudad, se le envían todos los que se puedan
        if (capacidades[v] > cant)
        {
            envio[v] = cant;
            acum += (cant * vecDij[v]);
            cant = 0;
        }
        else
        {
            envio[v] = capacidades[v];
            acum += (cant * capacidades[v]);
            cant -= capacidades[v];
        }
    }
    return acum;
}

int main()
{
    size_t N, cantProd;
    double minCosteTotal;
    typename GrafoP<double>::vertice origen;
    vector<size_t> envio(N,0); 
    N = 5;
    cantProd = 75;
    minCosteTotal = 0;
    origen = 3;

    vector<size_t> capCiud = {50, 50, 25, 0, 50, 30, 40, 30};

    vector<double> subvencion = {0.05, 0.5, 0.5, 0, 0.25, 0.2, 0.2, 0.4};

    GrafoP<double> mapaDistribucion("ejercicio_4.txt");
    GrafoP<double> mapaDistribucionCop(mapaDistribucion);

    cout << "matriz de costes directos ciudades: \n"
         << mapaDistribucion << endl;

    cout << "cantidades a almacenar en cada ciudad:" << endl;
    cout << DistribuirProducto(mapaDistribucion, origen, cantProd, subvencion, capCiud, envio) << endl;
    cout << "coste min total de la operacion:" << endl;
    cout << minCosteTotal << endl;
}