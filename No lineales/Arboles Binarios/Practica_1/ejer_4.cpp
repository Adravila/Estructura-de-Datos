#include <iostream>
#include <fstream>
#include "abin_vec_0.hpp"
#include "abin_E-S.h"

using namespace std;

int main()
{
   Abin<char> A(12);
   cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
   ifstream fe("abin.dat"); // abrir fichero de entrada
   rellenarAbin(fe, A);     // desde fichero
   fe.close();
   cout << "\n*** Mostrar árbol binario B ***\n";
   imprimirAbin(A); // en std::cout
   cout << "\nProfundidad de un árbol: " << A.profundidadB(A.hijoDrchoB(A.raizB())) << endl;
   cout << "Altura de un árbol: " << A.alturaB(A.raizB()) << endl;
}