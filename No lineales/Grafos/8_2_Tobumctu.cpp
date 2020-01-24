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

struct lineaAerea
{
    ciudad c1, c2;
    lineaAerea(const ciudad& a, const ciudad& b) : c1(a), c2(b) {}
};

double distancia(unsigned i, unsigned j, const ciudad &a, const ciudad &b)
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

std::vector<lineaAerea> distribucionTombuctiana(const std::vector<ciudad> &ciudades, const Grafo &carreteras)
{
    const unsigned n = carreteras.numVert();
    Particion p(n);
    GrafoP<double> costes(n);
    int nIslas = n;
    vector<lineaAerea> lineas;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (carreteras[i][j] && p.encontrar(i) != p.encontrar(j))
            {
                p.unir(p.encontrar(i), p.encontrar(j));
                nIslas--;
            }
        }
    }

    for (int k = 0; k < nIslas - 1; ++k)
    {
        ciudad c1, c2;
        int dist = 0;
        int min = 999;
        int ri_min, rj_min;

        // Buscar la distancia minima entre dos islas
        for (int i = 0; i < n; ++i)
        {
            int rep_i = p.encontrar(i);
            for (int j = 0; j < n; ++j)
            {
                int rep_j = p.encontrar(j);
                // Si son ciudades de distintas islas
                if (rep_i != rep_j)
                {
                    dist = distancia(i, j, ciudades[i], ciudades[j]);
                    if (dist < min)
                    {
                        min = dist;
                        c1 = ciudades[i];
                        c2 = ciudades[j];
                        ri_min = rep_i;
                        rj_min = rep_j;
                    }
                }
            }
        }
        lineas.push_back(lineaAerea(c1,c2));
        p.unir(ri_min, rj_min);
    }
    return lineas;
}

int main()
{
    std::vector<ciudad> ciudades(10);
    ciudades[0] = (ciudad{1, 1});  // A
    ciudades[1] = (ciudad{3, 3});  // B
    ciudades[2] = (ciudad{1, 5});  // C
    ciudades[3] = (ciudad{3, 7});  // D
    ciudades[4] = (ciudad{4, 9});  // E
    ciudades[5] = (ciudad{2, 10}); // F
    ciudades[6] = (ciudad{1, 13}); // G
    ciudades[7] = (ciudad{3, 13}); // H
    ciudades[8] = (ciudad{3, 15}); // I
    ciudades[9] = (ciudad{1, 15}); // J

    Grafo carreteras{10};

    // Isla 1
    carreteras[0][1] = carreteras[1][0] = true;
    carreteras[0][2] = carreteras[2][0] = true;
    carreteras[1][0] = carreteras[0][1] = true;
    carreteras[1][2] = carreteras[2][1] = true;

    // Isla 2
    carreteras[3][4] = carreteras[4][3] = true;
    carreteras[4][5] = carreteras[5][4] = true;

    // Isla 3
    carreteras[6][7] = carreteras[7][6] = true;
    carreteras[6][8] = carreteras[8][6] = true;
    carreteras[6][9] = carreteras[9][6] = true;
    carreteras[7][8] = carreteras[8][7] = true;
    carreteras[7][9] = carreteras[9][7] = true;
    carreteras[8][9] = carreteras[9][8] = true;

    Particion P{10};
    matriz<double> mapa{10};

    std::vector<lineaAerea> V = distribucionTombuctiana(ciudades, carreteras);

    for(vector<lineaAerea>::iterator it = V.begin(); it != V.end(); ++it)
    {
        std::cout << "(" << (*it).c1.x << ", " << (*it).c1.y << ") <=> (" << (*it).c2.x << ", " << (*it).c1.y << ")\n";
    }
}