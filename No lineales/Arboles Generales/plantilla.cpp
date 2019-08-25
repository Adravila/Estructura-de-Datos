#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

template <typename T>
bool esArbolnarioRec(typename Agen<T>::nodo n, const Agen<T>& A, int grado)
{
	if (n == Agen<T>::NODO_NULO)
	{
		return false;
	}
	else
	{
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		int hijos = 0;
		while(hijo != Agen<T>::NODO_NULO)
		{
			++hijos;
			if (!esArbolnarioRec(hijo, A, grado))
				return false;
			hijo = A.hermDrcho(hijo);
		}
		return grado == hijos || hijos == 0;
	}
}

template <typename T>
bool esArbolnario(const Agen<T>& A, int grado)
{
	return esArbolnarioRec(A.raiz(), A, grado);
}

int main()
{
    Agen<char> A, B, C, D;
    cout << "\n*** Lectura de árbol general A de agen.dat ***\n";
    ifstream fa("Data/agen.dat"); // abrir fichero de entrada
    rellenarAgen(fa, A);          // desde fichero
    fa.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A); // en std::cout
    cout << "Este árbol es un árbol estrictamente ternario: ";
    if (esArbolnario(A, 3))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);              // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "Este árbol es un árbol estrictamente ternario: ";
    if (esArbolnario(B, 3))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);              // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "Este árbol es un árbol estrictamente cuaternario: ";
    if (esArbolnario(C, 4))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);              // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "Este árbol es un árbol estrictamente binario: ";
    if (esArbolnario(D, 2))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }
}