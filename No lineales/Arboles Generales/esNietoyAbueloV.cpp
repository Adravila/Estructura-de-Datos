#include <iostream>
#include <fstream>
#include "Cabeceras/Agen.hpp"
#include "Cabeceras/agen_E-S.h"
#include <math.h>

using namespace std;

/**
 * Comprobar si el árbol contiene un nodo que sea nieto y abuelo a la vez
 * Creado por: Adrián Dávila Guerra ©
 * 25/04/2019
**/

template <typename T>
bool esNietoAbuelo(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return false;    
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        bool esAbuelo = false;
        bool esNieto = false;
        bool estado = false;

        // Comprobar si tiene abuelo
        if(A.padre(n) != Agen<T>::NODO_NULO && A.padre(A.padre(n)) != Agen<T>::NODO_NULO)
        {                
            esNieto = true;
        }

        // Comprobar si tiene al menos un nieto
        while(hijo != Agen<T>::NODO_NULO)
        {
            if(A.hijoIzqdo(hijo) != Agen<T>::NODO_NULO)
            {
                esAbuelo = true;
            }
            estado = (esAbuelo && esNieto) || esNietoAbuelo(hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        return estado;
    }
}

template <typename T>
int contarNietoYAbuelo(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return 0;    
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        bool esAbuelo = false;
        bool esNieto = false;
        int cont = 0;

        // Comprobar si tiene abuelo
        if(A.padre(n) != Agen<T>::NODO_NULO && A.padre(A.padre(n)) != Agen<T>::NODO_NULO)
        {                
            esNieto = true;
        }

        // Comprobar si tiene al menos un nieto
        while(hijo != Agen<T>::NODO_NULO)
        {
            if(A.hijoIzqdo(hijo) != Agen<T>::NODO_NULO)
            {
                esAbuelo = true;
            }
            cont = contarNietoYAbuelo(hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        
        if(esAbuelo && esNieto)
        {
            return cont + 1;
        }
        else
        {
            return cont;
        }
    }
}

int main()
{
    Agen<char> A;
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("Data/agen-abu.dat"); // abrir fichero de entrada
    rellenarAgen(fe, A);              // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol general A ***\n";
    imprimirAgen(A);
    cout << "Este árbol tiene un nieto y a su vez es abuelo: ";
    if (esNietoAbuelo(A.hermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), A))
    {
        cout << "SÍ." << endl;
    }
    else
    {
        cout << "NO." << endl;
    }
    cout << "Y tiene: " << contarNietoYAbuelo(A.hermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), A) << " nodos que son abuelos y nietos a la vez\n";
}