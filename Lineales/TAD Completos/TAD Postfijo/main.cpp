#include "PostFijo.hpp"
#include "Pila_enla.h"
#include "Lista_enla.h"
#include <iostream>

using namespace std;

int main()
{
    const char *c1 = "ABC*+", *c2 = "CAB+*", *c3 = "CBA-/", *c4 = "CBA-/";
    tVariable A('A',3), B('B',5), C('C',6), D('D',1);

    Lista<tVariable> L;
    Lista<tVariable>::posicion p;
    p = L.primera();
    L.insertar(A,p);
    p = L.siguiente(p);
    L.insertar(B,p);
    p = L.siguiente(p);
    L.insertar(C,p);

    // ABC*+= 33 --> A+(BC)
    cout << "ABC*+ = " << calcularPostfijo(c1,L) << endl;

    // CAB+*=48 --> C*(A+B)
    cout << "CAB+* = " << calcularPostfijo(c2,L) << endl;

    // CBA-/=3 --> C/(B-A)
    cout << "CBA-/ = " << calcularPostfijo(c3,L) << endl;

    // AC-BD/+=2 --> A-C+B/D 
    cout << "AC-BD/+ = " << calcularPostfijo(c4,L) << endl;

}
