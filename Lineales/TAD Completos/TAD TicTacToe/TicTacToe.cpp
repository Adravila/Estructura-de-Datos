#include <iostream>
#include <assert.h>

using namespace std;

template <int M>
class TicTacToe
{
public:
    TicTacToe();
    void colocarPieza(unsigned int x, unsigned int y, char c);
    void mostrarTablero() const;
    char jugadorActual() const;
    bool haGanado(int fil, int col, char turno);
private:
    char matriz[M][M];
    char player;
};

template <int M>
TicTacToe<M>::TicTacToe() : player('X')
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            matriz[i][j] = '.';
        }
    }
}

template <int M>
void TicTacToe<M>::colocarPieza(unsigned int x, unsigned int y, char c)
{
    assert(c == 'X' || c == 'O'); // Validar si es 'X' o 'O' antes de continuar

    if (player != c)
    {
        cout << "Tienes que esperar el próximo turno." << endl;
    }
    else
    {
        // Comprobamos si x,y está dentro de los límites del tablero
        if (x >= 0 && x < M && y >= 0 && y < M)
        {
            // Comprobamos si en x,y no hay ninguna ficha colocada
            if (matriz[x][y] == '.')
            {
                matriz[x][y] = c;
                if (player == 'X')
                {
                    player = 'O';
                }
                else
                {
                    player = 'X';
                }
            }
            else
            {
                cout << "Ya hay una ficha colocada en el tablero." << endl;
            }
        }
        else
        {
            cout << "La ficha está fuera de los límites del tablero." << endl;
        }
    }
}

template <int M>
void TicTacToe<M>::mostrarTablero() const
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template <int M>
inline char TicTacToe<M>::jugadorActual() const
{
    return player;
}

template <int M>
bool TicTacToe<M>::haGanado(int fil, int col, char turno)
{
    int v[4] = {0, 0, 0, 0};
    bool cond[4] = {true, true, true, true};
    char turno_;

    if (turno == 'O')
    {
        turno_ = 'X';
    }
    else if (turno == 'X')
    {
        turno_ = 'O';
    }
    
    for (int i = 0; i < M; ++i)
    {
        if (cond[0] && matriz[fil][i] == turno_) // Horizontal
        {
            cout << turno_;
            cond[0] = false;
            v[0] += 1;
        }
        if (cond[1] && matriz[i][col] == turno_) // Vertical
        {
            cond[1] = false;
            v[1] += 1;
        }
        if (cond[2] && matriz[M - 1][i] == turno_) // Vertical
        {
            cond[2] = false;
            v[2] += 1;
        }
        if (cond[3] && matriz[0][i] == turno_) // Vertical
        {
            cond[3] = false;
            v[3] += 1;
        }
    }

    for (int i = 0; i < M; ++i)
    {
        cout << v[i] << " ";
        if (v[i] == M)
            return true;
    }
    return false;
}

int main()
{
    TicTacToe<3> t;
    int fil, col;
    char turno = 'X';
    bool gana = false;

    while (!gana)
    {
        cout << "Resultado:\n\n";
        t.mostrarTablero();
        cout << endl;
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