#ifndef LISTA_CIRCULAR
#define LISTA_CIRCULAR
#include <cassert>
#define POS_NULL NULL

template <typename T> class ListaCir {
	struct nodo; // declaración adelantada privada
public:
		 typedef nodo* posicion; // posición de un elemento
		 ListaCir(); // constructor, requiere ctor. T()
		 ListaCir(const ListaCir<T>& l); // ctor. de copia, requiere ctor. T()
		 ListaCir<T>& operator =(const ListaCir<T>& l); // asignación delistas
		 void insertar(const T& x, posicion p);
		 void eliminar(posicion p);
		 T elemento(posicion p) const; // acceso a elto, lectura
		 T& elemento(posicion p); // acceso a elto, lectura/escritura
		 posicion buscar(const T& x) const; // T requiere operador ==
		 posicion siguiente(posicion p) const;
		 posicion anterior(posicion p) const;
		 posicion inipos() const;
		 ~ListaCir(); // destructor
private:
		struct nodo {
			 T elto;
			 nodo *ant, *sig;
			 nodo(const T& e, nodo* a = 0, nodo* s = 0) :
			 elto(e), ant(a), sig(s) {}
			 };
	  nodo* L; // lista doblemente enlazada de nodos
    void copiar(const ListaCir<T>& l);
};
// Método privado
 template <typename T>
 void ListaCir<T>::copiar(const ListaCir<T> &l)
 {
        if(l.inipos() != POS_NULL)                              //Si la lista a copiar tiene algun elemento, se copian
        {
            L = new nodo(l.elemento(l.inipos()), 0, 0);
            L->sig = L->ant = L;
            nodo* q;

            q = L;
            for (nodo* r = l.L->sig; r != l.L; r = r->sig) {
                 q->sig = new nodo(r->elto, q, L);
               q = q->sig;
            }
            L->ant = q;

        } else
        {
            L = 0;                                              //Si no se crea una lista vacia normal
        }
 }

 template <typename T>
 inline ListaCir<T>::ListaCir() : L( NULL ) {}                       //Devuelve una lista vacía en la que L será un puntero nulo



 template <typename T>
 inline ListaCir<T>::ListaCir(const ListaCir<T>& l) { copiar(l); }      //Const copia

 template <typename T>
 ListaCir<T>& ListaCir<T>::operator =(const ListaCir<T>& l)             // sobrecarga asignación
 {
			 if (this != &l) { // evitar autoasignación
				 this->~ListaCir(); // vaciar la lista actual
				 copiar(l);
			 }
			 return *this;
 }

 template <typename T> inline
 void ListaCir<T>::insertar(const T& x, ListaCir<T>::posicion p)
 {

    if(L == POS_NULL)                                           //Si la posición es nula creamos el primer nodo de la lista
    {
        L = new nodo(x, p, p);
        L->ant = L->sig = L;

    }
    else
        p->sig = p->sig->ant = new nodo(x, p, p->sig);          // el nuevo nodo con x queda en la posición p

 }

 template <typename T>
 inline void ListaCir<T>::eliminar(ListaCir<T>::posicion p)
 {
     p = p->sig;

     if(p == L)                                                 //Si el elemento a borrar es al que apunta L, L apunta al que ahora ocupa p
     {
        L = p->sig;
        p->ant->sig = p->sig;
        p->sig->ant = p->ant;
     }
     else                                                        // el nodo siguiente queda en la posición p
     {
        p->ant->sig = p->sig;
        p->sig->ant = p->ant;
     }

     if(p == p->sig)                                             // Si la lista solo tiene un elemento antes de eliminarlo apuntamos L a 0
            L = 0;

     delete p;


 }

 template <typename T>
 inline T ListaCir<T>::elemento(ListaCir<T>::posicion p) const
 {
		 return p->sig->elto;                                    // La direccion del un elemento se consigue pasando la posición del anterior
 }

 template <typename T>
 inline T& ListaCir<T>::elemento(ListaCir<T>::posicion p)
 {

		 return p->sig->elto;
 }

 template <typename T>
 typename ListaCir<T>::posicion
 ListaCir<T>::buscar(const T& x) const
 {
         assert(L == POS_NULL)  ;                                                     //Precondicion para evitar errores de ejecución
		 nodo* q;
		 bool encontrado;

		 encontrado = false;
         q = inipos();
		 while (q->sig != inipos() && !encontrado)
         {
		 		if (q->sig->elto == x)
					 encontrado = true;
                else
                     q = q->sig;
         }

         if(q->elto != x)
                q == POS_NULL;                                  //Si no está en la lista devuelve POS_NULL

		 return q;
 }

 template <typename T> inline
 typename ListaCir<T>::posicion ListaCir<T>::siguiente(ListaCir<T>::posicion p) const
 {
			 return p->sig;
 }

 template <typename T> inline
 typename ListaCir<T>::posicion
 ListaCir<T>::anterior(ListaCir<T>::posicion p) const
 {
		 return p->ant;
 }

 template <typename T>
 inline typename ListaCir<T>::posicion ListaCir<T>::inipos() const
 {
     nodo* posicion;

    if(L == POS_NULL)                                                           //Si la lista no tiene  elementos se devuelve pos_null
        posicion = POS_NULL;
    else
        posicion = L->ant;

    return posicion;
 }

 // Destructor: Vacía la lista y destruye el nodo cabecera
 template <typename T>
 ListaCir<T>::~ListaCir()
 {

			 if(L != 0)                                         //Si la lista está vacia solo se elimina el puntero L
             {
                 nodo* q;
                    while (L->sig != L)
                    {
					 q = L->sig;
					 L->sig = q->sig;
					  delete q;
                    }

             }

			 delete L;


 }
#endif // listacircular

