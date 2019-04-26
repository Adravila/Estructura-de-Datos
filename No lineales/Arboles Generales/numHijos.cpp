#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Contar el número de hijos que tiene un nodo determinado a partir de un árbol
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int numHijosRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
	    // Declaración de variables
	    int nHijos;
	    typename Agen<T>::nodo hijo;
	    // Definición de variables
	    nHijos = 0;
	    hijo = A.hijoIzqdo(n);

	    while (hijo != Agen<T>::NODO_NULO)
	    {
		    ++nHijos;
		    hijo = A.hermDrcho(hijo);
	    }
	    return nHijos;
    }
}

template <typename T>
int numHijos(const Agen<T> &A)
{
    return numHijosRec(A.raiz(),A);
}

int main()
{
	Agen<char> A,B,C,D;
	cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
	ifstream fa("Data/agen.dat"); // abrir fichero de entrada
	rellenarAgen(fa, A);	 // desde fichero
	fa.close();
	cout << "\n*** Mostrar árbol general A ***\n";
	imprimirAgen(A); // en std::cout
	cout << "\nNúmero de hijos de la raíz del árbol A 'agen': " << numHijos(A) << endl;

	cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
	ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
	rellenarAgen(fb, B);	 // desde fichero
	fb.close();
	cout << "\n*** Mostrar árbol general B ***\n";
	imprimirAgen(B); // en std::cout
	cout << "\nNúmero de hijos de la raíz del árbol B 'agen-ter': " << numHijos(B) << endl;

	cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
	ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
	rellenarAgen(fc, C);	 // desde fichero
	fc.close();
	cout << "\n*** Mostrar árbol general C ***\n";
	imprimirAgen(C); // en std::cout
	cout << "\nNúmero de hijos de la raíz del árbol C 'agen-cua': " << numHijos(C) << endl;

	cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
	ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
	rellenarAgen(fd, D);	 // desde fichero
	fd.close();
	cout << "\n*** Mostrar árbol general D ***\n";
	imprimirAgen(D); // en std::cout
	cout << "\nNúmero de hijos de la raíz del árbol D 'agen-abu': " << numHijos(D) << endl;
}
