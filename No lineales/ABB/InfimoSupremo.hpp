#include "Cabeceras/abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

//Devuelve el mínimo, A es un árbol no vacío
template <typename T>
T minimo(const Abb<T> &A)
{
	if (A.izqdo().vacio())
		return A.elemento();
	else
		minimo(A.izqdo());
}

//Devuelve el máximo, A es un árbol no vacío
template <typename T>
T maximo(const Abb<T> &A)
{
	if (A.drcho().vacio())
		return A.elemento();
	else
		maximo(A.drcho());
}

template <typename T>
int infimo(const Abb<T> &A, int x)
{
	if (A.elemento() == x) //elemento IGUAL
		return A.elemento();
	else if (A.elemento() < x)
	{ //elemento MENOR
		if (A.drcho().vacio() || (minimo(A.drcho()) > x))
			return A.elemento();
		else
			return infimo(A.drcho(), x);
	}
	else
	{ //elemento MAYOR
		if (A.izqdo().vacio() || (minimo(A.izqdo()) > x))
			return minimo(A);
		else
			return infimo(A.izqdo(), x);
	}
}

template <typename T>
int supremo(const Abb<T> &A, int x)
{
	if (A.elemento() == x) //elemento IGUAL
		return A.elemento();
	else if (A.elemento() < x)
	{ //elemento MENOR
		if (A.drcho().vacio() || (minimo(A.drcho()) < x))
			return maximo(A);
		else
			return supremo(A.drcho(), x);
	}
	else
	{ //elemento MAYOR
		if (A.izqdo().vacio() || (maximo(A.izqdo()) < x))
			return A.elemento();
		else
			return supremo(A.izqdo(), x);
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
	cout << "Supremo del árbol: " << supremo(A,4);
	cout << "Ínfimo del árbol: " << infimo(A,4);
}