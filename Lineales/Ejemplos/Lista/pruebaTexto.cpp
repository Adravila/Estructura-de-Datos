#include <iostream>
#include "Lista_enla.h"
#include <cstddef>
#include <cstring>

using namespace std;

struct tFrase
{
    tFrase() {}
    tFrase(const char *f)
    {
        int n = strlen(f);
        Lista<char>::posicion p;
        p = L_frase.primera();

        for (int i = 0; i < n; ++i)
        {
            L_frase.insertar(f[i], p);
            p = L_frase.siguiente(p);
        }
    }
    Lista<char> L_frase;
};

template <typename T>
class Texto
{
public:
    Texto();
    void mostrarTexto();
    void agregarFrase(const T &e);

private:
    Lista<tFrase> L_texto;
};

template <typename T>
Texto<T>::Texto() : L_texto(Lista<tFrase>()) {}

template <typename T>
void Texto<T>::agregarFrase(const T &e)
{
    Lista<tFrase>::posicion p;
    p = L_texto.fin();
    L_texto.insertar(e, p);
}

template <typename T>
void Texto<T>::mostrarTexto()
{
    Lista<tFrase>::posicion p;
    Lista<char>::posicion q;
    assert(p != L_texto.fin()); // Precondición: Hay elementos en la lista del Texto
    p = L_texto.primera();

    // Variables para acciones con @ y #
    bool arrobaSeguido, almuadillaEncontrada, imprimir;
    int cont;

    while (p != L_texto.fin())
    {
        // Definir dentro de la iteración de la lista de texto
        Lista<char> &F = L_texto.elemento(p).L_frase;
        arrobaSeguido = false;
        almuadillaEncontrada = false;
        imprimir = true;
        cont = 0;
        q = F.primera();

        while (q != F.fin())
        {
            // En el caso de operar con # entonces...
            if (F.elemento(q) == '#')
            {
                almuadillaEncontrada = true;
                ++cont;
            }

            // En el caso de operar con @ entonces...
            else if (F.elemento(q) == '@')
            {
                if (!arrobaSeguido)
                {
                    F.eliminar(q); // Elimina @
                    if (q != F.primera())
                    {
                        arrobaSeguido = true; // @ encontrado, se tiene en cuenta del siguiente
                        q = F.anterior(q);
                        F.eliminar(q); // Elimina el caracter anterior al @ borrado
                    }
                }
            }
            else
            {
                arrobaSeguido = false;
            }
            q = F.siguiente(q);
        }

        // En caso de que se haya encontrado #s
        if (almuadillaEncontrada)
        {
            L_texto.eliminar(p);
            tFrase frase_nueva;
            L_texto.insertar(frase_nueva, p);
            Lista<char> &F = L_texto.elemento(p).L_frase;

            q = F.primera();
            while (cont - 1 > 0)
            {
                F.insertar('#', q);
                --cont;
            } 
        }
        
        if (imprimir)
        {
            Lista<char> &F = L_texto.elemento(p).L_frase;
            q = F.primera();
            while (q != F.fin())
            {
                cout << F.elemento(q);
                q = F.siguiente(q);
            }
            cout << endl;
        }
        p = L_texto.siguiente(p);
    }
}

int main()
{
    tFrase f1("El municipl@io"),
        f2("Ligare@s@ "),
        f3("Hola, que tax@@@@l estamos"),
        f4("Hola, que# taa@l #estamos");

    Texto<tFrase> t;
    t.agregarFrase(f1);
    t.agregarFrase(f2);
    t.agregarFrase(f3);
    t.agregarFrase(f4);

    t.mostrarTexto();
}