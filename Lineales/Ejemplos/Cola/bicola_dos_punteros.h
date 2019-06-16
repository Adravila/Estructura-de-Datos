//Implementación mediante dos punteros a los extremos

#ifndef BICOLA_H
#define BICOLA_H
#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;

template <typename T>
class Bicola
{
public:
   Bicola();                                 // constructor
   Bicola(const Bicola<T> &p);               // ctor. de copia
   Bicola<T> &operator=(const Bicola<T> &p); // asignación de colas
   bool vacia() const;
   T frente() const;
   void pop();
   void push(const T &x);
   ~Bicola(); // destructor

   // Exclusivo de la cola (Bicola)
   void pushIni(const T &x);
   void popFin();

private:
   struct nodo
   {
      T elto;
      nodo *sig;
      nodo(const T &e, nodo *p = 0) : elto(e), sig(p) {}
   };
   nodo *inicio, *fin; // extremos de la cola
   void copiar(const Bicola<T> &c);
};

template <typename T>
void Bicola<T>::copiar(const Bicola<T> &c)
{
   if (c.inicio)
   { // c no está vacía
      // Copiar el primer elto.
      inicio = fin = new nodo(c.inicio->elto);
      // Copiar el resto de elementos hasta el final de la cola.
      for (nodo *q = c.inicio->sig; q; q = q->sig)
      {
         fin->sig = new nodo(q->elto);
         fin = fin->sig;
      }
   }
}

template <typename T>
inline Bicola<T>::Bicola() : inicio(0), fin(0)
{
}

template <typename T>
inline Bicola<T>::Bicola(const Bicola<T> &c) : inicio(0), fin(0)
{
   copiar(c);
}

template <typename T>
inline Bicola<T> &Bicola<T>::operator=(const Bicola<T> &c)
{
   if (this != &c)
   {                 // evitar autoasignación
      this->~Cola(); // vaciar la cola actual
      copiar(c);
   }
   return *this;
}

template <typename T>
inline bool Bicola<T>::vacia() const
{
   return (inicio == 0);
}

template <typename T>
inline T Bicola<T>::frente() const
{
   assert(!vacia());
   return inicio->elto;
}

template <typename T>
inline void Bicola<T>::pop()
{
   assert(!vacia());
   nodo *q = inicio;
   inicio = q->sig;
   if (!inicio)
      fin = 0;
   delete q;
}

template <typename T>
inline void Bicola<T>::push(const T &x)
{
   nodo *q = new nodo(x);
   if (inicio == 0) // cola vacía
      inicio = fin = q;
   else
      fin = fin->sig = q;
}

// Destructor: vacía la cola
template <typename T>
Bicola<T>::~Bicola()
{
   nodo *q;
   while (inicio)
   {
      q = inicio->sig;
      delete inicio;
      inicio = q;
   }
   fin = 0;
}

// Exclusivo de la cola (Bicola)
template <typename T>
void Bicola<T>::pushIni(const T &x)
{
   if (vacia())
   {
      fin = inicio = new nodo(x, 0);
   }
   else
   {
      inicio = new nodo(x, inicio);
   }
}

template <typename T>
void Bicola<T>::popFin()
{
   assert(!vacia());
   if (inicio == fin)
   {
      inicio = fin = 0;
   }
   else
   {
      nodo *p = inicio;
      while (p->sig != fin)
      {
         p = p->sig;
      }
      fin = p;
      fin->sig = 0;
      delete p->sig;
   }
}

#endif // COLA_ENLA_H
