#ifndef DICCIONARIO
#define DICCIONARIO
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Lista.h"

struct Traduccion {
    std::string ingles;
    Lista<string> trad;
    palabra(std::string& i, Lista<string>& tr) : ingles(i), trad(tr) {}
};

class Diccionario {
public:
    Diccionario(int plb) : palabras(plb) {}
    void insertar(string& english, string& spanish, size_t n);
    void eliminar(string& english, string& spanish, size_t n);
    Diccionario consultar(string& english);
    ~Diccionario();
private:
    Lista<Traduccion> L1;
    int palabras;
};

void Diccionario::insertar(string& english, string& spanish, size_t n) {
    typename Lista<Traduccion>::posicion x = L1.primera();
    bool encontrado = false;
    while(x != L1.fin() && encontrado == false) {
        if(strcmp(L1.elemento(x).ingles, english, n) == 0)
        L1.elemento(x).trad.insertar(spanish, trad.fin());
        encontrado = true;
        else {
            Traduccion T1;
            strcpy(T1.ingles, english);
            T1.trad.insertar(spanish, trad.fin());
            L1.insertar(T1, x);
            encontrado = true;
        }
        L1.siguiente(x);
    }
}

void Diccionario::eliminar(string& english, string& spanish, size_t n) {
    typename Lista<Traduccion>::posicion x = L1.primera();
    bool encontrado = false;
    while(x != L1.fin() && encontrado == false) {
        if(strcmp(L1.elemento(x).ingles, english, n) == 0) {
            typename Lista<string>::posicion y = L1.elemento(x).trad.buscar(spanish);
            L1.elemento(x).trad.eliminar(y);
            encontrado = true;
        }
    L1.siguiente(x);
    }
}

Diccionario Diciconario::consultar(string& english, size_t n) {
    typename Lista<Traduccion>::posicion x = L1.primera();
    while(x != L1.fin()) {
        if(strcmp(L1.elemento(x).ingles, english, n) == 0)
            return L1.elemento(x);
        L1.siguiente(x);
    }
}

Diccionario::~Diccionario() {
    L1.~Lista();
}

#endif
