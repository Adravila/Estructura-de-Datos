#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"
#include "math.h"
#include <map>

using namespace std;


bool evaluarExpresionRecursiva(Abin<char>::nodo n, Abin<char> A, map<char,bool> variables)
{
    if(n == Abin<char>::NODO_NULO)
    {
        return false;
    }
    else
    {
        if(A.hijoIzqdoB(n) == Abin<char>::NODO_NULO && A.hijoDrchoB(n) == Abin<char>::NODO_NULO)
        {
            map<char,bool>::iterator i = variables.find(A.elemento(n));
            if(i != variables.end())
            {
                return i->second;
            }
            else
            {
                return false;
            }
        }
        else
        {
            bool i = evaluarExpresionRecursiva(A.hijoIzqdoB(n),A,variables);
            bool d = evaluarExpresionRecursiva(A.hijoDrchoB(n),A,variables);
            bool res;
            switch (A.elemento(n))
            {
                case 'A': res = i && d; break;
                case 'O': res = i || d; break;
                case 'N': res = !i; break;
                default: break;
            }
            return res;
        }
    }
}


bool evaluarExpresion(Abin<char> A, map<char,bool>variables)
{
    return evaluarExpresionRecursiva(A.raizB(),A,variables);
}

/****************************************************/

typedef char tElto;
const tElto fin = '#'; // fin de lectura

int main()
{
   Abin<tElto> A;
   cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
   ifstream fe("abin-pro.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario A ***\n";
   imprimirAbin(A); // en std::cout


    map<char,bool> mapa;

    mapa.insert(make_pair('p',true));
    mapa.insert(make_pair('q',false));
    mapa.insert(make_pair('r',false));

   cout << "\nCantidad de nodos con tres nietos: " << evaluarExpresion(A,mapa) << endl;
}