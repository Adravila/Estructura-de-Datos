#include <iostream>
#include "Lista_enla.h"
#include <assert.h>

using namespace std;

struct funcion
{
    funcion() {}
    funcion(double x_, double y_ = 0) : x(x_), y(y_) {}
    double x, y;
};

bool operator==(const funcion &a, const funcion &b)
{
    return a.x == b.x;
}

class Escalonada
{
public:
    Escalonada();
    Escalonada(funcion &f);
    void anadirsalto(double x, double y);
    void eliminarEscalon(double x);
    double valorEnUnPunto(double x);
    double valorMin();
    double valorMax();
    void translacion(funcion f, double w, double z);

private:
    Lista<funcion> L;
};

Escalonada::Escalonada() {}

Escalonada::Escalonada(funcion &f)
{
    L.insertar(f, L.primera());
}

void Escalonada::anadirsalto(double x, double y)
{
    funcion salto(x, y);
    bool encontrado = false;
    Lista<funcion>::posicion i = L.buscar(salto);
    if (i != L.fin())
    {
        L.elemento(i).y = salto.y;
    }
    else
    {
        // ¿La nueva coord x es menor que la de la primera función?
        if (salto.x < L.elemento(L.primera()).x)
        {
            L.insertar(salto, L.primera());
            encontrado = true;
        }

        // ¿La nueva coord x es mayor que la de la última función?
        if (salto.x > L.elemento(L.anterior(L.fin())).x)
        {
            L.insertar(salto, L.fin());
            encontrado = true;
        }

        // Si la coord de x es igual que la función
        for (i = L.primera(); i != L.anterior(L.fin()) && !encontrado; i = L.siguiente(i))
        {
            if (salto.x >= L.elemento(i).x && salto.x < L.elemento(L.siguiente(i)).x)
            {
                encontrado = true;
            }
        }
        if (encontrado)
            L.insertar(salto, L.siguiente(i));
    }
}

void Escalonada::eliminarEscalon(double x)
{
    bool encontrado = false;
    funcion salto(x);
    Lista<funcion>::posicion p;
    for (p = L.primera(); !encontrado && p != L.fin(); p = L.siguiente(p))
    {
        if (salto.x >= L.elemento(p).x && salto.x < L.elemento(L.siguiente(p)).x)
        {
            encontrado = true;
        }
    }
    if (encontrado)
    {
        L.eliminar(p);
    }
    else
    {
        if (salto.x >= L.elemento(L.anterior(L.fin())).x)
        {
            L.eliminar(L.anterior(L.fin()));
        }
    }
}

double Escalonada::valorEnUnPunto(double x)
{
    bool encontrado = false;
    funcion salto(x);
    Lista<funcion>::posicion i;
    for (i = L.primera(); i != L.anterior(L.fin()) && !encontrado; i = L.siguiente(i))
    {
        if (salto.x >= L.elemento(i).x && salto.x < L.elemento(L.siguiente(i)).x)
        {
            return L.elemento(i).y;
        }
    }
    return 0;
}

double Escalonada::valorMin()
{
    double min = L.elemento(L.primera()).y;
    for (Lista<funcion>::posicion p = L.siguiente(L.primera()); p != L.fin(); p = L.siguiente(p))
    {
        if (L.elemento(p).y < min)
            min = L.elemento(p).y;
    }
    return min;
}
double Escalonada::valorMax()
{
    double max = L.elemento(L.primera()).y;
    for (Lista<funcion>::posicion p = L.siguiente(L.primera()); p != L.fin(); p = L.siguiente(p))
    {
        if (L.elemento(p).y > max)
            max = L.elemento(p).y;
    }
    return max;
}

void Escalonada::translacion(funcion f, double w, double z)
{
    Lista<funcion>::posicion p = L.buscar(f);
    double x, y;
    if (p != L.fin())
    {
        x = L.elemento(p).x + w;
        y = L.elemento(p).y + z;
        L.eliminar(p);
        anadirsalto(x, y);
    }
}

int main()
{
    funcion f1(2,5), f2(4, 2), f3(5, 3);
    Escalonada e(f1);
    e.anadirsalto(6,6);
}