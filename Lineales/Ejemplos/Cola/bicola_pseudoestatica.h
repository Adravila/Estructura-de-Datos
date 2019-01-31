#ifndef COLA_CIR_H
#define COLA_CIR_H
#include <cassert>

template <typename T> class Cola {
public:
    explicit Cola(size_t TamaMax); // constructor, requiere ctor. T()
    Cola(const Cola<T>& C); // ctor. de copia, requiere ctor. T()
    Cola<T>& operator =(const Cola<T>& C); // asig. colas, req. T()
    bool vacia() const;
    bool llena() const; // Requerida por la implementación
    const T& frente() const;
    void pop();
    void popFin();
    void push(const T& x);
    void pushIni(const T& x);
    ~Cola(); // destructor
private:
    T *elementos; // vector de elementos
    int Lmax; // tamaño del vector
    int inicio, fin; // posiciones de los extremos de la cola
};

// ******************************************** //

template <typename T> 
void Cola<T>::popFin(){
	assert(!vacia());
	fin = (Lmax + fin - 1) % Lmax;
}

template <typename T> 
void Cola<T>::pushIni(const T& x){
	assert(!llena());
	inicio = (Lmax + inicio - 1) % Lmax;
	elementos[inicio] = x;
}

// ******************************************** //

template <typename T>
Cola<T>::Cola(size_t TamaMax) :
    elementos(new T[TamaMax + 1]), // +1 para detectar cola llena
    Lmax(TamaMax + 1),
    inicio(0),
    fin(TamaMax)
{}

template <typename T>
Cola<T>::Cola(const Cola<T>& C) :
    elementos(new T[C.Lmax]),
    Lmax(C.Lmax),
    inicio(C.inicio),
    fin(C.fin)
{
    if (!C.vacia()) // Copiar el vector
        for (int i = inicio; i != (fin + 1) % Lmax; i = (i + 1) % Lmax)
            elementos[i] = C.elementos[i];
}

template <typename T>
Cola<T>& Cola<T>::operator =(const Cola<T>& C)
{
    if (this != &C) { // evitar autoasignación
    // Destruir el vector y crear uno nuevo si es necesario
        if (Lmax != C.Lmax) {
            delete[] elementos;
            Lmax = C.Lmax;
            elementos = new T[Lmax];
        }
        // Copiar el vector
        inicio = C.inicio;
        fin = C.fin;
        if (!C.vacia())
        for (int i = inicio; i != (fin + 1) % Lmax;
        i = (i + 1) % Lmax)
        elementos[i] = C.elementos[i];
    }
    return *this;
}

template <typename T>
inline bool Cola<T>::vacia() const
{
    return ((fin + 1) % Lmax == inicio);
}

template <typename T>
inline bool Cola<T>::llena() const
{
    return ((fin + 2) % Lmax == inicio);
}

template <typename T>
inline const T& Cola<T>::frente() const
{
    assert(!vacia());
    return elementos[inicio];
}

template <typename T>
inline void Cola<T>::pop()
{
    assert(!vacia());
    inicio = (inicio + 1) % Lmax;
}

template <typename T>
inline void Cola<T>::push(const T& x)
{
    assert(!llena());
    fin = (fin + 1) % Lmax;
    elementos[fin] = x;
}

template <typename T>
inline Cola<T>::~Cola()
{
    delete[] elementos;
}

#endif // COLA_CIR_H