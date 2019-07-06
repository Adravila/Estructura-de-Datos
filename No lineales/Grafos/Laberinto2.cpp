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
calcularCamino(GrafoP<size_t> &G, const Lista<casilla> &L, const casilla entrada, const casilla salida, size_t &len)
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
            if (esAdyacente(i, j))
                G[i][j] = 1;
            else if (i == j)
                G[i][j] = 0;
            else
                G[i][j] = GrafoP<size_t>::INFINITO;
        }
    }

    Lista<casilla>::posicion p = L.primera();
    vertice v;

    while(p != L.fin())
    {
        v = casillaToVertice(L.elemento(p));
        for(vertice i = 0; i < G.numVert(); i++)
            G[v][i] = G[i][v] = GrafoP<size_t>::INFINITO;
        p = L.siguiente(p);
    }

    vCosteMin = Dijkstra(G, casillaToVertice(entrada), vCaminMin);

    camin = camino<size_t>(casillaToVertice(entrada), casillaToVertice(salida), vCaminMin);

    len = vCosteMin[casillaToVertice(salida)];

    return camin;
}

int main()
{
    N = 7; // va a ser una laberinto de 6 x 6 casillas
    Lista<casilla> lPiedras;           //matriz bool de piedras
    GrafoP<size_t> laberinto(N * N); //van a hacer n*n nodos
    GrafoP<size_t> laberintoCopia(laberinto);
    size_t longitud; //longitud del camino mas corto
    //definimos las casillas de entrada y salida
    casilla entrada(0, 0), salida(6, 6);

    //insertamos las piedras en la lista de piedras
    lPiedras.insertar(casilla(0, 6), lPiedras.fin()); // 6
    lPiedras.insertar(casilla(1, 0), lPiedras.fin()); // 7
    lPiedras.insertar(casilla(1, 1), lPiedras.fin()); // 8
    lPiedras.insertar(casilla(1, 3), lPiedras.fin()); // 10
    lPiedras.insertar(casilla(1, 4), lPiedras.fin()); // 11
    lPiedras.insertar(casilla(1, 5), lPiedras.fin()); // 12
    lPiedras.insertar(casilla(2, 3), lPiedras.fin()); // 17
    lPiedras.insertar(casilla(3, 5), lPiedras.fin()); // 26
    lPiedras.insertar(casilla(4, 3), lPiedras.fin()); // 31
    lPiedras.insertar(casilla(4, 4), lPiedras.fin()); // 31
    lPiedras.insertar(casilla(4, 5), lPiedras.fin()); // 33
    lPiedras.insertar(casilla(5, 1), lPiedras.fin()); // 36
    lPiedras.insertar(casilla(5, 2), lPiedras.fin()); // 37
    lPiedras.insertar(casilla(5, 3), lPiedras.fin()); // 38
    lPiedras.insertar(casilla(6, 0), lPiedras.fin()); // 42


    //probamos el programa
    cout << "el camino para resolver el laberinto es : ";
    Lista<size_t> list = calcularCamino(laberintoCopia, lPiedras, entrada, salida, longitud);
    Lista<size_t>::posicion p = list.primera();
    while(p != list.fin())
    {
        cout << list.elemento(p) << " ";
        p = list.siguiente(p);
    }
    cout << "\n longitud del camino mas corto:" << longitud << endl;
}