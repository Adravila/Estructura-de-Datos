#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"

using namespace std;


/**
 * Contar los nodos que tengan un solo hijo de todo el árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
int contarUnSolosHijoRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int nNodos = 0;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		n = A.hijoIzqdo(n);
		// Comprobamos si el hijo existe y no tiene un hermano derecho
		if (n != Agen<T>::NODO_NULO)
		{
			typename Agen<T>::nodo hdrcho;
			hdrcho = A.hermDrcho(n);
			if (hdrcho == Agen<T>::NODO_NULO)
			{
				++nNodos;
			}
		}
		// Fin de la comprobación

		while (n != Agen<T>::NODO_NULO)
		{
			nNodos += contarUnSolosHijoRec(n, A);
			n = A.hermDrcho(n);
		}
		return nNodos;
	}
}

template <typename T>
int contarUnSolosHijo(const Agen<T> &A)
{
	return contarUnSolosHijoRec(A.raiz(), A);
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
	cout << "\nNúmero de nodos que tengan un solo hijo del árbol A 'agen': " << contarUnSolosHijo(A) << endl;

	cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
	ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
	rellenarAgen(fb, B);	 // desde fichero
	fb.close();
	cout << "\n*** Mostrar árbol general B ***\n";
	imprimirAgen(B); // en std::cout
	cout << "\nNúmero de nodos que tengan un solo hijo del árbol B 'agen-ter': " << contarUnSolosHijo(B) << endl;

	cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
	ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
	rellenarAgen(fc, C);	 // desde fichero
	fc.close();
	cout << "\n*** Mostrar árbol general C ***\n";
	imprimirAgen(C); // en std::cout
	cout << "\nNúmero de nodos que tengan un solo hijo del árbol C 'agen-cua': " << contarUnSolosHijo(C) << endl;

	cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
	ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
	rellenarAgen(fd, D);	 // desde fichero
	fd.close();
	cout << "\n*** Mostrar árbol general D ***\n";
	imprimirAgen(D); // en std::cout
	cout << "\nNúmero de nodos que tengan un solo hijo del árbol D 'agen-abu': " << contarUnSolosHijo(D) << endl;
}