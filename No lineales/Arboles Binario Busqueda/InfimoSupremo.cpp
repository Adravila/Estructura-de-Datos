#include "Cabeceras/abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

//Devuelve el mínimo, A es un árbol no vacío
template <typename T>
int minimo(const Abb<T> &A)
{
	if (A.izqdo().vacio())
    {
		return A.elemento();
    }
	else
    {
		minimo(A.izqdo());
    }
}

//Devuelve el máximo, A es un árbol no vacío
template <typename T>
int maximo(const Abb<T> &A)
{
	if (A.drcho().vacio())
    {
		return A.elemento();
    }
	else
    {
		return maximo(A.drcho());
    }
}

template <typename T>
int infimo(const Abb<T> &A, int x)
{
    // Si el árbol está vacío
    if(A.vacio())
    {
        return 0;
    }
    // elemento IGUAL
	if (A.elemento() == x)
    {
		return A.elemento();
    }
    // elemento MENOR
	else if (A.elemento() < x)
	{
		if (A.drcho().vacio() || (minimo(A.drcho()) > x))
        {
			return minimo(A);
        }
		else
        {
			return infimo(A.drcho(), x);
        }
	}
    // elemento MAYOR
	else
	{
		if (A.izqdo().vacio() || (minimo(A.izqdo()) > x))
        {
  			return A.elemento();          
        }
		else
        {
			return infimo(A.izqdo(), x);
        }
	}
}

template <typename T>
int supremo(const Abb<T> &A, int x)
{
    // Si el árbol está vacío
    if(A.vacio())
    {
        return 0;
    }
    // elemento IGUAL
	if (A.elemento() == x)
    {
		return A.elemento();
    }
    // elemento MENOR
	else if (A.elemento() < x)
	{
		if (A.drcho().vacio() || (maximo(A.drcho()) < x))
        {
			return maximo(A);
        }
		else
        {
			return supremo(A.drcho(), x);
        }
	}
    // elemento MAYOR
	else
	{
		if (A.izqdo().vacio() || (maximo(A.izqdo()) < x))
        {
			return A.elemento();
        }
		else
        {
			return supremo(A.izqdo(), x);
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
    Abb<int> A;
    A.insertar(83);
    A.insertar(25);
    A.insertar(80);
    A.insertar(30);
    A.insertar(15);
    A.insertar(24);
    A.insertar(60);
    A.insertar(70);
    A.insertar(18);
    A.insertar(3);
    A.insertar(99);
    A.insertar(161);
    A.insertar(130);
    A.insertar(131);

    std::cout << "Imprimir árbol: ";
    ImprimirArbolBusq(A);
    std::cout << std::endl;
	cout << "Supremo del árbol: " << supremo(A,87) << endl;
	cout << "Ínfimo del árbol: " << infimo(A,87) << endl;
}