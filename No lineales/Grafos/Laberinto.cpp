#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"
#include "Cabeceras/TAD/Lista_enla.h"
#include <stdlib.h>
#include <cmath>

using namespace std;

size_t N; // va a ser una laberinto de 3 x 3casillas
typedef typename GrafoP<size_t>::vertice vertice;

struct casilla
{
    vertice x;
    vertice y;
    casilla(vertice x_ = 0, vertice y_ = 0) : x(x_), y(y_) {}
    bool operator==(casilla b) { return (this->x == b.x) && (this->y == b.y); }
};

struct pared
{
    casilla uno;
    casilla dos;
    pared(casilla uno_ = casilla(0, 0), casilla dos_ = casilla(0, 0)) : uno(uno_), dos(dos_) {}
    bool operator==(pared b) { return (this->uno == b.uno) && (this->dos == b.dos); }
};

casilla verticeToCasilla(const vertice v)
{
    casilla c;

    c.x = v / N;
    c.y = v % N;

    return c;
}

vertice casillaToVertice(const casilla c)
{
    vertice v;

    v = c.x * N + c.y;

    return v;
}

bool esAdyacente(const vertice a, const vertice b)
{
    casilla uno, dos;

    uno = verticeToCasilla(a);
    dos = verticeToCasilla(b);

    return (abs(int(uno.x) - int(dos.x)) + abs(int(uno.y) - int(dos.y))) == 1;
}

typename GrafoP<size_t>::tCamino 
calcularCamino(GrafoP<size_t> &G, const Lista<pared> &L, const casilla entrada, const casilla salida, size_t &len)
{
    casilla a, b;
    vector<size_t> vCosteMin(G.numVert());
    vector<size_t> vCaminMin(G.numVert());

    typename GrafoP<size_t>::tCamino camin;

    for (vertice i = 0; i < G.numVert(); i++)
    {
        a = verticeToCasilla(i);
        for (vertice j = 0; j < G.numVert(); j++)
        {
            b = verticeToCasilla(j);
            if (esAdyacente(i, j) && L.buscar(pared(a, b)) == L.fin())
                G[i][j] = 1;
            else if (i == j)
                G[i][j] = 0;
            else
                G[i][j] = GrafoP<size_t>::INFINITO;
        }
    }

    vCosteMin = Dijkstra(G, casillaToVertice(entrada), vCaminMin);

    camin = camino<size_t>(casillaToVertice(entrada), casillaToVertice(salida), vCaminMin);

    len = vCosteMin[casillaToVertice(salida)];

    return camin;
}

int main()
{
    N = 3; // va a ser una laberinto de 3 x 3casillas
    Lista<pared> lParedes;           //matriz bool de paredes
    GrafoP<size_t> laberinto(N * N); //van a hacer n*n nodos
    GrafoP<size_t> laberintoCopia(laberinto);
    size_t longitud; //longitud del camino mas corto
    //definimos las casillas de entrada y salida
    casilla entrada(0, 0), salida(2, 2);

    //definimos las paredes
    pared a(casilla(0, 0), casilla(0, 1));
    pared b(casilla(1, 1), casilla(1, 2));
    pared c(casilla(1, 1), casilla(2, 1));

    //insertamos las paredes en la lista de paredes
    lParedes.insertar(a, lParedes.fin());
    lParedes.insertar(b, lParedes.fin());
    lParedes.insertar(c, lParedes.fin());

    //probamos el programa
    cout << "el camino para resolver el laberinto es : ";
    Lista<size_t> list = calcularCamino(laberintoCopia, lParedes, entrada, salida, longitud);
    Lista<size_t>::posicion p = list.primera();
    while(p != list.fin())
    {
        cout << list.elemento(p) << " ";
        p = list.siguiente(p);
    }
    cout << "\n longitud del camino mas corto:" << longitud << endl;
}