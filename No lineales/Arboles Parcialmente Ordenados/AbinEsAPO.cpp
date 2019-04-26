#include <iostream>
#include <fstream>
#include "Cabeceras/abin_din.hpp"
#include "Cabeceras/abin_E-S.h"
#include <math.h>

using namespace std;

template <typename T>
bool sonDescendientes(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        bool desciende = true;
        if (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.elemento(n) >= A.elemento(A.hijoIzqdoB(n)))
            {
                desciende = false;
            }
        }
        if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO)
        {
            if (A.elemento(n) >= A.elemento(A.hijoDrchoB(n)))
            {
                desciende = false;
            }
        }
        return desciende && sonDescendientes(A.hijoIzqdoB(n), A) && sonDescendientes(A.hijoDrchoB(n), A);
    }
}

template <typename T>
int alturaArbol(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    else
        return 1 + max(alturaArbol(A.hijoIzqdoB(n), A), alturaArbol(A.hijoDrchoB(n), A));
}

template <typename T>
bool esCompleto(typename Abin<T>::nodo n, const Abin<T> &A, int altura, int prof, bool flag)
{
    if (n == Abin<T>::NODO_NULO)
    {
        if (altura >= prof && flag)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if ((A.hijoDrchoB(n) == Abin<T>::NODO_NULO && A.hijoIzqdoB(n) != Abin<T>::NODO_NULO && !flag) ||
            (A.hijoDrchoB(n) != Abin<T>::NODO_NULO && A.hijoIzqdoB(n) == Abin<T>::NODO_NULO && !flag))
        {
            flag = true;
        }
        if (prof == altura - 1 && !flag)
        {
            if (A.hijoDrchoB(n) != Abin<T>::NODO_NULO || A.hijoIzqdoB(n) == Abin<T>::NODO_NULO)
            {
                flag = true;
            }
        }
        return true + esCompleto(A.hijoDrchoB(n), A, altura, prof + 1, flag) && esCompleto(A.hijoIzqdoB(n), A, altura, prof + 1, flag);
    }
}

template <typename T>
bool esAPO(const Abin<T> &A)
{
    if(!A.arbolVacioB())
    {
        //cout << "\nÁrbol completo: ";
        //esCompleto(A.raizB(), A, alturaArbol(A.raizB(), A), 0, false) ? cout << "SÍ" << endl : cout << "NO" << endl;
        //cout << "Son descendientes: ";
        //sonDescendientes(A.raizB(), A) ? cout << "SÍ" << endl : cout << "NO" << endl;
        return esCompleto(A.raizB(), A, alturaArbol(A.raizB(), A), 0, false) && sonDescendientes(A.raizB(), A);
    }
    else
    {
        return false;
    }
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
    Abin<tElto> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("Data/abin-completo.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);            // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A 'abin-completo.data' ***\n";
    imprimirAbin(A); // en std::cout
    cout << "\n¿Es esto un APO?: ";
    esAPO(A) ? cout << "SÍ, es un APO" << endl : cout << "NO, no es un APO" << endl;
}