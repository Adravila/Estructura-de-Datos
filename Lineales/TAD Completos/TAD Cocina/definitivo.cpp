#include <iostream>
#include "Lista_enla.h"

using namespace std;

struct tMueble
{
    int id, anch, pos;
    tMueble() {}
    tMueble(int id_, int pos_, int anch_) : id(id_), pos(pos_), anch(anch_) {}
};

bool operator == (const tMueble& m1, const tMueble& m2)
{
    return m1.id == m2.id;
}

class Cocina
{
public:
    Cocina(size_t tamaMax);
    void agregarMueble(const tMueble &M);
    bool cabeMueble(const tMueble &M, Lista<tMueble>::posicion &p);
    void eliminarMueble(int i);
    void pegarMueble(int i);
    const tMueble &observadorMueble(int i);
    void imprimirCocina();
    ~Cocina();

private:
    Lista<tMueble> L;
    size_t longitud, current_tam;
    const tMueble vacio;
};

Cocina::Cocina(size_t tamaMax) : longitud(tamaMax), current_tam(0) {}

Cocina::~Cocina()
{
    L = Lista<tMueble>();
    longitud = 0;
    current_tam = 0;
}

bool Cocina::cabeMueble(const tMueble &M, Lista<tMueble>::posicion &p)
{
    if (current_tam + M.anch >= longitud)
    {
        return false;
    }
    if (p == L.fin())
    {
        return true;
        current_tam = M.anch;
    }
    else
    {
        while (p != L.fin())
        {
            if (M.pos < L.elemento(p).pos)
            {
                if (M.pos + M.anch - 1 < L.elemento(p).pos)
                {
                    return true; // Colocar mueble en el extremo izquierdo.
                    current_tam += M.anch;
                }
            }
            else
            {
                if (M.pos >= L.elemento(p).pos && M.pos <= L.elemento(p).pos + L.elemento(p).anch - 1)
                {
                    return false; // Está ocupando espacio;
                }
                if (L.siguiente(p) == L.fin())
                {
                    p = L.siguiente(p);
                    return true; // Colocar mueble en el extremo derecho.
                    current_tam += M.anch;
                }
                else if (M.anch + M.pos - 1 < L.elemento(L.siguiente(p)).pos)
                {
                    p = L.siguiente(p);
                    return true; // Colocar mueble entre dos muebles.
                    current_tam += M.anch;
                }
            }
            p = L.siguiente(p);
        }
    }
    return false;
}

void Cocina::agregarMueble(const tMueble &M)
{
    Lista<tMueble>::posicion p = L.primera();

    // Comprobamos si no existe dicho mueble antes
    p = L.buscar(M);
    if (p != L.fin())
    {
        return;
    }
    // No existe, proceder a insertar un mueble
    p = L.primera();
    if (cabeMueble(M, p))
    {
        L.insertar(M, p);
    }
}

void Cocina::imprimirCocina()
{
    Lista<tMueble>::posicion p;
    p = L.primera();
    int id = 0;
    while (p != L.fin())
    {
        cout << "ID: " << L.elemento(p).id << endl;
        cout << "Posicion: " << L.elemento(p).pos << endl;
        cout << "Anchura: " << L.elemento(p).anch << endl;
        cout << endl;
        id = L.elemento(p).id;
        p = L.siguiente(p);
    }
}

void Cocina::eliminarMueble(int i)
{
    Lista<tMueble>::posicion p;
    p = L.primera();
    int cont = i, id = 0;
    while (p != L.fin() && cont > 0)
    {
        --cont;
        if (cont == 0)
        {
            L.eliminar(p);
            p = L.fin();
        }
        else
        {
            p = L.siguiente(p);
        }
    }
}

void Cocina::pegarMueble(int i)
{
    int cont = i;
    Lista<tMueble>::posicion p;
    p = L.primera();

    if (cont == 1)
    {
        L.elemento(p).pos = 0;
    }
    else
    {

        while (p != L.fin() && cont > 0)
        {
            --cont;
            if (cont == 0)
            {
                if (p != L.primera())
                {
                    L.elemento(p).pos = L.elemento(L.anterior(p)).pos + L.elemento(L.anterior(p)).anch;
                    p = L.fin();
                }
            }
            else
            {
                p = L.siguiente(p);
            }
        }
    }
}

const tMueble &Cocina::observadorMueble(int i)
{
    int cont = i;
    Lista<tMueble>::posicion p;
    p = L.primera();

    while (p != L.fin())
    {
        --cont;
        if (cont == 0)
        {
            return L.elemento(p);
        }
        else
        {
            p = L.siguiente(p);
        }
    }
    return vacio;
}

int main()
{
    Cocina c(11);
    tMueble M1(1, 3, 3), M2(2, 1, 2), M3(3, 6, 3), M4(4, 4, 1), M5(5, 0, 1), M6(6, 9, 1);
    c.agregarMueble(M1);
    c.agregarMueble(M2);
    c.agregarMueble(M6);
    c.pegarMueble(1);
    c.pegarMueble(2);
    c.pegarMueble(3);
    c.eliminarMueble(2);
    c.agregarMueble(M1);
    c.agregarMueble(M2);
    c.agregarMueble(M3);
    c.agregarMueble(M4);
    c.agregarMueble(M5);
    c.agregarMueble(M6);
    c.imprimirCocina();

    cout << "ID del mueble: " << c.observadorMueble(3).id << endl;
}