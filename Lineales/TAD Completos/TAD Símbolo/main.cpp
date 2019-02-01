#include "TAD Simbolo.hpp"
#include <iostream>

using namespace std;

int main()
{
    Simbolo s;
    tTrazo t1 = 'D', t2 = 'S', t3 = 'B', t4 = 'I';
    s.AgregarTrazo(t1);
    s.AgregarTrazo(t2);
    s.AgregarTrazo(t3);
    s.AgregarTrazo(t4);
    s.Simetrica('A');
    s.mostrarSimbolo();
}
