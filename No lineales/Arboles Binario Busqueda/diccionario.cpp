#include "Cabeceras/abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Diccionario: Haz un diccionario usando un Arbol de búsqueda. Utiliza como estructura una
// con los campos español y zuelandes por ejemplo y acuerdate de sobrecargar
// los operandos de comparación de la estructura.

struct Palabra
{
    Palabra() {}
    Palabra(string esp, string zue) : espaniol(esp), zuelandes(zue) {}
    string espaniol;
    string zuelandes;
};

inline bool operator<(const Palabra &p1, const Palabra &p2)
{
    return p1.espaniol < p2.espaniol;
}

ostream &operator<<(ostream &os, const Palabra &p)
{
    return os << p.espaniol;
}

class Diccionario
{
    public:
        Diccionario() {}
        void insertarPalabra(const Palabra &pal);
        void EliminarPalabra(const Palabra &pal);
        void cambiarPalabra(Palabra &pal, string esp_ep);
        string buscarPalabra(const Palabra &pal);
        void ImprimirPalabras(const Palabra &e);    // Exclusivo
    private:
        Abb<Palabra> A;
};

void Diccionario::insertarPalabra(const Palabra &pal)
{
    A.insertar(pal);
}

void Diccionario::EliminarPalabra(const Palabra &pal)
{
    if (!A.buscar(pal).vacio())
    {
        A.eliminar(A.buscar(pal).elemento());
    }
}

void Diccionario::cambiarPalabra(Palabra &pal, string pal_esp)
{
    if (!A.buscar(pal).vacio())
    {
        A.eliminar(pal);
        pal.espaniol = pal_esp;
        A.insertar(pal);
    }
}

string Diccionario::buscarPalabra(const Palabra &pal)
{
    if (!A.buscar(pal).vacio())
    {
        return A.buscar(pal).elemento().zuelandes;
    }
    else
        return "Palabra no encontrada";
}

void Diccionario::ImprimirPalabras(const Palabra &e)
{
    Abb<Palabra> B = A.buscar(e);
    if (!B.vacio())
    {
        cout << "Español: " << B.elemento().espaniol << endl;
        cout << "Zuelandes: " << B.elemento().zuelandes << endl;
    }
    else
    {
        cout << "No se ha encontrado la palabra" << endl;
    }
}

int main()
{
    Palabra p1("Aprobar", "Suspender");
    Palabra p2("Triunfo", "Desastre");
    Palabra p3("Victoria", "Derrota");
    Palabra p4("EDNL", "SUSPENSO CON MAYÚSCULAS");
    Palabra p5("AEED", "SUSPENSO CON MAYÚSCULAS VERSIÓN 2");
    Palabra p6("PCTR", "Ni lo quieras saber");
    Palabra p7("Hola", "Adiós");
    Palabra p8("Hoy no", "Mañana");
    Palabra p9("Sí", "No");
    Palabra p10("España", "Zuelandia");
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
    D.insertarPalabra(p10);
    D.cambiarPalabra(p10, "Nueva Palabra");
    D.ImprimirPalabras(p10);
    D.ImprimirPalabras(p4);
    D.ImprimirPalabras(p6);
    D.EliminarPalabra(p7);
    D.ImprimirPalabras(p7);
}
