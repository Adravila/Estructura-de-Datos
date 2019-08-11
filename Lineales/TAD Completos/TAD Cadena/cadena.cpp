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
 *  - Decidir si una cadena es vacía
 *  - Decidir si un elemento aparece en una cadena
 *  - Decidir si dos cadenas aparece en una cadena
 *  - Calcular la inversa de una cadena
 */

class Cadena
{
public:
    Cadena();
    void aniadirIzqda(char e);
    void aniadirDrcha(char e); // OK
    void concatenar(Cadena &cad); // OK
    int calcularLongitud();       // OK
    char imprimirIzqdo();         // OK
    char imprimirDrcho();         // OK
    void eliminarIzqdo();
    void eliminarDrcho(); // OK
    bool esCadenaVacia() const; // OK
    bool esta(char e);  // OK
    // Extra
    void imprimirCadena() const;
private:
    char cad_[100];
    size_t tam;
};

Cadena::Cadena() : tam(0) {}

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

void Cadena::aniadirIzqda(char e)
{
    char cad[100];
    cad_[tam] = e;

    if (tam == 0)
    {
        cad_[0] = e;
        cout << cad_[0] << endl;
    }
    else
    {
        for (int i = 0; i < tam; ++i)
        {
            cad[i] = cad_[tam - i];
            cout << cad[i];
        }
        cout << endl;
    }
    ++tam;
}

void Cadena::aniadirDrcha(char e)
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
    cad1.aniadirDrcha('h');
    cad1.aniadirDrcha('o');
    cad1.aniadirDrcha('l');
    cad1.aniadirDrcha('a');
    cad2.aniadirDrcha('a');
    cad2.aniadirDrcha('d');
    cad2.aniadirDrcha('i');
    cad2.aniadirDrcha('o');
    cad2.aniadirDrcha('s');
    cad1.concatenar(cad2);
    cad1.imprimirCadena();
    cout << cad1.esta('s');
}