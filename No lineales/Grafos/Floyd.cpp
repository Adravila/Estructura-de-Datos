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

int main()
{
    GrafoP<int> G("Data/prueba.txt");
    matriz<GrafoP<int>::vertice> P;
    matriz<int> m;
    m = Floyd(G, P);
    cout << "Imprimir resultado Floyd:\n" << m << endl;
    cout << "Imprimir matriz de caminos:\n" << P << endl;
}