#include <algorithm>
#include <iostream> 
#include <fstream> 
#include "ABIN_VEC0_H.h" 
#include "abin_E-S.h"

template <typename T>
int diferenciaAltura(const Abin<T>& A, typename Abin<T>::nodo n )
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        return abs( A.alturaB(A.hijoIzqdoB(n))-A.alturaB(A.hijoDrchoB(n)) );
    }
}
template <typename T>
int ejer6(const Abin<T>& A, typename Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return std::max( std::max( diferenciaAltura(A, n), ejer6(A, A.hijoIzqdoB(n)) ), ejer6(A, A.hijoDrchoB(n)) );
}

using namespace std; 

int main () { 
   Abin<char> A(12); 
   cout << "\n*** Lectura de árbol binario B de abin-2.dat ***\n"; 
   ifstream fe("abin-2.dat");   // abrir fichero de entrada 
   rellenarAbin(fe, A);       // desde fichero 
   fe.close(); 
   cout << "\n*** Mostrar árbol binario B ***\n"; 
   imprimirAbin(A);           // en std::cout 
   cout << "Altura de un árbol: " << ejer6(A,(A.raizB())) << endl;
} 
