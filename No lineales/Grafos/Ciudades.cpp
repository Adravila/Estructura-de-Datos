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

/*
    El archipiélago Grecolandia (Zuelandia) está formado por dos islas: Fobos y Deimos que tienen
    N1 y N2 ciudades de las cuales C1 y C2 son costeras (C1 <= N1 y C2 <= N2)

    También se dispone de los grafos Fobos y Deimos representados mediante sendas matrices de adyacencia.
    Si el valor es 'true' entonces hay carretera y el coste de ella correspondería con la distancia Euclidea
    existente entre las ciudades origen y destino de la misma.

    Nos planteamos construir un puente entre todas las posibles (ciudades costeras también) para conectar
    el archipiélago. Los fondos vienen de fondos FEDER por lo que son irrelevantes. Sin embargo, el coste
    directo de viajar por el puente, igual que en el caso de una carretera coincidirá con su longitud 
    (distancia Euclidea entre las poblaciones origen y destino de dicho puente)

    De cara a poder decidir qué puente construir es importante indicar que se van a realizar el mismo
    número de viajes entre cualesquiera de 2 ciudades del archipiélago, por lo que no existen ciudades
    más importantes que otras ni rutas más importantes que otras. Todos los posibles viajes origen-destino
    en el archipiélago son, por tanto, de igual importancia y en consecuencia, debemos escoger el puente
    que minimice el coste mínimo de viajar entre las ciudades del archipiélago, dado lo irrelevante del
    coste de construcción.

    En estas condiciones implementa una función que devuelva el puente a construir dados:
        1. Matriz de adyacencia de Fobos
        2. Matriz de adyacencia de Deimos
        3. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas
        4. Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas
        5. Lista de ciudades costeras de Fobos
        6. Lista de ciudades costeras de Deimos
*/

using namespace std;
typedef typename GrafoP<size_t>::vertice vertice;

struct Ciudad
{
    Ciudad(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    int x, y;
};

float DistanciaEuclidea(const Ciudad &a, const Ciudad &b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

template <typename tCoste>
tCoste SumaMatriz(const matriz<tCoste> &M)
{
    tCoste suma = 0;
    for (int i = 0; i < M.dimension(); ++i)
    {
        for (int j = 0; j < M.dimension(); ++j)
        {
            suma += M[i][j];
        }
    }
    return suma;
}

void Puente(Grafo Fobos, Grafo Deimos, vector<bool> CosterasFobos, vector<bool> CosterasDeimos,
            vector<Ciudad> ciudadesFobos, vector<Ciudad> ciudadDeimos)
{
    //Matriz con los costes de Fobos y Deimos
    GrafoP<float> FD(Fobos.numVert() + Deimos.numVert());

    for (vertice i = 0; i < FD.numVert(); ++i)
    {
        for (vertice j = 0; j < FD.numVert(); ++j)
        {
            if(i == j)
            {
                FD[i][j] = 0;
            }
            else if (Fobos[i % Deimos.numVert()][j % Deimos.numVert()] && i < Fobos.numVert() && j < Fobos.numVert())
            {
                FD[i][j] = DistanciaEuclidea(ciudadesFobos[i], ciudadesFobos[j]);
                cout << "FD[" << i << "][" << j << "]: " << FD[i][j] << endl;
            }
            else if (Deimos[i % Deimos.numVert()][j % Deimos.numVert()] && i >= Deimos.numVert() && j >= Deimos.numVert())
            {
                FD[i][j] = DistanciaEuclidea(ciudadDeimos[i - Deimos.numVert()], ciudadDeimos[j - Deimos.numVert()]);
                                cout << "FD[" << i << "][" << j << "]: " << FD[i][j] << endl;
            }
            else
            {
                FD[i][j] = GrafoP<float>::INFINITO;
            }
            
        }
    }

    //Se van añadiendo los puentes, y se calcula la suma de la matriz con //Floyd
    matriz<vertice> P(FD.numVert());
    matriz<float> F(FD.numVert());
    int posF = -1, posD = -1;
    float minimo = GrafoP<float>::INFINITO;

    for (vertice i = 0; i < Fobos.numVert(); ++i)
    {
        if (CosterasFobos[i])
        {
            for (int j = 0; j < Deimos.numVert(); ++j)
            {
                if (CosterasDeimos[i])
                {
                    GrafoP<float> TempG = FD;
                    float costePuente = DistanciaEuclidea(ciudadesFobos[i], ciudadDeimos[j]);
                    cout << costePuente << " i " << i << endl;
                    TempG[i][j + Fobos.numVert()] = costePuente;
                    TempG[j + Fobos.numVert()][i] = costePuente;
                    F = Floyd(TempG, P);
                    float s = SumaMatriz(F);
                    if (s < minimo)
                    {
                        minimo = s;
                        posF = i;
                        posD = j;
                    }
                }
            }
        }
    }

    cout << "En Fobos el puente se construye en " << posF << "." << endl;
    cout << "En Deimos el puente se construye en " << posD << "." << endl;
    cout << "El coste del puente es " << minimo << "." << endl;
}

int main()
{
    int N1 = 4, N2 = 4;
    Grafo g1(N1), g2(N2);
    g1[0][1] = true;
    g1[1][0] = true;
    g1[1][2] = true;
    g1[2][1] = true;
    g1[2][3] = true;
    g1[3][2] = true;
    g2[0][1] = true;
    g2[0][2] = true;
    g2[1][0] = true;
    g2[1][2] = true;
    g2[1][3] = true;
    g2[2][0] = true;
    g2[2][1] = true;
    g2[2][3] = true;
    g2[3][1] = true;
    g2[3][2] = true;

    vector<bool> CosterasFobos(N1, false), CosterasDeimos(N2, false);

    CosterasFobos[0] = true;
    CosterasFobos[3] = true;
    CosterasDeimos[1] = true;
    CosterasDeimos[0] = true;
    CosterasDeimos[2] = true;

    Ciudad c1(0, 4), c2(3, 7), c3(3, 5), c4(3, 3);
    Ciudad c5(0,3), c6(1, 0), c7(1, 3), c8(2, 0);

    vector<Ciudad> ciudadesFobos(N1), ciudadesDeimos(N2);
    ciudadesFobos[0] = c1;
    ciudadesFobos[1] = c2;
    ciudadesFobos[2] = c3;
    ciudadesFobos[3] = c4;
    ciudadesDeimos[0] = c5;
    ciudadesDeimos[1] = c6;
    ciudadesDeimos[2] = c7;
    ciudadesDeimos[3] = c8;

    Puente(g1, g2, CosterasFobos, CosterasDeimos, ciudadesFobos, ciudadesDeimos);
}