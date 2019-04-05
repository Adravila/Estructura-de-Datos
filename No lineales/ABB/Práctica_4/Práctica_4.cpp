#include "abb.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Bonus

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

template <typename T>
void imprimirPersona(const T &e, const Abb<T> A)
{
    Abb<Persona> B = A.buscar(e);
    if (!A.buscar(e).vacio())
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

// Ejercicio 1
template <typename T>
void EliminarSubarbol(const T &x, Abb<T> &A)
{
    while (!A.buscar(x).vacio())
    {
        if (!A.buscar(x).izqdo().vacio())
        {
            A.eliminar(A.buscar(x).izqdo().elemento());
        }
        else if (!A.buscar(x).drcho().vacio())
        {
            A.eliminar(A.buscar(x).drcho().elemento());
        }
        else
        {
            A.eliminar(A.buscar(x).elemento());
        }
    }
}

// Ejercicio 2

// Imprimir

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

template <typename T>
void ImprimirAbin(typename Abin<T>::nodo n, Abin<T> A)
{
    if (n != Abin<T>::NODO_NULO)
    {
        std::cout << A.elemento(n) << " ";
        ImprimirAbin(A.hijoIzqdoB(n), A);
        ImprimirAbin(A.hijoDrchoB(n), A);
    }
}

int main()
{
    Abb<int> A, B;
    A.insertar(7);
    A.insertar(5);
    A.insertar(12);
    A.insertar(9);
    A.insertar(17);
    A.insertar(8);
    A.insertar(11);
    A.insertar(10);

    // Copiamos para probar el ejercicio 2
    B = A;

    std::cout << "Imprimir árbol: ";
    ImprimirArbolBusq(A);
    std::cout << std::endl;

    // Ejercicio 1: Eliminar subárbol
    EliminarSubarbol(9, A);
    std::cout << "Árbol de búsqueda resultante: ";
    ImprimirArbolBusq(A);
    std::cout << std::endl;

    // Ejercicio 2: Crear Abin a partir del ABB
    Abin<int> C = (Abin<int>)B;

    std::cout << "Árbol binario resultante: ";
    ImprimirAbin(C.raizB(), C);
    std::cout << std::endl;
    // Bonus *************************************

    // Agenda: Haz una agenda usando un Arbol de búsqueda. Utiliza como estructura una
    // con los campos telefono y nombre por ejemplo y acuerdate de sobrecargar
    // los operandos de comparación de la estructura.

    Persona p1("Adrian", "999666444");
    Persona p2("Joaquin", "9412415512");
    Persona p3("Maria", "99523523523");
    Persona p4("Rosa", "9523523561");
    Persona p5("Pedro", "912415591");
    Persona p6("Manuel", "9436734721");
    Persona p7("Raquel", "912414912");
    Persona p8("Julio", "956252532");
    Persona p9("Paco", "76346356");
    Persona p10("Lolo", "663214525");
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
    imprimirPersona(p4, P);
}