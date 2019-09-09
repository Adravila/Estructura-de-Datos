#include <iostream>
#include "Pila_enla.h"
#include "Tren.h"

int main()
{
    Tren<tVagon> T;
    T.InsertarVagon(1);
    T.InsertarVagon(2);
    T.InsertarVagon(3);
    T.InsertarVagon(4);
    T.InsertarVagon(5);
    T.DesplazarIzq();
    T.DesplazarIzq();
    T.DesplazarIzq();
    T.DesplazarDrch();
    //T.EliminarVagon();
    //T.EliminarVagon();
    //T.EliminarVagon();
    //T.EliminarVagon();
    //T.EliminarVagon();

    T.MostrarTren();
}