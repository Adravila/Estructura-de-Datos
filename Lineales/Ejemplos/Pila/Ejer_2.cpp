#include <iostream>
#include "Pila_enla.h"

using namespace std;

bool XY(Pila<char>& P_ORG)
{
    Pila<char> P_INV;

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
        P_INV.pop();
        P_ORG.pop();
    }
    return true;
}

bool determinarSecuencia(const Pila<char>& P)
{   
    Pila<char> P_ORG, P_INV;
    P_ORG = P;

    while(!P_ORG.vacia())
    {
        if(XY(P_ORG)) // Comprueba si la secuencia X&B se cumple
        {
            if(!P_ORG.vacia())
            { 
                if(P_ORG.tope() == '#')           
                    P_ORG.pop();
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    /** Explicación:
     * Se crea una función que determina y devuelva si una secuencia de caracteres (a partir de una pila)
     * de entrada es de la forma A#B#C#D ..., donde A,B,C,D, ... siga de la forma X&Y,
     * que a su vez están separadas por el carácter '#'.
     **/

    Pila<char> P;
    P.push('A'); P.push('B'); P.push('C'); P.push('&'); P.push('C'); P.push('B'); P.push('A'); P.push('#');
    P.push('X'); P.push('Y'); P.push('Z'); P.push('&'); P.push('Z'); P.push('Y'); P.push('X'); P.push('#');
    P.push('H'); P.push('I'); P.push('&'); P.push('I'); P.push('H'); P.push('#');
    P.push('V'); P.push('&'); P.push('V'); 
    
    if(determinarSecuencia(P)){ std::cout << "Es correcto." << std::endl; }
    else
    {
        std::cout << "Es Incorrecto." << std::endl;
    }
    
}