#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

/**
 * En este ejercicio vamos a contar cuantos nietos y abuelos son a la vez
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

using namespace std;

template <typename T>
bool esAbuelo(typename Agen<T>::nodo n, const Agen<T> &A, int prof)
{
    typename Agen<T>::nodo hijo;
    if (n == Agen<T>::NODO_NULO)
    {
        return false;
    }
    else
    {
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            if (esAbuelo(hijo, A, prof + 1))
            {
                return true;
            }
            hijo = A.hermDrcho(hijo);
        }
        return (prof >= 2);
    }
}

template <typename T>
bool esNieto(typename Agen<T>::nodo n, const Agen<T> &A)
{
    int cont = 0;
    while (n != A.raiz())
    {
        ++cont;
        n = A.padre(n);
    }
    return cont == 2;
}

template <typename T>
int contarEsNietoAbueloRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if (esAbuelo(n, A, 0) && esNieto(n,A))
        {
            return 1 + contarEsNietoAbueloRec(A.hijoIzqdo(n), A) + contarEsNietoAbueloRec(A.hermDrcho(n), A);
        }
        else
        {
            return 0 + contarEsNietoAbueloRec(A.hijoIzqdo(n), A) + contarEsNietoAbueloRec(A.hermDrcho(n), A);
        }
    }
}

template <typename T>
int contarEsNietoAbuelo(const Agen<T> &A)
{
    return contarEsNietoAbueloRec(A.raiz(), A);
}

int main()
{
	Agen<char> A, B, C, D;
	cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
	ifstream fa("Data/agen.dat"); // abrir fichero de entrada
	rellenarAgen(fa, A);	 // desde fichero
	fa.close();
	cout << "\n*** Mostrar árbol general A ***\n";
	imprimirAgen(A); // en std::cout
	cout << "\nCantidad de nodos que son abuelos y nietos en el árbol A 'agen': " << contarEsNietoAbuelo(A) << endl;

	cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
	ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
	rellenarAgen(fb, B);		 // desde fichero
	fb.close();
	cout << "\n*** Mostrar árbol general B ***\n";
	imprimirAgen(B); // en std::cout
	cout << "\nCantidad de nodos que son abuelos y nietos en el árbol B 'agen-ter': " << contarEsNietoAbuelo(B) << endl;

	cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
	ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
	rellenarAgen(fc, C);		 // desde fichero
	fc.close();
	cout << "\n*** Mostrar árbol general C ***\n";
	imprimirAgen(C); // en std::cout
	cout << "\nCantidad de nodos que son abuelos y nietos en el árbol C 'agen-cua': " << contarEsNietoAbuelo(C) << endl;

	cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
	ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
	rellenarAgen(fd, D);		 // desde fichero
	fd.close();
	cout << "\n*** Mostrar árbol general D ***\n";
	imprimirAgen(D); // en std::cout
	cout << "\nCantidad de nodos que son abuelos y nietos en el árbol D 'agen-abu': " << contarEsNietoAbuelo(D) << endl;
}