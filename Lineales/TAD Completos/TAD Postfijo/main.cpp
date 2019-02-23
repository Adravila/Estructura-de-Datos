#include "PostFijo.hpp"
#include "Pila_enla.h"
#include "Cola_enla.h"
#include <iostream>

using namespace std;

int main()
{
    Cola<tVariable> C1, C2, C3;
    tVariable A(3), B(5), C(6);
    tVariable op_suma('+'), op_resta('-'), op_prod('*'), op_div('/');
    
    // ABC*+= 33 --> A+(BC)
    C1.push(A); C1.push(B); C1.push(C); C1.push(op_prod); C1.push(op_suma);
    cout << "ABC*+ = " << calcularPostfijo(C1) << endl;

    // CAB+*=48 --> C*(A+B)
    C2.push(C); C2.push(A); C2.push(B); C2.push(op_suma); C2.push(op_prod);  
    cout << "CAB+* = " << calcularPostfijo(C2) << endl;

    // CBA-/=3 --> C/(B-A)
    C3.push(C); C3.push(B); C3.push(A); C3.push(op_resta); C3.push(op_div);
    cout << "CBA-/ = " << calcularPostfijo(C3) << endl;
}
