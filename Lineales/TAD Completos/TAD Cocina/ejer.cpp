#include <iostream>
#include "Lista_Ord.h"

using namespace std;

struct tMueble
{
    tMueble(int id_ = 0, int pos_ = 0, int tam_ = 0) : id(id_), pos(pos_), tam(tam_) {}
    int id, pos, tam;
};

// Operador para la lista ordenada
bool operator<=(const tMueble &m1, const tMueble &m2)
{
    return m1.pos <= m2.pos;
}

class Cocina
{
public:
    Cocina(size_t tamMax);
    void agregarMueble(const tMueble &m);
    bool cabeMueble(const tMueble &m, typename Lista<tMueble>::posicion &p) const;
    const tMueble &observarMueble(int i) const;
    void moverMueble(int i);
    void eliminarMueble(int i); // Orden 1
    void imprimirCocina();      // Extra
private:
    Lista<tMueble> L;
    size_t longitud;
};

Cocina::Cocina(size_t tamMax) : longitud(tamMax) {}

void Cocina::imprimirCocina()
{
    Lista<tMueble>::posicion p;
    p = L.primera();
    while (p != L.fin())
    {
        cout << "ID: " << L.elemento(p).id << endl;
        cout << "Pos: " << L.elemento(p).pos << endl;
        cout << "Anchura: " << L.elemento(p).tam << endl;
        cout << endl;
        p = L.siguiente(p);
    }
}

void Cocina::agregarMueble(const tMueble &m)
{
    Lista<tMueble>::posicion p;
    p = L.primera();

    assert(m.pos + m.tam - 1 < longitud);

    if (p == L.fin())
    {
        L.inser_Ord(m);
    }
    else
    {
        while (p != L.fin())
        {
            if (cabeMueble(m, p))
            {
                L.inser_Ord(m);
                p = L.fin();
            }
            else
            {
                if (p != L.fin())
                {
                    p = L.siguiente(p);
                }
            }
        }
    }
}

inline bool Cocina::cabeMueble(const tMueble &m, typename Lista<tMueble>::posicion &p) const
{
    bool cabe = true;

    if (m.pos <= L.elemento(p).pos) // Está detrás
    {
        if (m.pos + m.tam - 1 >= L.elemento(p).pos || L.elemento(p).pos + L.elemento(p).tam - 1 <= m.pos) // Obstaculiza detrás
        {
            cabe = false;
            p = L.fin();
        }
    }
    else
    {
        if (L.siguiente(p) != L.fin())
        {
            cabe = false;
        }
    }
    return cabe;
}

const tMueble &Cocina::observarMueble(int i) const
{
    Lista<tMueble>::posicion p, p_aux;
    int cont = i;
    p = L.primera();

    while (p != L.fin() && cont >= 0)
    {
        p_aux = p;
        p = L.siguiente(p);
        --cont;
    }

    assert(p_aux != L.fin());
    // Si existe un mueble, entonces lo devuelve.
    return L.elemento(p_aux);
}

void Cocina::moverMueble(int i)
{
    Lista<tMueble>::posicion p, p_aux;
    int cont = i;
    p = L.primera();

    // Si es el primer mueble
    if (p == L.fin() || cont == 0)
    {
        L.elemento(p).pos = 0;
    }
    else
    {
        while (cont != 0 && p != L.fin())
        {
            p = L.siguiente(p);
            --cont;
        }
        if (p != L.primera() && p != L.fin())
        {
            p_aux = L.anterior(p);
            L.elemento(p).pos = L.elemento(p_aux).pos + L.elemento(p_aux).tam;
        }
        assert(p != L.fin());
    }
}

void Cocina::eliminarMueble(int i)
{
    Lista<tMueble>::posicion p, p_aux;
    int cont = i;
    p = L.primera();

    while (p != L.fin() && cont >= 0)
    {
        p_aux = p;
        p = L.siguiente(p);
        --cont;
    }

    assert(p != L.fin());
    // Si existe un mueble, entonces lo devuelve.
    L.eliminar(p_aux);
}

int main()
{
    Cocina c(10);
    tMueble m1(1, 3, 2), m2(2, 3, 2), m3(3, 9, 1), m4(4, 8, 1), m5(5, 0, 1);
    tMueble m6(6, 8, 1), m7(7, 1, 2), m8(8,9,1);

    c.agregarMueble(m1);
    c.agregarMueble(m3);
    c.agregarMueble(m4);
    c.agregarMueble(m5);
    c.agregarMueble(m2);
    c.eliminarMueble(2);

    c.moverMueble(2);

    c.agregarMueble(m6);
    c.agregarMueble(m7);

    c.moverMueble(2);
    c.moverMueble(3);

    c.agregarMueble(m8);

    c.moverMueble(4);
    c.moverMueble(5);

    c.eliminarMueble(0);
    c.eliminarMueble(0);
    c.eliminarMueble(0);
    c.eliminarMueble(0);

    c.moverMueble(1);
    c.moverMueble(0);
    c.imprimirCocina();

    int i = 1;
    cout << "El mueble: " << c.observarMueble(i).id << endl;
    cout << "En la posición: " << c.observarMueble(i).pos << endl;
    cout << "Con tamaño: " << c.observarMueble(i).tam << endl;


    return 0;
}
