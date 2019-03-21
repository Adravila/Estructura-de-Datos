#include <iostream>

template <typename T>
class Abin
{
  public:
    typedef int nodo; // índice de la matriz entre 0 y maxNodos - 1
    static const nodo NODO_NULO;
    explicit Abin(size_t maxNodos, const T &e_nulo = T()); // constructor
    void insertarRaizB(const T &e);
    void insertarHijoIzqdoB(nodo n, const T &e);
    void insertarHijoDrchoB(nodo n, const T &e);
    void eliminarHijoIzqdoB(nodo n);
    void eliminarHijoDrchoB(nodo n);
    ~Abin(); // destructor
    bool arbolVacioB() const;
    void eliminarRaizB();
    const T &elemento(nodo n) const; // acceso a elto, lectura
    T &elemento(nodo n);             // acceso a elto, lectura/escritura
    nodo raizB() const;
    nodo padreB(nodo n) const;
    nodo hijoIzqdoB(nodo n) const;
    nodo hijoDrchoB(nodo n) const;
    Abin(const Abin<T> &a);               // ctor. de copia
    Abin<T> &operator=(const Abin<T> &a); //asignación de árboles
  private:
    T *nodos;
    int maxNodos; // tamaño del vector
    T ELTO_NULO;  // marca celdas vacías
    int profundidad();
};

template <typename T>
Abin<T>::Abin(size_t maxNodos, const T &e_nulo) : nodos(new T[maxNodos]),
                                                  maxNodos(maxNodos),
                                                  ELTO_NULO(e_nulo)
{
    // marcar todas las celdas libres
    for (nodo n = 0; n <= maxNodos - 1; n++)
        nodos[n] = ELTO_NULO;
}

template <typename T>
int Abin<T>::profundidad(typename AbinVec<T>::nodo n)
{
    return profundidadRec(n, 0, maxNodos - 1);
}

template <typename T>
int Abin<T>::profundidadRec(typename AbinVec<T>::nodo n, int i, int j)
{
    if (i <= j)
    {
        if (n < (i + j) / 2)
        {
            return 1 + profundidadRec(n, i, (i + j) / 2 - 1);
        }
        else if (n > (i + j) / 2)
        {
            return 1 + profundidadRec(n, (i + j) / 2 + 1, j);
        }
    }
    else
    {
        return 0;
    }
}

template <typename T>
void Abin<T>::insertarRaizB(const T &e)
{
    size_t pos = (maxNodos - 1) / 2;
    assert(nodos[pos] == ELTO_NULO); // árbol vacío
    nodos[pos] = e;
}

template <typename T>
void Abin<T>::insertarHijoIzqdoB(Abin<T>::nodo n, const T &e)
{
    assert(n >= 0 && n <= maxNodos - 1); // nodo válido
    assert(nodos[n] != ELTO_NULO);      // nodo del árbol

    size_t pos = n - (maxNodos + 1) / pow(2, profundidad(n) + 2);

    assert(nodos[pos] == ELTO_NULO); // n no tiene hijo izqdo.
    nodos[pos] = e;
}

template <typename T>
void Abin<T>::insertarHijoDrchoB(Abin<T>::nodo n, const T &e)
{
    assert(n >= 0 && n <= maxNodos - 1); // nodo válido
    assert(nodos[n] != ELTO_NULO);      // nodo del árbol

    size_t pos = n + (maxNodos + 1) / pow(2, profundidad(n) + 2);

    assert(nodos[pos] == ELTO_NULO); // n no tiene hijo izqdo.
    nodos[pos] = e;
}

template <typename T> // ******
inline typename Abin<T>::nodo Abin<T>::padreB(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1);                                                // nodo válido
    assert(nodos[n] != ELTO_NULO);                                                      // nodo del árbol
    if (n % (N + 1) / pow(2, profundidad() - 1) == (N + 1) / pow(2, profundidad() + 1)) // nodo n es hijo izquierdo de su padre
    {
        return n + (N + 1) / pow(2, profundidad() + 1);
    }
    else // nodo n es hijo derecho de su padre
    {
        return n - (N + 1) / pow(2, profundidad() + 1);
    }
}

template <typename T>
void Abin<T>::eliminarHijoIzqdoB(Abin<T>::nodo n)
{
    assert(n >= 0 && n < maxNodos - 1); // nodo válido

    size_t pos_hizq = n - (maxNodos + 1) / pow(2, profundidad(n) + 2);
    size_t pos_hder = n + (maxNodos + 1) / pow(2, profundidad(n) + 2);

    assert(nodos[pos_hizq] == ELTO_NULO && nodos[pos_hder] == ELTO_NULO); // nodo n es hoja
    nodos[n] = ELTO_NULO;
}

template <typename T>
void Abin<T>::eliminarHijoDrchoB(Abin<T>::nodo n)
{
    assert(n >= 0 && n < maxNodos - 1); // nodo válido

    size_t pos_hizq = n - (maxNodos + 1) / pow(2, profundidad(n) + 2);
    size_t pos_hder = n + (maxNodos + 1) / pow(2, profundidad(n) + 2);

    assert(nodos[pos_hizq] == ELTO_NULO && nodos[pos_hder] == ELTO_NULO); // nodo n es hoja
    nodos[n] = ELTO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarRaizB()
{
    size_t pos = (maxNodos - 2) / 2;
    assert(nodos[pos] == ELTO_NULO && nodos[pos] == ELTO_NULO); // nodo n es hoja
    nodos[n] = ELTO_NULO;
}

template <typename T>
inline const T &Abin<T>::elemento(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1); // nodo válido
    assert(nodos[n] != ELTO_NULO);       // nodo del árbol
    return nodos[n];
}

template <typename T>
inline T &Abin<T>::elemento(Abin<T>::nodo n)
{
    assert(n >= 0 && n <= maxNodos - 1); // nodo válido
    assert(nodos[n] != ELTO_NULO);       // nodo del árbol
    return nodos[n];
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raizB() const
{
    size_t pos = (maxNodos - 2) / 2;
    return (nodos[pos] == ELTO_NULO) ? NODO_NULO : 0;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::hijoIzqdoB(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1);              // nodo válido
    assert(nodos[n] != ELTO_NULO);                    // nodo del árbol
    return (n + (N + 1) / pow(2, profundidad() + 1)); //****
}

template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoDrchoB(Abin<T>::nodo n) const
{
    assert(n >= 0 && n <= maxNodos - 1);              // nodo válido
    assert(nodos[n] != ELTO_NULO);                    // nodo del árbol
    return (n - (N + 1) / pow(2, profundidad() + 1)); //****
}
