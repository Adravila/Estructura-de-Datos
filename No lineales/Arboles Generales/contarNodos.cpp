#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"

using namespace std;

/**
 * Contar los nodos que hay en todo el árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int contarNodosRec(const Agen<T> &A, typename Agen<T>::nodo n)
{
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		// Declaración de variables
		int cont;
		typename Agen<T>::nodo hijo;
		// Definición de variables
		cont = 0;
		hijo = A.hijoIzqdo(n);

		while (hijo != Agen<T>::NODO_NULO)
		{
			cont += contarNodosRec(A, hijo);
			hijo = A.hermDrcho(hijo);
		}
		return 1 + cont;
	}
}

template <typename T>
int contarNodos(const Agen<T> &A)
{
	return contarNodosRec(A, A.raiz());
}

int main()
{
	Agen<char> A, B, C, D;
	cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
	ifstream fa("Data/agen.dat"); // abrir fichero de entrada
	rellenarAgen(fa, A);		  // desde fichero
	fa.close();
	cout << "\n*** Mostrar árbol general A ***\n";
	imprimirAgen(A); // en std::cout
	cout << "\nNúmero de nodos del árbol A 'agen': " << contarNodos(A) << endl;

	cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
	ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
	rellenarAgen(fb, B);			  // desde fichero
	fb.close();
	cout << "\n*** Mostrar árbol general B ***\n";
	imprimirAgen(B); // en std::cout
	cout << "\nNúmero de nodos del árbol B 'agen-ter': " << contarNodos(B) << endl;

	cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
	ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
	rellenarAgen(fc, C);			  // desde fichero
	fc.close();
	cout << "\n*** Mostrar árbol general C ***\n";
	imprimirAgen(C); // en std::cout
	cout << "\nNúmero de nodos del árbol C 'agen-cua': " << contarNodos(C) << endl;

	cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
	ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
	rellenarAgen(fd, D);			  // desde fichero
	fd.close();
	cout << "\n*** Mostrar árbol general D ***\n";
	imprimirAgen(D); // en std::cout
	cout << "\nNúmero de nodos del árbol D 'agen-abu': " << contarNodos(D) << endl;
}
