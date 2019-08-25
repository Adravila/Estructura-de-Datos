#include "Cabeceras/abb.hpp"
#include "Cabeceras/Pila_enla.h"
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
void eliminarEltos(const T& e, Abb<T>& A)
{
    Abb<T> B = A.buscar(e);
    Pila<T> P;

    // Buscar elementos del árbol a eliminar
    // Se añade los elementos a eliminar dentro de una pila
    while(!B.vacio())
    {
        T elto = B.elemento();
        P.push(elto);
        B.eliminar(elto);
    }
    // Procesar la eliminación
    while(!P.vacia())
    {
        A.eliminar(P.tope());
        P.pop();
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
    eliminarEltos(12, A);

    std::cout << "Imprimir árbol: ";
    ImprimirArbolBusq(A);
    std::cout << std::endl;

}