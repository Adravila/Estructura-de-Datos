#include <iostream> 
#include <fstream> 
#include "ABIN_H.h"
#include "abin_E-S.h"

using namespace std; 

struct expresion{
    double operando;
    char operador;
    expresion(char opr = ' ', double opn = 0) : operando(opr), operador(opn){}
};

istream& operator >>(istream &i, expresion& n)
{
    i >> n.operador >> n.operando;
    i.ignore();
    return i;
}

ostream& operator <<(ostream &o,const expresion& n)
{
    o << n.operador  << n.operando;
    return o;
}

bool operator !=(const expresion& izq,const expresion& der){
    return !(izq.operador == der.operador && izq.operando == der.operando);
}


// ****************************************************************************** //

template <typename T>
double calcularRec(const Abin<T>& A, typename Abin<T>::nodo n){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        switch(A.elemento(n).operador){
            case '+': return calcularRec(A,A.hijoIzqdoB(n))+calcularRec(A,A.hijoDrchoB(n));
            case '-': return calcularRec(A,A.hijoIzqdoB(n))-calcularRec(A,A.hijoDrchoB(n));
            case '*': return calcularRec(A,A.hijoIzqdoB(n))*calcularRec(A,A.hijoDrchoB(n));
            case '/': return calcularRec(A,A.hijoIzqdoB(n))/calcularRec(A,A.hijoDrchoB(n));
            default:  return A.elemento(n).operando;
        }
}

template <typename T>
double calcular(const Abin<T>& A){
    if(!A.arbolVacioB())
        return calcularRec(A,A.raizB());
    else
        return 0;
}

int main()
{
    Abin<expresion> A;
    cout << "*****Lectura del arbol binario A desde abin.dat****\n";
    ifstream fs("abin.dat");
    rellenarAbin<expresion>(fs, A);
    fs.close();

    //---------------- Entradas y salidas
    imprimirAbin(A);
    cout << "\n resultado : "<< calcular(A) << endl;;
}
