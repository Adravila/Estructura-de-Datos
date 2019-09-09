#include "PostFijo.hpp"
#include "Pila_enla.h"
#include "Lista_enla.h"
#include <iostream>
#include <map>

using namespace std;

int calcularPostfijo(const char* c, map<char,int>& m)
{
    Pila<char> P_ORG, P_OP;
    int var1 = 0, var2 = 0, res = 0;

    // Convertir cadena de caracteres en una Pila
    for(int i = 0; c[i] != '\0'; ++i)
    {
        P_ORG.push(c[i]);
    }

    // Vamos a operar
    while(!P_ORG.vacia())
    {
        if(P_ORG.tope() == '+' || P_ORG.tope() == '-' || P_ORG.tope() == '*' || P_ORG.tope() == '/')
        {
            P_OP.push(P_ORG.tope());
        }
        else // Asignar valores y calcular
        {
            if(var1 == 0)
            {
                var1 = m.find(P_ORG.tope())->second;
            }
            else if(var2 == 0)
            {
                var2 = m.find(P_ORG.tope())->second;
            }
            if(var1 != 0 && var2 != 0 && !P_OP.vacia())  // Calculamos
            {
                char op = P_OP.tope();
                P_OP.pop();

                switch(op)
                {
                    case '+': res = var2 + var1; break;
                    case '-': res = var2 - var1; break;
                    case '*': res = var2 * var1; break;
                    case '/': res = var2 / var1; break;
                }
                var1 = res;
                var2 = 0;
            }
        }
        P_ORG.pop();
    }
    return res;
}

int main()
{
    const char *c1 = "ABC*+", *c2 = "CAB+*", *c3 = "CBA-/", *c4 = "CBA-/";
    map<char, int> m;
    m.insert(make_pair('A',3));
    m.insert(make_pair('B',5));
    m.insert(make_pair('C',6));
    m.insert(make_pair('D',5));

    // ABC*+= 33 --> A+(BC)
    cout << "ABC*+ = " << calcularPostfijo(c1,m) << endl;

    // CAB+*=48 --> C*(A+B)
    cout << "CAB+* = " << calcularPostfijo(c2,m) << endl;

    // CBA-/=3 --> (B-A) / C
    cout << "CBA-/ = " << calcularPostfijo(c3,m) << endl;

    // AC-BD/+=2 --> A-C+B/D  AC-B+/D
    cout << "AC-BD/+ = " << calcularPostfijo(c4,m) << endl;

}
