#include "Agen.h"

template <typename T>
int profundidad(const Agen<T>& A, typename Agen<T>::nodo n){
	if(A.padre(n) == Agen<T>::NODO_NULO)
		return 0;
	else
		return 1+profundidad(A,A.padre(n));
}

template <typename T>
int descendientes(const Agen<T>& A, typename Agen<T>::nodo n){
	int desc = 0;
	if(n == Agen<T>::NODO_NULO)
		return 0;
	else{
		desc++;
		typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
		if(hijo != Agen<T>::NODO_NULO){
			desc += descendientes(A,hijo);
			hijo = A.hermDrcho(A.hijoIzqdo(n));
			while(hijo != Agen<T>::NODO_NULO){
				desc += descendientes(A,hijo);
				hijo = A.hermDrcho(hijo);
			}
		}
		return desc;
	}
}

template <typename T>
bool esNostalgico(const Agen<T>& A, typename Agen<T>::nodo n){
    std::cout << profundidad(A,n) << " > " << descendientes(A,n)-1 << std::endl;
	return (profundidad(A,n) > descendientes(A,n)-1);
}

template <typename T>
int NostalgicoRec(const Agen<T>& A, typename Agen<T>::nodo n){
	int nost = 0;
	if(n != Agen<T>::NODO_NULO){
		if(esNostalgico(A,n)){
			nost++;
		}else{
			typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
			if(hijo != Agen<T>::NODO_NULO){
				nost += NostalgicoRec(A,hijo);
				hijo = A.hermDrcho(A.hijoIzqdo(n)); // Es el hermano del hijo
				while(hijo != Agen<T>::NODO_NULO){
					nost += NostalgicoRec(A,hijo);
					hijo = A.hermDrcho(hijo);
				}
			}
		}
		return nost;
	}
}

template <typename T>
int Nostalgico(const Agen<T>& A){
	if(!A.arbolVacio())
		return NostalgicoRec(A,A.raiz());
	else
		return 0;
}
