#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Calcular el grado de todo el árbol general
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

// Alternativa

template <typename T>
int gradoAgenRec2(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        // Declaración de variables
        typename Agen<T>::nodo hijo;
        int gradoMax;
        // Definición de variables
        gradoMax = 0;
        hijo = A.hijoIzqdo(n);

        while (hijo != Agen<T>::NODO_NULO)
        {
            if (n != A.raiz()) // Para evitar que el nodo raíz pase más de una vez
            {
                ++gradoMax;
            }
            gradoMax = std::max(gradoMax, gradoAgenRec(hijo, A));
            hijo = A.hermDrcho(hijo);
        }
        return gradoMax;
    }
}

// Método principal

template <typename T>
int gradoAgenRec(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == Agen<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        // Declaración de variables
        typename Agen<T>::nodo hijo;
        int gradoMax;
        // Definición de variables
        gradoMax = 0;
        hijo = A.hijoIzqdo(n);

        // Contar hijos
        while (hijo != Agen<T>::NODO_NULO)
        {
            ++gradoMax;
            hijo = A.hermDrcho(hijo);
        }
        
        hijo = A.hijoIzqdo(n);

        while (hijo != Agen<T>::NODO_NULO)
        {
            gradoMax = std::max(gradoMax, gradoAgenRec(hijo, A));
            hijo = A.hermDrcho(hijo);
        }
        return gradoMax;
    }
}

template <typename T>
int gradoAgen(const Agen<T> &A)
{
    return gradoAgenRec(A.raiz(), A);
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
    cout << "\nCalcular grado del árbol A 'agen': " << gradoAgen(A) << endl;

    cout << "\n*** Lectura de árbol general B de agen-ter.dat ***\n";
    ifstream fb("Data/agen-ter.dat"); // abrir fichero de entrada
    rellenarAgen(fb, B);              // desde fichero
    fb.close();
    cout << "\n*** Mostrar árbol general B ***\n";
    imprimirAgen(B); // en std::cout
    cout << "\nCalcular grado del árbol B 'agen-ter': " << gradoAgen(B) << endl;

    cout << "\n*** Lectura de árbol general C de agen-cua.dat ***\n";
    ifstream fc("Data/agen-cua.dat"); // abrir fichero de entrada
    rellenarAgen(fc, C);              // desde fichero
    fc.close();
    cout << "\n*** Mostrar árbol general C ***\n";
    imprimirAgen(C); // en std::cout
    cout << "\nCalcular grado del árbol C 'agen-cua': " << gradoAgen(C) << endl;

    cout << "\n*** Lectura de árbol general D de agen-abu.dat ***\n";
    ifstream fd("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fd, D);              // desde fichero
    fd.close();
    cout << "\n*** Mostrar árbol general D ***\n";
    imprimirAgen(D); // en std::cout
    cout << "\nCalcular grado del árbol D 'agen-abu': " << gradoAgen(D) << endl;
}
