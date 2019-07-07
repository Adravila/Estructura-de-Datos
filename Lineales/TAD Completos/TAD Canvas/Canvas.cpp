#include <iostream>
#include "Pila_enla.h"

using namespace std;

/*
    ESPECIFICACIÓN DEL TAD CANVAS:

     - Postcondición: crea un canvas con las dimensiones NxN (una matriz cuadrada) en la que recibe
      como parámetro una matriz de tipo carácter
    Canvas(char colores[tam][tam])

     - Precondición: x e y debe estar dentro de los límites de la matriz (entre 0 y 8)
     - Postcondición: Selecciona una celda para ser reemplazado por un nuevo color
    void Canvas::pintarCelda(int y, int x, RGB color)

     - Precondición: x e y debe estar dentro de los límites de la matriz (entre 0 y 8)
     - Postcondición: Selecciona una celda, la pinta incluyendo a sus adyacentes de manera recursiva
    void rellenarColor(int x, int y, RGB color);

     - Postcondición: Imprime el estado actual del canvas    
    void mostrarCanvas() const;
 */

typedef char RGB;
const int tam = 9;

struct tNodo
{
    tNodo() {}
    tNodo(RGB color_, int x, int y) : color(color_), fil(x), col(y) {}
    int fil, col;
    RGB color;
};

class Canvas
{
public:
    Canvas(char colores[tam][tam]);
    void pintarCelda(int y, int x, RGB color);
    void rellenarColor(int y, int x, RGB color);
    void mostrarCanvas() const;

private:
    Pila<tNodo> P;
    tNodo matriz[tam][tam];
};

Canvas::Canvas(char colores[tam][tam])
{
    for (int i = 0; i < tam; ++i)
    {
        for (int j = 0; j < tam; ++j)
        {
            matriz[i][j] = tNodo(colores[i][j], i, j);
        }
    }
}

void Canvas::pintarCelda(int y, int x, RGB color)
{
    assert(x < tam && y < tam && x > 0 && y > 0);
    matriz[y][x].color = color;
}

void Canvas::rellenarColor(int y, int x, RGB color)
{
    assert(x < tam && y < tam && x >= 0 && y >= 0);
    RGB color_ = matriz[y][x].color; // antiguo color

    // Comprobamos si el nodo a pintar es del mismo color, evitamos su relleno si es así
    if (color == color_)
    {
        return;
    }

    do
    {
        if (!P.vacia())
        {
            x = P.tope().col;
            y = P.tope().fil;
            P.pop();
        }
        if (y - 1 >= 0 && color_ == matriz[y - 1][x].color) // ARRIBA
        {
            P.push(matriz[y - 1][x]);
        }
        if (x - 1 > 0 && color_ == matriz[y][x - 1].color) // IZQUIERDA
        {
            P.push(matriz[y][x - 1]);
        }
        if (x + 1 < tam && color_ == matriz[y][x + 1].color) // DERECHA
        {
            P.push(matriz[y][x + 1]);
        }
        if (y + 1 <= tam && color_ == matriz[y + 1][x].color) // ABAJO
        {
            P.push(matriz[y + 1][x]);
        }

        matriz[y][x].color = color;

    } while (!P.vacia());
}

void Canvas::mostrarCanvas() const
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cout << matriz[i][j].color << "  ";
        }
        cout << endl;
    }
}

int main()
{
    char colores[tam][tam] = {
        {'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'},
        {'N', 'B', 'B', 'B', 'N', 'B', 'B', 'B', 'N'},
        {'N', 'B', 'B', 'B', 'N', 'B', 'B', 'B', 'N'},
        {'N', 'B', 'B', 'N', 'B', 'B', 'B', 'B', 'N'},
        {'N', 'N', 'N', 'B', 'B', 'B', 'N', 'N', 'N'},
        {'N', 'B', 'B', 'B', 'B', 'N', 'B', 'B', 'N'},
        {'N', 'B', 'B', 'B', 'N', 'B', 'B', 'B', 'N'},
        {'N', 'B', 'B', 'B', 'N', 'B', 'B', 'B', 'N'},
        {'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'}
    };

    Canvas c(colores);
    c.rellenarColor(1, 1, 'R');
    c.rellenarColor(7, 7, 'R');
    c.rellenarColor(4, 4, 'G');
    c.rellenarColor(0, 0, 'Z');
    c.pintarCelda(4, 4, 'O');
    c.mostrarCanvas();
}