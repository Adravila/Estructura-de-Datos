#include "Lista_doble.h"
#include <iostream>
using namespace std;

typedef char tTrazo;

class Simbolo
{
public:
    explicit Simbolo();
    void agregarTrazo(const tTrazo &t);
    void deshacerNTrazos(unsigned int n);
    void simetricoX();
    void simetricoY();
    void simetricoXY();
    void mostrarSimbolo() const;
private:
    Lista<tTrazo> L;
};

Simbolo::Simbolo() : L{Lista<tTrazo>{}} {}

void Simbolo::agregarTrazo(const tTrazo &t)
{
    assert(t == 'S' || t == 'B' || t == 'I' || t == 'D');
    L.insertar(t, L.fin());
}

void Simbolo::deshacerNTrazos(unsigned int n)
{
    Lista<tTrazo>::posicion pos = L.fin();
    unsigned int i = n;
    bool todo = false;

    if (i == 0)
    {
        todo = true;
    }

    if (pos != L.primera())
    {
        pos = L.anterior(pos);
    }

    while((pos != L.primera()) && (i > 0 || todo))
    {
        --i;
        L.eliminar(pos);
        if (pos != L.primera())
        {
            pos = L.anterior(pos);
        }
    }
}

void Simbolo::simetricoX()
{
    Lista<tTrazo>::posicion pos = L.primera();

    while(pos != L.fin())
    {
        if(L.elemento(pos) == 'I')
        {
            L.elemento(pos) = 'D';
        }
        else if(L.elemento(pos) == 'D')
        {
            L.elemento(pos) = 'I';
        }
        pos = L.siguiente(pos);
    }
}

void Simbolo::simetricoY()
{
    Lista<tTrazo>::posicion pos = L.primera();

    while(pos != L.fin())
    {
        if(L.elemento(pos) == 'S')
        {
            L.elemento(pos) = 'B';
        }
        else if(L.elemento(pos) == 'B')
        {
            L.elemento(pos) = 'S';
        }
        pos = L.siguiente(pos);
    }
}

void Simbolo::simetricoXY()
{
    simetricoX();
    simetricoY();
}

void Simbolo::mostrarSimbolo() const
{
    Lista<tTrazo>::posicion pos = L.primera();    
    while(pos != L.fin())
    {
        cout << L.elemento(pos) << " ";
        pos = L.siguiente(pos);
    }
    cout << endl;
}


int main()
{
    Simbolo s;
    tTrazo t1 = 'D', t2 = 'S', t3 = 'B', t4 = 'I';
    s.agregarTrazo(t1);
    s.agregarTrazo(t2);
    s.agregarTrazo(t3);
    s.agregarTrazo(t4);
    s.simetricoY();
    s.mostrarSimbolo();
}
