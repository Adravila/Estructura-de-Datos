#include <iostream>
#include <assert.h>

using namespace std;

/**
 * Especificar las cadenas finitas sobre un alfabeto dado como parámetro. La especificación debe incluir
 * las siguientes operaciones:
 *  - crear cadena vacía
 *  - añadir un elemento por la izquierda de una cadena
 *  - añadir un elemento por la derecha de una cadena
 *  - concatenar dos cadenas
 *  - calcular la longitud de una cadena
 *  - consultar el elemento más a la izquierda de una cadena
 *  - eliminar el elemento más a la izquierda de una cadena
 *  - consultar el elemento más a la derecha de una cadena
 *  - eliminar el elemento más a la derecha de una cadena
 *  - Comprobar si una cadena es vacía
 *  - Calcular la inversa de una cadena
 */

class Cadena
{
public:
    Cadena();
    void aniadirIzqda(char e);
    void aniadirDrcha(char e);
    void concatenar(Cadena &cad); 
    int calcularLongitud();
    char imprimirIzqdo();
    char imprimirDrcho();
    void eliminarIzqdo();
    void eliminarDrcho();
    bool esCadenaVacia() const;
    bool esta(char e);
    void invertir();
    // Extra
    void imprimirCadena() const;
private:
    char cad_[100];
    size_t tam;
};

Cadena::Cadena() : tam(0) {}


void Cadena::aniadirIzqda(char e)
{
    assert(tam < 100);
    char cad[100];
    cad[0] = e;    

    for(int i = 0; i <= tam; ++i)
    {
        cad[i + 1] = cad_[i];
    }

    ++tam;

    for(int i = 0; i <= tam; i++)
    {
        cad_[i] = cad[i];
    }
}

inline void Cadena::aniadirDrcha(char e)
{
    cad_[tam] = e;
    ++tam;
}

void Cadena::concatenar(Cadena &c)
{
    size_t t = c.tam;

    for (int i = 0; i < t; ++i)
    {
        cad_[tam] = c.cad_[i];
        ++tam;
    }
}

inline bool Cadena::esCadenaVacia() const
{
    return tam == 0;
}

bool Cadena::esta(char e)
{
    bool esta = false;
    for (int i = 0; i < tam && !esta; ++i)
    {
        if (cad_[i] == e)
            esta = true;
    }
    return esta;
}

inline int Cadena::calcularLongitud()
{
    return tam;
}

inline char Cadena::imprimirIzqdo()
{
    return cad_[0];
}

inline char Cadena::imprimirDrcho()
{
    return cad_[tam - 1];
}

inline void Cadena::eliminarDrcho()
{
    assert(tam > 0);
    --tam;
}

inline void Cadena::eliminarIzqdo()
{
    assert(tam > 0);

    for(int i = 0; i < tam; ++i)
    {
        cad_[i] = cad_[i+1];
    }
    --tam;
}

void Cadena::invertir()
{
    assert(tam > 0);
    char cad[100];
    for(int i = 0; i < tam; ++i)
    {
        cad[i] = cad_[tam - i - 1];
    }
    for(int i = 0; i < tam; ++i)
    {
        cad_[i] = cad[i];
    }
}

void Cadena::imprimirCadena() const
{
    for (int i = 0; i <= tam; ++i)
    {
        cout << cad_[i];
    }
}

int main()
{
    Cadena cad1, cad2;
    cad1.aniadirIzqda('h');
    cad1.aniadirIzqda('o');
    cad1.aniadirIzqda('l');
    cad1.aniadirIzqda('a');
    cad1.invertir();
    cad2.aniadirDrcha('a');
    cad2.aniadirDrcha('d');
    cad2.aniadirDrcha('i');
    cad2.aniadirDrcha('o');
    cad2.aniadirDrcha('s');
    cad2.eliminarIzqdo();
    cad1.concatenar(cad2);
    cad1.imprimirCadena();
    cout << cad1.esta('s');
}