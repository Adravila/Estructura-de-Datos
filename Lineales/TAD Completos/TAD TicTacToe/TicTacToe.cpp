#include <iostream>
#include <assert.h>

using namespace std;

/** ESPECIFICACIÓN DEL TAD TicTacToe 
 *  
 *   - Postcondición: construye una matriz de 3x3 de tipo char, se insertan puntos
 *   que lo consideramos como posiciones vacías.
 *  TicTacToe()
 * 
 *   - Precondición: c debe ser un char con el carácter 'X' o 'O'
 *   - Postcondición: Coloca una pieza indicada en la matriz por 'y' (fil) y 'x' (col)
 *  void colocarPieza(unsigned int y, unsigned int x, char c);
 * 
 *   - Postcondición: Muestra el estado actual del tablero
 *  void mostrarTablero() const;
 * 
 *   - Postcondición: Devuelve el turno del jugador
 *  char jugadorActual() const;
 * 
 *   - Precondición: Las posiciones 'y' y 'x' deben estar dentro de los límites de la matriz
 *   - Postcondición: Devuelve true si la posición es válida, en caso contrario devolverá false
 *  bool posicionValida(unsigned int y, unsigned int x) const
 * 
 *   - Precondición: Las posiciones 'y' y 'x' deben estar dentro de los límites de la matriz
 *   - Postcondición: Devuelve true si el jugador indicado por el parámetro ha ganado la partida,
 *     en caso contrario devolverá false.
 *  bool haGanado(int fil, int col, char turno)
 * 
*/

class TicTacToe
{
public:
    TicTacToe();
    void colocarPieza(unsigned int y, unsigned int x, char c);
    void mostrarTablero() const;
    char jugadorActual() const;
    bool posicionValida(unsigned int y, unsigned int x) const;
    bool haGanado(int fil, int col, char turno);

private:
    char matriz[3][3];
    char player; // O ó X
};

TicTacToe::TicTacToe() : player('X')
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            matriz[i][j] = '.';
        }
    }
}

void TicTacToe::colocarPieza(unsigned int y, unsigned int x, char c)
{
    assert(c == 'X' || c == 'O'); // Validar si es 'X' o 'O' antes de continuar

    if (player != c)
    {
        cout << "Tienes que esperar el próximo turno." << endl;
    }
    if (posicionValida(y, x))
    {
        matriz[y][x] = c;
        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
    }
}

void TicTacToe::mostrarTablero() const
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

inline char TicTacToe::jugadorActual() const
{
    return player;
}

bool TicTacToe::haGanado(int fil, int col, char turno)
{
   bool gana = false;

    // Horizontal
    if(matriz[0][0] == turno && matriz[0][1] == turno && matriz[0][2] == turno) gana = true;
    else if(matriz[1][0] == turno && matriz[1][1] == turno && matriz[1][2] == turno) gana = true;
    else if(matriz[2][0] == turno && matriz[2][1] == turno && matriz[2][2] == turno) gana = true;

    // vertical
    else if(matriz[0][0] == turno && matriz[1][0] == turno && matriz[2][0] == turno) gana = true;
    else if(matriz[0][1] == turno && matriz[1][1] == turno && matriz[2][1] == turno) gana = true;
    else if(matriz[0][2] == turno && matriz[1][2] == turno && matriz[2][2] == turno) gana = true;

    // Diagonal principal
    else if(matriz[0][0] == turno && matriz[1][1] == turno && matriz[1][2] == turno) gana = true;
    // Diagonal inversa
    else if(matriz[2][0] == turno && matriz[2][1] == turno && matriz[2][2] == turno) gana = true;
    return gana;
}

bool TicTacToe::posicionValida(unsigned int y, unsigned int x) const
{
    bool estado = true;
    // Comprobamos si x,y está dentro de los límites del tablero
    if (y >= 0 && y < 3 && x >= 0 && x < 3)
    {
        // Comprobamos si en x,y no hay ninguna ficha colocada
        if (matriz[y][x] == '.')
        {
            estado = true;
        }
        else
        {
            cout << "Ya hay una ficha colocada en el tablero." << endl;
            estado = false;
        }
    }
    else
    {
        cout << "La ficha está fuera de los límites del tablero." << endl;
        estado = false;
    }
    return estado;
}

int main()
{
    TicTacToe t;
    int fil, col;
    char turno = 'X';
    bool gana = false;

    while (!gana)
    {
        cout << "Resultado:\n\n";
        t.mostrarTablero();
        cout << "TURNO DE " << turno << ": " << endl;
        cout << "Elije la casilla a insertar: " << endl;
        cout << "Fila y Columna: ";
        cin >> fil >> col;
        t.colocarPieza(fil, col, turno);
        cout << endl;

        if (t.haGanado(fil, col, turno))
        {
            cout << "¡ HA GANADO EL JUGADOR " << turno << " !" << endl;
            gana = true;
        }
        turno = t.jugadorActual();
    }
}