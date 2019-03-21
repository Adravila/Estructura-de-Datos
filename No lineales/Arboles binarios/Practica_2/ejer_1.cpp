#include <iostream> 
#include <fstream> 
#include "abin_din.hpp" 
#include "abin_E-S.h"

using namespace std; 

template <typename T>
bool arbolesSimilaresRec(const Abin<T>& A, typename Abin<T>::nodo n, const Abin<T>& B, typename Abin<T>::nodo m){
    if(n == Abin<T>::NODO_NULO && m == Abin<T>::NODO_NULO)
        return true;
    else
        if(n != Abin<T>::NODO_NULO && m != Abin<T>::NODO_NULO)
            return arbolesSimilaresRec(A,A.hijoIzqdoB(n),B,A.hijoIzqdoB(m)) && arbolesSimilaresRec(A,A.hijoDrchoB(n),B,A.hijoDrchoB(m));
        else
            return false;
}

template <typename T>
bool arbolesSimilares(const Abin<T>& A, const Abin<T>& B){
    if(A.arbolVacioB() || B.arbolVacioB())
        return A.arbolVacioB() && B.arbolVacioB();
    else
        return arbolesSimilaresRec(A,A.raizB(),B,B.raizB());
}

int main () { 
    Abin<char> A,B; 
    cout << "\n*** Lectura de árbol binario A de abin.dat ***\n"; 
    ifstream fe("abin.dat");   // abrir fichero de entrada 
    rellenarAbin(fe, A);       // desde fichero 
    fe.close(); 
    cout << "\n*** Mostrar árbol binario A ***\n"; 
    imprimirAbin(A);     
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n"; 
    ifstream fa("abin.dat");   // abrir fichero de entrada 
    rellenarAbin(fa, B);       // desde fichero 
    fa.close(); 
    cout << "\n*** Mostrar árbol binario B ***\n"; 
    imprimirAbin(B);         // en std::cout 
    if(arbolesSimilares(A,B))
        cout << "\nLos dos arboles son similares.\n";
    else
        cout << "\nLos dos arboles son distintos.\n";
} 
