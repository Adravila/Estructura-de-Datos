#include "Cabeceras/abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

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

template <typename T>
void ImprimirAbin(typename Abin<T>::nodo n, Abin<T> A)
{
    if (n != Abin<T>::NODO_NULO)
    {
        std::cout << A.elemento(n) << " ";
        ImprimirAbin(A.hijoIzqdoB(n), A);
        ImprimirAbin(A.hijoDrchoB(n), A);
    }
}

int main()
{
    Abb<int> A;
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

  // Ejercicio 2: Crear Abin a partir del ABB
    Abin<int> B = (Abin<int>)A;

    std::cout << "Árbol binario resultante: ";
    ImprimirAbin(B.raizB(), B);
    std::cout << std::endl;
}