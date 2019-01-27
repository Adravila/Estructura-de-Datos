#include <iostream>
#include "Pila_enla.h"

using namespace std;

bool XY(const Pila<char>& P)
{
    Pila<char> P_ORG, P_INV;
    P_ORG = P;

    // Pasamos la parte de X a una pila nueva
    while(!P_ORG.vacia() && P_ORG.tope() != '&')
    {
        P_INV.push(P_ORG.tope());
        P_ORG.pop();
    }

    // En caso de que no se haya introducido '&'
    if(P_ORG.vacia()) 
    {
        return false;
    }
    else
    {
         P_ORG.pop();
    }
    
    // Ahora comparamos si el otro extremo de la pila es inversa
    while(!P_INV.vacia() && !P_ORG.vacia())
    {

        if(P_ORG.tope() != P_INV.tope())
        {
            return false;
        }
        P_ORG.pop();
        P_INV.pop();
    }
    return P_ORG.vacia() && P_INV.vacia();
}

int main()
{
    /** Explicación:
     * Se crea una función que determina y devuelva si una secuencia de caracteres (a partir de una pila)
     * de entrada es de la forma X&Y, donde X sigue una secuencia ordenada de caracteres e Y es la secuencia
     * inversa, separadas por el carácter '&'.
     **/

    Pila<char> P;
    P.push('A'); P.push('B'); P.push('C'); P.push('D'); 
    P.push('E'); P.push('F'); P.push('&'); P.push('F'); 
    P.push('E'); P.push('D'); P.push('C'); P.push('B');
    P.push('A');
    
    if(XY(P)){ std::cout << "Es correcto." << std::endl; }
    else
    {
        std::cout << "Es Incorrecto." << std::endl;
    }
    
}