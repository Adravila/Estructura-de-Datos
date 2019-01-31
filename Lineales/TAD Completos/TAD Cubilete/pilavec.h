//Implementación genérica vectorial pseudoestática

#ifndef PILA_VEC_H
#define PILA_VEC_H
#include <cassert>

template <typename tElemento>
class Pila {
   public:
      explicit Pila(unsigned TamaMax); // constructor
      Pila(const Pila& p); // ctor. de copia
      Pila& operator =(const Pila& p); // asignación entre pilas
      bool vacia() const;
      bool llena() const; // Requerida por la implementación
      tElemento tope() const;
      void pop();
      void push(const tElemento& x);
      ~Pila(); // destructor
   private:
      tElemento *elementos; // vector de elementos
      unsigned Lmax; // tamaño del vector
      int tope_; // posición del tope
};

template <typename tElemento>
inline Pila<tElemento>::Pila(unsigned TamaMax) :
   elementos(new tElemento[TamaMax]),
   Lmax(TamaMax),
   tope_(-1)
{}

template <typename tElemento>
Pila<tElemento>::Pila(const Pila<tElemento>& p) :
   elementos(new tElemento[p.Lmax]),
   Lmax(p.Lmax),
   tope_(p.tope_)
{
   for (int i = 0; i <= tope_; i++) // copiar el vector
      elementos[i] = p.elementos[i];
}

template <typename tElemento>
Pila<tElemento>& Pila<tElemento>::operator =(const Pila<tElemento>& p)
{
   if (this != &p) { // evitar autoasignación
      // Destruir el vector y crear uno nuevo si es necesario
      if (Lmax != p.Lmax) {
         delete[] elementos;
         Lmax = p.Lmax;
         elementos = new tElemento[Lmax];
      }
      // Copiar el vector
      tope_ = p.tope_;
      for (int i = 0; i <= tope_; i++)
         elementos[i] = p.elementos[i];
   }
   return *this;
}

template <typename tElemento>
inline bool Pila<tElemento>::vacia() const
{
   return (tope_ == -1);
}

template <typename tElemento>
inline bool Pila<tElemento>::llena() const
{
   return (tope_ != -1 && tope_ > Lmax - 2);
}

template <typename tElemento>
inline tElemento Pila<tElemento>::tope() const
{
   assert(!vacia());
   return elementos[tope_];
}

template <typename tElemento>
inline void Pila<tElemento>::pop()
{
   assert(!vacia());
   --tope_;
}

template <typename tElemento>
inline void Pila<tElemento>::push(const tElemento& x)
{
   assert(!llena());
   ++tope_;
   elementos[tope_] = x;
}

template <typename tElemento>
inline Pila<tElemento>::~Pila()
{
   delete[] elementos;
}

#endif //PILA_VEC_H
