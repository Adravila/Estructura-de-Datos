#include <iostream>
#include "Pila_enla.h"

using namespace std;

void InvertirSerie(Pila<int>& P, int a, int b)
{
    Pila<int> P_IZQ, P_MED, P_DCH;
    bool proceso = false;
    // Modificar valores del rango a y b
    while(!P.vacia())
    {
        if(P.tope() == a && proceso == false)
        {
            while(!P.vacia() && P.tope() != b)
            {
                P_DCH.push(P.tope());
                P.pop();
            }
            P_DCH.push(P.tope());
            // dar la vuelta
            while(!P_DCH.vacia())
            {
                P_MED.push(P_DCH.tope());
                P_DCH.pop();
            }
            P.pop();
            proceso = true; // Evitar invertir elementos para otro rango
        }
        if(proceso == true) // Caso DERECHO
        {
            P_DCH.push(P.tope());
            P.pop();
        }
        else    // Caso Izquierdo
        {
            P_IZQ.push(P.tope());
            P.pop();
        }
    }
    
    // Concatenamos las tres pilas
    while(!P_DCH.vacia())
    {
        P.push(P_DCH.tope());
        P_DCH.pop();
    }
    while(!P_MED.vacia())
    {
        P.push(P_MED.tope());
        P_MED.pop();
    }
    while(!P_IZQ.vacia())
    {
        P.push(P_IZQ.tope());
        P_IZQ.pop();
    }

    // Mostrar resultados
    while(!P.vacia())
    {
        cout << P.tope();
        P.pop();
    }
}

int main()
{
    /** Explicación:
     * Escriba una función que dados dos elementos a y b y una pila, invierta la secuencia delimitada
     * por ambos dentro de ella.
     * Dado que la pila puede tener elementos repetidos, se invertirá la secuencia delimitada por
     * la primera ocurrencia de a y de b.
     * Ejemplos: a=1, b=2
     * Pila original: 4789918679624893210
     * Pila final: 4789926976814893210
     */
        
    // Variables
    Pila<int> P;
    int a,b;

    // Definición de las variables
    P.push(0); P.push(1); P.push(2); P.push(3); P.push(9); P.push(8); P.push(4); P.push(2); 
    P.push(6); P.push(9); P.push(7); P.push(6); P.push(8); P.push(1); P.push(9); P.push(9); 
    P.push(8); P.push(7); P.push(4);

    a = 1; b = 2;

    // Llamada función InvertirSerie
    InvertirSerie(P,a,b);
}