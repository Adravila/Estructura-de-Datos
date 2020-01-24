#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

int contarNodosRec(typename Abin<char>::nodo n, const Abin<char> &A)
{
    if(n == Abin<char>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + contarNodosRec(A.hijoIzqdoB(n),A) + contarNodosRec(A.hijoDrchoB(n),A);
    }
}

int alturaNodoRec(typename Abin<char>::nodo n, const Abin<char> &A)
{
    if(n == Abin<char>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + alturaNodoRec(A.hijoIzqdoB(n),A) + alturaNodoRec(A.hijoDrchoB(n),A);
    }
}

int profundidadNodoRec(typename Abin<char>::nodo n, const Abin<char> &A)
{
    if(A.padreB(n) == Abin<char>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + profundidadNodoRec(A.padreB(n), A);
    }
}

int contarNodos(const Abin<char> &A)
{
    return contarNodosRec(A.raizB(), A);
}

int main()
{
    Abin<char> A;
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n";
    ifstream fe("abin.dat"); // abrir fichero de entrada
    rellenarAbin(fe, A);     // desde fichero
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A); // en std::cout
    cout << "Nodos totales: " << contarNodos(A) << endl;
    cout << "Nodos totales: " << profundidadNodoRec(A.hijoIzqdoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB()))),A) << endl;
}