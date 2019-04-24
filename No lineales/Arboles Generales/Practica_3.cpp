#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

// BONUS

// Contar número de hijos de un nodo dado

template <typename T>
int numHijos(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int nHijos;
	typename Agen<T>::nodo hijo;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
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

// Contar número de nodos

template <typename T>
int contarNumNodosRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int nNodos = 0;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		++nNodos;
		n = A.hijoIzqdo(n);
		while (n != Agen<T>::NODO_NULO)
		{
			nNodos += contarNumNodosRec(n, A);
			n = A.hermDrcho(n);
		}
		return nNodos;
	}
}

template <typename T>
int contarNumNodos(const Agen<T> &A)
{
	return contarNumNodosRec(A.raiz(), A);
}

// Contar nodos que tengan un solo hijo

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

// EJERCICIO x **************************************************

template <typename T>
int gradoDesequilibriov2Rec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int grado;
	typename Agen<T>::nodo hijo;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		grado = numHijos(n, A);
		hijo = A.hijoIzqdo(n);
		while (hijo != Agen<T>::NODO_NULO)
		{
			grado = abs(max(gradoDesequilibriov2Rec(hijo, A), grado) - min(gradoDesequilibriov2Rec(hijo, A), grado));
			hijo = A.hermDrcho(hijo);
		}
		return grado;
	}
}

template <typename T>
int gradoDesequilibriov2(const Agen<T> &A)
{
	return gradoDesequilibriov2Rec(A.raiz(), A);
}

// EJERCICIO 1 **************************************************

template <typename T>
int gradoArbolRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int grado;
	typename Agen<T>::nodo hijo;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		grado = numHijos(n, A);
		hijo = A.hijoIzqdo(n);
		while (hijo != Agen<T>::NODO_NULO)
		{
			grado = max(gradoArbolRec(hijo, A), grado);
			hijo = A.hermDrcho(hijo);
		}
		return grado;
	}
}

template <typename T>
int gradoArbol(const Agen<T> &A)
{
	return gradoArbolRec(A.raiz(), A);
}

// EJERCICIO 2 **************************************************

template <typename T>
int profundidadAgen(typename Agen<T>::nodo n, const Agen<T> &A)
{
	if (n == A.raiz())
	{
		return 0;
	}
	else
	{
		return 1 + profundidadAgen(A.padre(n), A);
	}
}

// EJERCICIO 3 **************************************************

template <typename T>
int alturaAgen(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int altura;
	typename Agen<T>::nodo hijo;
	if (n == Agen<T>::NODO_NULO)
	{
		return -1;
	}
	else
	{
		altura = 0;
		hijo = A.hijoIzqdo(n);
		while (hijo != Agen<T>::NODO_NULO)
		{
			altura = max(alturaAgen(hijo, A), altura);
			hijo = A.hermDrcho(hijo);
		}
		return altura + 1;
	}
}

template <typename T>
int gradoDesequilibrioRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int grado_max, grado_min;
	typename Agen<T>::nodo hijo;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		hijo = A.hijoIzqdo(n);
		grado_max = alturaAgen(n, A);
		grado_min = grado_max;
		while (hijo != Agen<T>::NODO_NULO)
		{
			grado_max = max(gradoDesequilibrioRec(A.hijoIzqdo(n), A), grado_max);
			grado_min = min(gradoDesequilibrioRec(A.hijoIzqdo(n), A), grado_min);
			hijo = A.hermDrcho(hijo);
		}
		return abs(grado_max - grado_min);
	}
}

template <typename T>
int gradoDesequilibrio(const Agen<T> &A)
{
	return gradoDesequilibrioRec(A.raiz(), A);
}

// Otra forma válida
/************************************
template <typename T>
int gradoDesequilibrioRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int grado;
	typename Agen<T>::nodo hijo;
	if (n == Agen<T>::NODO_NULO)
	{
		return 0;
	}
	else
	{
		grado = numHijos(n, A);
		hijo = A.hijoIzqdo(n);
		while (hijo != Agen<T>::NODO_NULO)
		{
			grado = abs(max(gradoDesequilibrioRec(hijo, A), grado) - min(gradoDesequilibrioRec(hijo,A),grado));
			hijo = A.hermDrcho(hijo);
		}
		return grado;
	}	
}

template <typename T>
int gradoDesequilibrio(const Agen<T> &A)
{
	return gradoDesequilibrioRec(A.raiz(),A);
}
/************************************ */

