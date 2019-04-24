#include "Cabeceras/abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Agenda: Haz una agenda usando un Arbol de búsqueda. Utiliza como estructura una
// con los campos telefono y nombre por ejemplo y acuerdate de sobrecargar
// los operandos de comparación de la estructura.

struct Persona
{
    Persona() {}
    Persona(string nom, string telf) : nombre(nom), telefono(telf) {}
    string nombre;
    string telefono;
};

inline bool operator<(const Persona &p1, const Persona &p2)
{
    return p1.nombre < p2.nombre;
}

ostream &operator<<(ostream &os, const Persona &p)
{
    return os << p.nombre;
}

template <typename T>
void imprimirPersona(const T &e, const Abb<T> A)
{
    Abb<Persona> B = A.buscar(e);
    if (!B.vacio())
    {
        Persona P = B.elemento();
        cout << "Nombre: " << P.nombre << endl;
        cout << "Telefono: " << P.telefono << endl;
    }
    else
    {
        cout << "No se ha encontrado la persona" << endl;
    }
}

template <typename T>
void ImprimirArbolBusq(const Abb<T> A)
{
    if (!A.vacio())
    {
        std::cout << A.elemento() << " ";
        ImprimirArbolBusq(A.izqdo());
        ImprimirArbolBusq(A.drcho());
    }
}

int main()
{
    Persona p1("Raúl", "999666444");
    Persona p2("Lorena", "9412415512");
    Persona p3("Andrés", "99523523523");
    Persona p4("Penélope", "9523523561");
    Persona p5("Luis", "912415591");
    Persona p6("Lucas", "9436734721");
    Persona p7("Ernesto", "912414912");
    Persona p8("Julio", "956252532");
    Persona p9("Rosa", "76346356");
    Persona p10("Manuel", "663214525");
    Abb<Persona> P;

    P.insertar(p1);
    P.insertar(p2);
    P.insertar(p3);
    P.insertar(p4);
    P.insertar(p5);
    P.insertar(p6);
    P.insertar(p7);
    P.insertar(p8);
    P.insertar(p9);
    P.insertar(p10);
    std::cout << "Árbol de búsqueda resultante:\n";
    ImprimirArbolBusq(P);
    cout << "\n\nDatos de P5\n"; // Luis
    imprimirPersona(p5, P);
    cout << endl;
}
