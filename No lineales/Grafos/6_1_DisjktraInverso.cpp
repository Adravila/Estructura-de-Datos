#include <algorithm> //sort
#include <vector>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"

using namespace std;

template <typename tCoste>
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice destino,
                           vector<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false);                  // Conjunto de vértices vacío.
   vector<tCoste> D;                          // Costes mínimos hasta destino.
   
   // Iniciar D y P con caminos directos hasta el vértice destino.
   D = vector<tCoste> (n, GrafoP<tCoste>::INFINITO);
   for(int i = 0; i < n; ++i)
   {
         D[i] = G[i][destino];
   }
   D[destino] = 0;                             // Coste destino-destino es 0.
   P = vector<vertice>(n, destino);
   
   // Calcular caminos de coste mínimo desde cada vértice.
   S[destino] = true;                          // Incluir vértice destino en S.
   
   for (size_t i = 1; i <= n; i++) {
      // Seleccionar vértice w no incluido en S
      // con menor coste hasta destino.
      
      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for (v = 0; v < n; v++) {
          if (!S[v] && D[v] <= costeMin) {
             costeMin = D[v];
             w = v;
          }
      }
      S[w] = true;                          // Incluir vértice w en S.
      
      // Recalcular coste hasta cada v no incluido en S a través de w.
      for (v = 0; v < n; v++) {
          tCoste wvD;
          if(D[v] != GrafoP<tCoste>::INFINITO) wvD = suma(G[v][w], D[w]);
          else wvD = G[v][destino];
          
          if (wvD < D[v]) {
             D[v] = wvD;
             P[v] = (D[w] != GrafoP<tCoste>::INFINITO) ? w : v;
          }
      }
   }
   return D;
}


int main()
{
    GrafoP<int> G("Data/grafo-2.txt");
    std::cout << G;

    vector<GrafoP<int>::vertice> dij;
    vector<GrafoP<int>::vertice> dijInv;
    std::cout << "\nResultado Dijkstra: ";
    std::cout << Dijkstra(G,0,dij);
    std::cout << "\nResultado Dijkstra inverso: ";
    std::cout << DijkstraInv(G,4,dijInv) << std::endl;
}
