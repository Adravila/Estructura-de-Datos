#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"

using namespace std;


int main()
{
    /**
     * Se utiliará una matriz de booleanos
     * Floyd para obtener la matriz de costes mínimos de cada vértice desde un origen a un destino
     * En el apartado D se realizará Dijsktra y Dijsktra inverso (Para todo origen -> Capital + Capital -> Para todo destino)
    **/
   
    GrafoP<int> G("Data/grafo-3.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> v;
    std::cout << "\nResultado Diámetro: " << Diametro(G) << endl;
}
