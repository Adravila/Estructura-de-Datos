#include "Agen.h"

template <typename T>
int profNodoRec(const Agen<T>& A, typename Agen<T>::nodo n){
    if(n == A.raiz())
        return 0;
    else
        return 1+profNodoRec(A,A.padre(n));
}

template <typename T>
int profNodo(const Agen<T>& A, typename Agen<T>::nodo n){
    if(A.arbolVacio())
        return 0;
    else
        return profNodoRec(A,n);
}
