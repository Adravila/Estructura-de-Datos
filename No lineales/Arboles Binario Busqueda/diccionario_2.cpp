#include "Cabeceras/abb.hpp"
#include "Cabeceras/Pila_enla.h"
#include <algorithm>
#include <iostream>
#include <string>

// Diccionario: Haz un diccionario usando un Arbol de búsqueda. Utiliza como estructura una
// con los campos español e inglés por ejemplo y acuerdate de sobrecargar
// los operandos de comparación de la estructura.

using namespace std;

struct tPalabra
{
    string esp, eng;
    tPalabra(){};
    tPalabra(string esp_, string eng_) : esp(esp_), eng(eng_) {}
};

bool operator<(const tPalabra &p1, const tPalabra &p2)
{
    return p1.esp < p2.esp;
}

ostream &operator<<(ostream &os, const tPalabra &p)
{
    return os << p.esp;
}

class Diccionario
{
public:
    Diccionario() {}
    void consultarPalabra(const tPalabra &e);
    void eliminarPalabra(const tPalabra &e);
    void insertarPalabra(const tPalabra &e);
    void modificarPalabraESP(tPalabra &pal, string esp);
    void modificarPalabraENG(tPalabra &pal, string eng);
    string buscarPalabraESP(string e);
    void imprimirPalabras(const tPalabra &e);

private:
    Abb<tPalabra> A;
};

void Diccionario::imprimirPalabras(const tPalabra &e)
{
    Abb<tPalabra> B = A.buscar(e);
    if (!B.vacio())
    {
        cout << "Español: " << B.elemento().esp << endl;
        cout << "Inglés: " << B.elemento().eng << endl;
    }
    else
    {
        cout << "No se ha encontrado la palabra" << endl;
    }
}

string Diccionario::buscarPalabraESP(string e)
{
    tPalabra p(e,e);

    if(!A.buscar(p).vacio())
    {
        return A.buscar(p).elemento().esp;
    }
    else
    {
        return "nulo";
    }
}

void Diccionario::consultarPalabra(const tPalabra &e)
{
    Abb<tPalabra> B = A.buscar(e);
    if (!B.vacio())
    {
        cout << "Esp: " << B.elemento().esp << endl;
        cout << "Eng: " << B.elemento().eng << endl;
    }
    else
    {
        cout << "La palabra no está registrada en el diccionario." << endl;
    }
}

void Diccionario::eliminarPalabra(const tPalabra &e)
{
    if (!A.buscar(e).vacio())
    {
        A.eliminar(e);
    }
    else
    {
        cout << "No se ha encontrado la palabra a eliminar" << endl;
    }
}

void Diccionario::insertarPalabra(const tPalabra &e)
{
    if (A.buscar(e).vacio())
    {
        A.insertar(e);
    }
    else
    {
        cout << "Ya existe esa palabra en el diccionario." << endl;
    }
}

void Diccionario::modificarPalabraESP(tPalabra &pal, string esp)
{
    if (!A.buscar(pal).vacio())
    {
        pal.esp = esp;
        A.eliminar(pal);
        A.insertar(pal);
    }
    else
    {
        cout << "No se ha encontrado la palabra a modificar." << endl;
    }
}

void Diccionario::modificarPalabraENG(tPalabra &pal, string eng)
{
    if (!A.buscar(pal).vacio())
    {
        pal.eng = eng;
        A.eliminar(pal);
        A.insertar(pal);
    }
    else
    {
        cout << "No se ha encontrado la palabra a modificar." << endl;
    }
}

int main()
{
    tPalabra p1("Ratón", "Mouse"),
        p2("Coche", "Car"),
        p3("Pez", "Fish"),
        p4("Agua", "Water"),
        p5("Manzana", "Apple"),
        p6("Habitación", "Room"),
        p7("Ordenador", "Computer"),
        p8("Pan", "Bread"),
        p9("Comida", "Food");

    Diccionario D;
    D.insertarPalabra(p1);
    D.insertarPalabra(p2);
    D.insertarPalabra(p3);
    D.insertarPalabra(p4);
    D.insertarPalabra(p5);
    D.insertarPalabra(p6);
    D.insertarPalabra(p7);
    D.insertarPalabra(p8);
    D.insertarPalabra(p9);

    D.modificarPalabraESP(p5, "Tomate");
    D.modificarPalabraENG(p5, "Tomatoe");
    D.consultarPalabra(p5);
    D.insertarPalabra(p9);

    cout << "Pan se traduce como: " << D.buscarPalabraESP("Pan") << endl;
}