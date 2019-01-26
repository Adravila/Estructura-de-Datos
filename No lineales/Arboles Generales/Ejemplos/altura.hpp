#include "Agen.h"

template <typename T>
int alturaNodoRec(const Agen<T>& A, typename Agen<T>::nodo n){
    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else{
        int alturaMax;
        typename Agen<T>::nodo hijo;

        alturaMax = 0;
        hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO){
            alturaMax = std::max(alturaMax, alturaNodoRec(A,hijo)+1);
            hijo = A.hermDrcho(hijo);
        }
        return alturaMax;
    }
}

template <typename T>
int alturaNodo(const Agen<T>& A, typename Agen<T>::nodo n){
    if(A.arbolVacio())
        return 0;
    else
        return alturaNodoRec(A,n);
}
