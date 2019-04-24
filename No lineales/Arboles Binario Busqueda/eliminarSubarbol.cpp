#include "Cabeceras/abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Ejercicio 1
template <typename T>
void EliminarSubarbol(const T &x, Abb<T> &A)
{
    while (!A.buscar(x).vacio())
    {
        if (!A.buscar(x).izqdo().vacio())
        {
            A.eliminar(A.buscar(x).izqdo().elemento());
        }
        else if (!A.buscar(x).drcho().vacio())
        {
            A.eliminar(A.buscar(x).drcho().elemento());
        }
        else
        {
            A.eliminar(A.buscar(x).elemento());
        }
    }
}

template <typename T>
void ImprimirArbolBusq(const Abb<T> A)
{
    if (!A.vacio())
    {
        std::cout << A.elemento() << " ";
        ImprimirArbolBusq(A.izqdo());
        ImprimirArbolBusq(A.drcho());
    }
}

int main()
{
    Abb<int> A, B;
    A.insertar(7);
    A.insertar(5);
    A.insertar(12);
    A.insertar(9);
    A.insertar(17);
    A.insertar(8);
    A.insertar(11);
    A.insertar(10);

    std::cout << "Imprimir árbol: ";
    ImprimirArbolBusq(A);
    std::cout << std::endl;

    // Ejercicio 1: Eliminar subárbol
    EliminarSubarbol(9, A);
    std::cout << "Árbol de búsqueda resultante: ";
    ImprimirArbolBusq(A);
    std::cout << std::endl;
}