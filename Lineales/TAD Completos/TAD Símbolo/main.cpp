#include <iostream>
#include "TAD Simbolo.hpp"

int main()
{
    Simbolo s;
    tTrazo t1 = 'B', t2 = 'D', t3 = 'S', t4 = 'I', t5 = 'I';
    s.AgregarTrazo(t1);
    s.AgregarTrazo(t2);
    s.AgregarTrazo(t3);
    s.AgregarTrazo(t4);
    s.AgregarTrazo(t5);
    s.Simetrica('A');
    s.Simetrica('A');
    s.mostrarSimbolo();
}