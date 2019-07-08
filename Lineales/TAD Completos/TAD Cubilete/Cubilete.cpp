#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Pila_enla.h"

using namespace std;

/*
  Un cubo es  cuerpo formado por seis caras que son cuadradas. La particularidad
  de estos cuerpos es que todas las caras son simetricas, están dispuestas de
  forma paralela y de a pares, y tienen cuatro lados. Una de las caras es hueca.
  Todo cubo cuenta con un tamaño invariable definido por el tamaño de una de sus
  aristas, y puede colocarse en 8 posiciones distintas, que pueden resumirse en
  cubo cuya cara opuesta se situe más arriba en la pila, es el que puede
  considerarse en el tope. Dicha relación será expresada en función del tamaño
  del cubo. Para realizar el juego utilizaré el tad Pila en su representación
  mediante celdas enlazadas, cuya especificación podreís encontrar en la teoría
  del tema 5 en el campus virtual.

  Operaciones:

  tCubo(entero, entero)
  Precondicion: recibe dos enteros como parametros o 1 en el caso por defecto.
  Postcondición: crea un cubo con un tamaño correspondiente al primer entero,
  siempre igual o mayor a 1, y otro entero que es la  posición, que si es 0 es
  boca abajo y si es mayor que 0, es bocarriba.

  entero tam()
  Postcondición: devuelve el tamaño del cubo.

  entero pos()
  Postcondición: devuelve la posición del cubo.

  procedimiento vuelta()
  Postcondición: cambia la posición del cubo. Si es 0 a 1. Si es mayor que 0, lo
  cambia a 0.

  PilaDeCubos juego(PilaDeCubos )
  Precondicion: recibe una PilaDeCubos con al menos 2 cubos.
  Postcondición: devuelve una PilaDeCubos con los cubos de la pila parametro
  ordenados de mayor a menor.
*/

class tCubo
{
public:
  tCubo(const int t = 1, const int p = 1);
  const int tam() const { return tam_; }
  int pos() const { return pos_; }
  void vuelta()
  {
    if (pos_)
    {
      pos_ = 0;
    }
    else
    {
      pos_ = 1;
    }
  }

private:
  int tam_;
  int pos_;
};

tCubo::tCubo(const int t, const int p) : tam_{t}, pos_{p}
{
  if (tam_ < 1)
    tam_ = 1;
  if (pos_ < 0)
    pos_ = 1;
}

Pila<tCubo> juego(Pila<tCubo> &P1)
{
  Pila<tCubo> P2, P3;

  while (!P1.vacia())
  {
    P2.push(P1.tope());
    P1.pop();

    if (P2.tope().pos())
    {
      tCubo aux(P2.tope());
      P2.pop();
      aux.vuelta();
      P2.push(aux);
    }

    if (!P1.vacia() && P1.tope().tam() > P2.tope().tam())
    {
      P3.push(P1.tope());
      P1.pop();
    }

    while (!P2.vacia() && !P3.vacia() && P2.tope().tam() < P3.tope().tam())
    {
      P1.push(P2.tope());
      P2.pop();
    }

    if (!P3.vacia())
    {
      P2.push(P3.tope());
      P3.pop();
    }
  }

  return P2;
}

void pilePrint(const Pila<tCubo> P)
{
  Pila<tCubo> P1(P);

  while (!P1.vacia())
  {
    cout << P1.tope().tam() << " ";
    P1.pop();
  }

  cout << endl;
}

int main()
{
  srand(time(NULL));
  Pila<tCubo> P;
  unsigned i = 0;

  while (i < 5)
  {
    P.push(tCubo(rand() % 10 + 1, rand() % 2));
    ++i;
  }

  pilePrint(P);
  Pila<tCubo> P1 = juego(P);
  pilePrint(P1);

  return 0;
}
