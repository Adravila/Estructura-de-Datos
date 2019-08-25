#include <iostream>
#include <assert.h>

/**
 * Especificar un tipo de datos para representar figuras como sucesiones de trazos A (arriba), B (abajo)
 * D (derecha), I (izquierda) de longitud unitaria, con al menos las siguientes operaciones:
 *  - girar la figura 90º en sentido horario
 *  - duplicar el tamaño de la figura
 *  - calcular la altura máxima de la figura
 *  - calcular la anchura máxima de la figura
*/

using namespace std;

class Figura
{
public:
    Figura(size_t tamaMax);
    void agregarFigura(char e);
    void girarFigura();
    void duplicarTam();
    int calcularAlturaMax();
    int calcularAnchuraMax();
    bool vacia() const;
    // Extra
    void imprimirFiguras() const;
private:
    char *figuras;
    size_t tam, fin;
};

Figura::Figura(size_t tamaMax) : figuras(new char[tamaMax]),
                                 tam(tamaMax), fin(-1) {}

void Figura::agregarFigura(char e)
{
    assert(e == 'A' || e == 'B' || e == 'D' || e == 'I');
    ++fin;
    figuras[fin] = e;
}

inline bool Figura::vacia() const
{
    return (fin == -1);
}

void Figura::girarFigura()
{
    if (!vacia())
    {
        for (int i = 0; i <= fin; ++i)
        {
            switch (figuras[i])
            {
            case 'A':
                figuras[i] = 'D';
                break;
            case 'D':
                figuras[i] = 'B';
                break;
            case 'B':
                figuras[i] = 'I';
                break;
            case 'I':
                figuras[i] = 'A';
                break;
            }
        }
    }
}

void Figura::duplicarTam()
{
    assert((fin * 2) < tam);
    char f[tam];
    fin = fin * 2;

    for (int i = 0; i <= fin; ++i)
    {
        f[i] = figuras[i / 2];
    }
    for (int i = 0; i <= fin; ++i)
    {
        figuras[i] = f[i];
    }
}

int Figura::calcularAlturaMax()
{
    int cont_arriba = 0;
    int cont_abajo = 0;
    for (int i = 0; i <= fin; i++)
    {
        if (figuras[i] == 'A')
        {
            ++cont_arriba;
        }
        else if (figuras[i] == 'B')
        {
            ++cont_abajo;
        }
    }
    return abs(cont_arriba - cont_abajo) + 1;
}

int Figura::calcularAnchuraMax()
{
    int cont_derecha = 0;
    int cont_izquierda = 0;
    for (int i = 0; i <= fin; i++)
    {
        if (figuras[i] == 'D')
        {
            ++cont_derecha;
        }
        else if (figuras[i] == 'I')
        {
            ++cont_izquierda;
        }
    }
    return abs(cont_derecha - cont_izquierda) + 1;
}

void Figura::imprimirFiguras() const
{
    for (int i = 0; i <= fin; ++i)
    {
        cout << figuras[i] << " ";
    }
    cout << endl;
}

int main()
{
    Figura f(100);
    f.agregarFigura('D');
    f.agregarFigura('A');
    f.agregarFigura('I');
    f.agregarFigura('I');
    f.agregarFigura('B');
    f.agregarFigura('B');
    f.agregarFigura('D');
    f.agregarFigura('D');
    f.agregarFigura('B');
    f.girarFigura();
    f.duplicarTam();
    f.imprimirFiguras();
}