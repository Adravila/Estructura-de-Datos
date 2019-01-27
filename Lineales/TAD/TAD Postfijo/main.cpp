#include "PostFijo.hpp"
#include "Pila_enla.h"
#include <iostream>

using namespace std;

int main()
{
    Pila<tVariable> P1, P2, P3;
    tVariable A(3), B(5), C(6);
    tVariable op_suma('+'), op_resta('-'), op_prod('*'), op_div('/');
    
    // ABC*+= 33 --> A+(BC)
    P1.push(A); P1.push(B); P1.push(C); P1.push(op_prod); P1.push(op_suma);
    cout << "ABC*+ = " << calcularPostfijo(P1) << endl;

    // CAB+*=48 --> C*(A+B)
    P2.push(C); P2.push(A); P2.push(B); P2.push(op_suma); P2.push(op_prod);  
    cout << "CAB+* = " << calcularPostfijo(P2) << endl;

    // CBA-/=3 --> C/(B-A)
    P3.push(C); P3.push(B); P3.push(A); P3.push(op_resta); P3.push(op_div);
    cout << "CBA-/ = " << calcularPostfijo(P3) << endl;
}
