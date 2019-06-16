#include <iostream>
#include "Pila_enla.h"
#include <assert.h>

using namespace std;

typedef int tVagon;

template <typename T>
class Tren
{
public:
    Tren() : P_IZQ(Pila<tVagon>()), P_DCH(Pila<tVagon>()), activo(-1){};
    void desplazarIzq();
    void desplazarDch();
    void eliminarVagon();
    void insertarVagon(const T &v);
    const tVagon &observarVagon() const;
    bool trenVacio() const;
    void MostrarTren();

private:
    Pila<tVagon> P_IZQ, P_DCH;
    tVagon activo;
};

template <typename T>
bool Tren<T>::trenVacio() const
{
    return P_IZQ.vacia() && P_DCH.vacia() && activo == -1;
}

template <typename T>
void Tren<T>::insertarVagon(const T &v)
{
    if (activo != -1)
    {
        P_DCH.push(activo);
    }
    activo = v;
}

template <typename T>
void Tren<T>::eliminarVagon()
{
    if (!P_DCH.vacia())
    {
        activo = P_DCH.tope();
        P_DCH.pop();
    }
    else if (!P_IZQ.vacia())
    {
        activo = P_IZQ.tope();
        P_IZQ.pop();
    }
    else
    {
        activo = -1;
    }
}

template <typename T>
void Tren<T>::desplazarIzq()
{
    if (!P_DCH.vacia())
    {
        P_IZQ.push(activo);
        activo = P_DCH.tope();
        P_DCH.pop();
    }
}

template <typename T>
void Tren<T>::desplazarDch()
{
    if (!P_IZQ.vacia())
    {
        P_DCH.push(activo);
        activo = P_IZQ.tope();
        P_IZQ.pop();
    }
}

template <typename T>
const tVagon &Tren<T>::observarVagon() const
{
    return activo;
}


template <typename tVagon>
void Tren<tVagon>::MostrarTren()
{
    Pila<tVagon> i, d, aux;

    i = P_IZQ;
    d = P_DCH;

    while (!i.vacia())
    {
        aux.push(i.tope());
        i.pop();
    }

    std::cout << " Izq: ";
    while (!aux.vacia())
    {
        std::cout << aux.tope() << " ";
        aux.pop();
    }

    std::cout << "\n Activo: " << activo << std::endl;

    std::cout << " Der: ";
    while (!d.vacia())
    {
        std::cout << d.tope() << " ";
        d.pop();
    }
    std::cout << std::endl;
}

int main()
{
    Tren<tVagon> T;
    tVagon val;
    int op = 0;
    do{
        cout << "Menu Tren" << endl;
        cout << "1. Desplazar a la izquierda" << endl;
        cout << "2. Desplazar a la derecha" << endl;
        cout << "3. Eliminar el vagón activo" << endl;
        cout << "4. Insertar vagón activo" << endl;
        cout << "5. Observar el vagón activo" << endl;
        cout << "6. Tren vacío" << endl;
        cout << " MONITOR " << endl;
        T.MostrarTren();
        cout << "Elegir: ";
        cin >> op;
        switch (op)
        {
            case 1 : T.desplazarIzq(); break;
            case 2 : T.desplazarDch(); break;
            case 3 : T.eliminarVagon(); break;
            case 4 : cout << "Introduzca un vagón: "; cin >> val; T.insertarVagon(val); break;
            case 5 : cout << "Vagón activo: " << T.observarVagon(); break;
            case 6 : cout << "¿Vagón vacío?"; (T.trenVacio()) ? (cout << " Sí") : (cout << " No"); cout << endl;
            case 7 : break;
            default: cout << "No se ha introducido una opción correcta.";
        }
    }while(op != 7);
}