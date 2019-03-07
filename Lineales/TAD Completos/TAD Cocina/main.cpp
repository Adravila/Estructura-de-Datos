#include <iostream>
#include "cocina.hpp"

int main()
{
    Cocina c(10);
    tMueble m1(1,2), m2(2,3), m3(2,5), m4(3,5);
    c.insertar(m1);
    c.insertar(m2);
    c.insertar(m3);
    c.insertar(m4);
    c.pintar();
}