template <typename T>
bool esArbolTernarioRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
	int cont;
	typename Agen<T>::nodo hijo;
	if (n != Agen<T>::NODO_NULO)
	{
		if (numHijos(n, A) == 3)
		{
			cont = 0;
			hijo = A.hijoIzqdo(n);
			if (hijo != Agen<T>::NODO_NULO)
			{
				++cont;
				hijo = A.hermDrcho(hijo);
			}
			return cont == 3;
		}
		else
		{
			return false;
		}
	}
}

template <typename T>
bool esArbolTernario(const Agen<T> &A)
{
	if (!A.arbolVacio())
	{
		esArbolTernarioRec(A.raiz(),A);
	}
	else
	{
		return false;
	}
}

// En función del nivel o altura del árbol que tenga (k+1) será el tamaño máximo de la matriz
// El recorrido del cuadrante va al sentido de las agujas del reloj, empezando por el extremo superior izquierdo
// Si un cuadrante está completamente negro corresponde a una hoja NEGRA
// Si un cuadrante está completamente blanco corresponde a una hoja BLANCA
// Si un cuadrande no está complemente blanco o negro se tiene que seguir bajando nivel
// Árbol cuaternario (cuatro hijos o ninguno)

/**
template <typename T>
char[][] arbolBlancoNegroRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
	bool completo_negro = false;
	int n = 2;
	int M[][];
	if(n != Agen<T>::NODO_NULO)
	{
		if(A.elemento(n) == 'B')
		{
			if()

		}
		else if(A.elemento(n) == 'N')
		{

		}
		else
		{
			
		}
		
	}
	else
	{
		
	}
	
}

template <typename T>
int[][] arbolBlancoNegro(const Agen<T>& A)
{
	if(!A.arbolVacio())
	{
		return arbolBlancoNegroRec(A,A.raiz());
	}
}
**/

// MENÚ **************************************************

template <typename T>
void ejecutar_menu(const Agen<T> &A)
{
	int op;
	do
	{
		cout << "\nM e n ú" << endl;
		cout << "1. Práctica 3: Árboles Generales" << endl;
		cout << "2. Bonus" << endl;
		cout << "Elegir: ";
		cin >> op;

		switch (op)
		{
		case 1:
			cout << "\nS U B M E N Ú" << endl;
			cout << "1. Determinar grado del árbol" << endl;
			cout << "2. Determinar la profundidad de un nodo" << endl;
			cout << "3. Grado desequilibrio del árbol" << endl;
			cout << "4. ¿Es esto un árbol estrictamente ternario?" << endl;
			cout << "Elegir: ";
			cin >> op;

			switch (op)
			{
			case 1:
				cout << "El grado del árbol es: " << gradoArbol(A) << endl;
				break;
			case 2:
				cout << "Profundidad del nodo seleccionado: " << profundidadAgen(A.hijoIzqdo(A.hijoIzqdo(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))))), A) << endl;
				break;
			case 3:
				cout << "Grado desequilibrio del árbol:  " << gradoDesequilibrio(A) << endl;
				break;
			case 4:
				cout << "Este árbol es un árbol estrictamente ternario:  ";
				if (esArbolTernario(A))
				{
					cout << "SÍ." << endl;
				}
				else
				{
					cout << "NO." << endl;
				}
				break;

			default:
				break;
			}
			break;
		case 2:
			cout << "\nS U B M E N Ú" << endl;
			cout << "1. Mostrar árbol general" << endl;
			cout << "2. Contar nodos" << endl;
			cout << "3. Contar nodos que tengan un solo hijo" << endl;
			cout << "4. Grado desequilibrio del árbol a partir de la longitud de la rama más larga menos longitud de la rama más corta " << endl;
			cout << "Elegir: ";
			cin >> op;

			switch (op)
			{
			case 1:
				cout << "\n*** Mostrar árbol general A ***\n";
				imprimirAgen(A);
				break;
			case 2:
				cout << "En el árbol hay una cantidad de: " << contarNumNodos(A) << " nodos " << endl;
				break;
			case 3:
				cout << "En el árbol hay una cantidad de " << contarUnSolosHijo(A) << " nodos con un solo hijo." << endl;
				break;
			case 4:
				cout << "Grado desequilibrio del árbol:  " << gradoDesequilibriov2(A) << endl;
				break;
			default:
				break;
			}
		}
	} while (op != 0);
}

int main()
{
	Agen<char> A;
	cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
	ifstream fe("abin - ter.dat"); // abrir fichero de entrada
	rellenarAgen(fe, A);	 // desde fichero
	fe.close();
	ejecutar_menu(A);
}