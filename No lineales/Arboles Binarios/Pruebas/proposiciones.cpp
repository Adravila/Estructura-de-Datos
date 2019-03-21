#include <iostream>
#include <fstream>
#include "abin_din.hpp"
#include "abin_E-S.h"

/**
 Ejercicio Examen Septiembre 2013
 Una proposición o formula proposicional es:
 - Un símbolo proposicional del conjunto {p1,p2,…,pn} siendo N una constante arbitraria, o bien
 - Una expresión constituida aplicando conectivas lógicas a otras formulas proposicionales. 
 
 Se consideran las conectivas ^ (Y), ˅ (O) y ¬ (NO).
 Una valoración es una asignación de un valor de verdad (verdadero o falso) a cada símbolo {p1,p2,…,pn}.
 La forma de representar una valoración será mediante una secuencia de valores de verdad. 
 
 Por tanto, siendo v una secuencia de valores de verdad de longitud N, la valoración del símbolo pi, 
 es el valor indicado por el índice i-esimo de v. Por ejemplo, suponiendo N=3, la secuencia <verdadero, falso, verdadero> 
 representa la valoración que asigna verdadero a p1, falso a p2 y verdadero a p3. Una vez que se tiene una valoración, 
 es posible obtener un valor de verdad para cualquier formula, proposición con solo interpretar las conectivas lógicas 
 con su significado convencional.

 Veamos una serie de ejemplo suponiendo N=3:

 Proposición Valoración Valor de verdad
 p1 ^ p2 <verdadero, falso, falso> Falso
 p1 ^ ¬ p2 <verdadero, verdadero, falso> Verdadero
 p1 ^ ¬ p1 <falso, falso, falso> Verdadero
 (p1 ˅ p3) ^ p2 <verdadero, falso, falso> Falso

 Una forma de representar una proposición es mediante un árbol binario en el que los nodos internos contienen las conectivas
 lógicas y las hojas contienen los símbolos porposicionales.
 
 Se pide:
 - Crear una proposición con un único símbolo del conjunto {p1,p2,…,pn} con N constante.
 - Tres operaciones (Y, O, No) para construir una nueva formula a partir de otros previamente creados.
 - Destruir una proposición.
 - Calcular el valor de verdad de una formula, a partir de una valoración del conjunto de símbolos {p1,p2,…,pn} siendo N constante.
**/ 

using namespace std;

struct proposicion
{
    proposicion(char op_ = ' ', bool val_ = false) : op(op_), val(val_) {}
    char op;
    bool val;
};

istream &operator>>(istream &i, proposicion &n)
{
    i >> n.op >> n.op;
    i.ignore();
    return i;
}

ostream &operator<<(ostream &o, const proposicion &n)
{
    o << n.op << n.val;
    return o;
}

bool operator!=(const proposicion &izq, const proposicion &der)
{
    return !(izq.op == der.op && izq.val == der.val);
}

/*****************************************************************/
/*****************************************************************/
template <typename T>
class proposiciones
{
    typedef char ELTO_AND, ELTO_OR;
    public:
        proposiciones(int n);
        void raizProp(const proposicion& p, int N, const Abin<T>& A);
        void opAND(typename Abin<T>::nodo n, const T& e, const Abin<T>& A);
        void opOR(typename Abin<T>::nodo n, const T& e, const Abin<T>& A);
        void opNOT(typename Abin<T>::nodo n, const Abin<T>& A);
        void destruirProp(typename Abin<T>::nodo n, const Abin<T>& A);
        bool calcular(const Abin<T> &A);
    private:
        bool calcularRec(typename Abin<T>::nodo n, const Abin<T> &A);
        int N;
        bool* v;
};

template <typename T>
proposiciones<T>::proposiciones(int n) : v(n), N(n)
{
    ELTO_AND = '^';
    ELTO_OR = 'v'
}  

template <typename T>
void proposiciones<T>::raizProp(const proposicion& p, int N, const Abin<T>& A)
{
    A.insertarRaizB(p);
}

template <typename T>
void proposiciones<T>::opAND(typename Abin<T>::nodo n, const T& e, const Abin<T>& A)
{
    assert(N < 3);
    A.insertarHijoIzqdoB(n,A.elemento(n));
    A.elemento(n) = ELTO_AND;
    A.insertarHijoDrchoB(n,e);
    ++N;
}

template <typename T>
void proposiciones<T>::opOR(typename Abin<T>::nodo n, const T& e, const Abin<T>& A)
{
    assert(N < 3);
    A.insertarHijoIzqdoB(n,A.elemento(n));
    A.elemento(n) = NODO_OR;
    A.insertarHijoDrchoB(n,e);
    ++N;
}

template <typename T>
void opNOT(typename Abin<T>::nodo n, const Abin<T>& A)
{
    A.insertarHijoIzqdoB(n,NODO_NOT);
}


template <typename T>
void proposiciones<T>::destruirProp(typename Abin<T>::nodo n, const Abin<T>& A)
{

}

template <typename T>
bool proposiciones<T>::calcular(const Abin<T> &A)
{
    if (!A.arbolVacioB())
    {
        return calcularRec(A.raizB(), A);
    }
    else
    {
        return false;
    }
}

template <typename T>
bool proposiciones<T>::calcularRec(typename Abin<T>::nodo n, const Abin<T> &A)
{
    if (A.hijoIzqdoB(n) == Abin<T>::NODO_NULO) // Es hoja
    {
        return A.elemento(n).val;
    }
    else
    {
        switch (A.elemento(n).op)
        {
        case '^':
            return calcularRec(A.hijoIzqdoB(n),A) && calcularRec(A.hijoDrchoB(n),A);
            break;
        case 'v':
            return calcularRec(A.hijoIzqdoB(n),A) || calcularRec(A.hijoDrchoB(n),A);
            break;
        default:
            return false;
        }
    }
}

int main()
{
    Abin<proposicion> A;
    cout << "*****Lectura del arbol binario A desde abin.dat****\n";
    ifstream fs("abin-3.dat");
    rellenarAbin<proposicion>(fs, A);
    fs.close();

    //---------------- Entradas y salidas
    imprimirAbin(A);
    cout << "\n resultado : " << logProp(A) << endl;
}