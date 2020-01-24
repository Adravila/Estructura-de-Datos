#include <cmath>
#include <iostream>
#include "Cabeceras/Grafo/grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafoPMC.h"
#include "Cabeceras/Grafo/alg_grafo_E-S.h"
#include "Cabeceras/Grafo/particion.h"
#include "Cabeceras/Grafo/particion.cpp"
#include "Cabeceras/Grafo/grafoMA.h"

struct ciudad
{
    double x, y;
    ciudad(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

double distancia(unsigned i, unsigned j, const std::vector<ciudad> &ciudades)
{
    const ciudad &a = ciudades[i];
    const ciudad &b = ciudades[j];
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

std::pair<Particion, matriz<double>> distribucionTombuctiana(const std::vector<ciudad> &ciudades, const Grafo &carreteras)
{
    const unsigned n = carreteras.numVert();
    Particion p(n);
    GrafoP<double> costes(n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (carreteras[i][j] && p.encontrar(i) != p.encontrar(j))
            {
                p.unir(p.encontrar(i), p.encontrar(j));
            }
            if (carreteras[i][j])
            {
                costes[i][j] = distancia(i, j, ciudades);
            }
        }
    }

    int cont = 0;
    for(int i = 0; i < n; ++i)
    {
        if(p.encontrar(i) == i)
        {
            std::cout << "\nIsla " << cont << ": "; 
            ++cont;
        }
            std::cout << i << " ";
    }
    std::cout << "\n";

    matriz<GrafoP<double>::vertice> P;
    return std::make_pair(p, Floyd(costes, P));
}

int main()
{
    std::vector<ciudad> ciudades(9);
    ciudades[0] = (ciudad{1, 0}); // A
    ciudades[1] = (ciudad{2, 1}); // B
    ciudades[2] = (ciudad{3, 0}); // C
    ciudades[3] = (ciudad{2, 4}); // D
    ciudades[4] = (ciudad{3, 4}); // E
    ciudades[5] = (ciudad{3, 7}); // F
    ciudades[6] = (ciudad{4, 9}); // G
    ciudades[7] = (ciudad{2, 8}); // H
    ciudades[8] = (ciudad{0, 7}); // I

    Grafo carreteras{9};

    // Isla 1
    carreteras[0][1] = carreteras[1][0] = true;
    carreteras[0][2] = carreteras[2][0] = true;
    carreteras[1][2] = carreteras[2][1] = true;
    carreteras[1][3] = carreteras[3][1] = true;
    carreteras[1][4] = carreteras[4][1] = true;
    carreteras[2][3] = carreteras[3][2] = true;

    // Isla 2
    carreteras[6][5] = carreteras[5][6] = true;
    carreteras[7][5] = carreteras[5][7] = true;

    Particion P{9};
    matriz<double> mapa{9};

    mapa = distribucionTombuctiana(ciudades, carreteras).second;

    std::cout << mapa;
}