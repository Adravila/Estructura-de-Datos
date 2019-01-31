#include <iostream>
#include "Texto.hpp"

int main()
{
    Lista<Lista<char>> LT;
    Lista<char> L1, L2;
    Lista<Lista<char>>::posicion pos_lt;
    Lista<char>::posicion pos_c;

    pos_lt = LT.primera();
    pos_c = L1.primera();
    
    // Insertamos la palabra: El municipl@io        
    L1.insertar('@',pos_c);
        pos_c = L1.siguiente(pos_c);

        L1.insertar('E',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('l',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar(' ',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('m',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('u',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('n',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('i',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('c',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('i',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('p',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('l',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('@',pos_c);
        pos_c = L1.siguiente(pos_c);
        //L1.insertar('@',pos_c);
        //pos_c = L1.siguiente(pos_c);
        L1.insertar('i',pos_c);
        pos_c = L1.siguiente(pos_c);
        L1.insertar('o',pos_c);
        pos_c = L1.siguiente(pos_c);

    LT.insertar(L1,pos_lt);
    pos_lt = LT.siguiente(pos_lt);

    pos_c = L2.primera();
    // Insertamos la palabra: Ligare@s@
        L2.insertar('L',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('i',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('g',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('a',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('r',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('e',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('@',pos_c);
        //pos_c = L2.siguiente(pos_c);
        //L2.insertar('#',pos_c);
        //pos_c = L2.siguiente(pos_c);
        //L2.insertar('#',pos_c);
        //pos_c = L2.siguiente(pos_c);        
        //L2.insertar('#',pos_c);
        //pos_c = L2.siguiente(pos_c);        
        //L2.insertar('#',pos_c);
        //pos_c = L2.siguiente(pos_c);        
        //L2.insertar('#',pos_c);
        //pos_c = L2.siguiente(pos_c);        
        //L2.insertar('#',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('s',pos_c);
        pos_c = L2.siguiente(pos_c);
        L2.insertar('@',pos_c);
    LT.insertar(L2,pos_lt);

    Texto T(LT);
    T.MostrarTexto();
}