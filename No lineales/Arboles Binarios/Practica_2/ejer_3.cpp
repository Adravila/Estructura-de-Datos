#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

using namespace std;

struct expresion
{
    double operando;
    char operador;
    expresion(char opr = ' ', double opn = 0) : operando(opr), operador(opn) {}
};

istream &operator>>(istream &i, expresion &n)
{
    i >> n.operador >> n.operando;
    i.ignore();
    return i;
}

ostream &operator<<(ostream &o, const expresion &n)
{
    o << n.operador << n.operando;
    return o;
}

bool operator!=(const expresion &izq, const expresion &der)
{
    return !(izq.operador == der.operador && izq.operando == der.operando);
}

// ****************************************************************************** //

template <typename T>
double calcularRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO) // Es hoja
        return A.elemento(n).operando;
    else
        switch (A.elemento(n).operador)
        {
        case '+':
            return calcularRec(A.hijoIzqdoB(n),A) + calcularRec(A.hijoDrchoB(n),A);
        case '-':
            return calcularRec(A.hijoIzqdoB(n),A) - calcularRec(A.hijoDrchoB(n),A);
        case '*':
            return calcularRec(A.hijoIzqdoB(n),A) * calcularRec(A.hijoDrchoB(n),A);
        case '/':
            return calcularRec(A.hijoIzqdoB(n),A) / calcularRec(A.hijoDrchoB(n),A);
        default:
            return A.elemento(n).operando;
        }
}

template <typename T>
double calcular(const Abin<T> &A)
{
    if (!A.arbolVacioB())
        return calcularRec(A.raizB(), A);
    else
        return 0;
}

int main()
{
    Abin<expresion> A;
    cout << "*****Lectura del arbol binario A desde abin.dat****\n";
    ifstream fs("abin-3.dat");
    rellenarAbin<expresion>(fs, A);
    fs.close();

    //---------------- Entradas y salidas
    imprimirAbin(A);
    cout << "\n resultado : " << calcular(A) << endl;
}
