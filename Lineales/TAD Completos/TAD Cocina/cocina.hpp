#ifndef COCINA_H
#define COCINA_H
#include <iostream>
#include "listaDinamica.h"

class Mueble {
public:
    Mueble(int posicion=0, int anchura=0) : posicion_(posicion), anchura_(anchura) {} // Constructor
    int posicion() const { return posicion_; }
    int& posicion() { return posicion_; } // Modificador
    int anchura() const { return anchura_; }
private:
    int posicion_,
        anchura_;
};

class Cocina {
public:
    Cocina(int longitud) : longitud_(longitud) {} // Constructor
    bool posicionPermitida(int posicion, int anchura) const;
    void insertar(const Mueble& m);
    void eliminar(int i); // Elimina el mueble i-ésimo
    Mueble obtenerMueble(int i) const; // Devuelve el mueble i-ésimo
    void moverMueble(int i); // Mueve el mueble i-ésimo hacia la izquierda
    void pintar() const; // Pinta en consola una representación de la cocina
    ~Cocina();
private:
    int longitud_;
    Lista<Mueble> muebles;
};

bool Cocina::posicionPermitida(int pos, int anch) const {
    typename Lista<Mueble>::posicion p;
    Mueble actual;

    p = muebles.primera();
    while(p!=muebles.fin()) { // Recorremos todos los muebles
        actual = muebles.elemento(p); // Uno de los muebles
        if(!(pos+anch < actual.posicion() || pos > actual.posicion()+actual.anchura())) // Está NEGADO. Si la posición no es valida para alguno de los muebles devuelve falso.
            return false;
        p = muebles.siguiente(p);
    }
    return true;
}

void Cocina::insertar(const Mueble& m) {
    typename Lista<Mueble>::posicion p;
    Mueble actual;
    bool posicion;

    if(posicionPermitida(m.posicion(), m.anchura())){ // Comprobamos que la posicion es válida primero
        p = muebles.primera();
        posicion = false;
        while(p!=muebles.fin() && !posicion){ // Recorremos hasta encontrar la posicion adecuada o la última
            actual = muebles.elemento(p); // Uno de los muebles
            if(m.posicion() < actual.posicion()) { // Encontramos un mueble posterior al nuestro, ocuparemos ese lugar
                posicion = true; // true para no seguir buscando
            }
            else{
                p = muebles.siguiente(p);
            }
        }
        // Si no hay ningun mueble no entra en el while y ocupa la posición primera
        muebles.insertar(m, p); // Se inserta en la posición que encontramos
    }
    else
        std::cout << "Posicion no permitida." << std::endl;
}

void Cocina::eliminar(int i) {
    typename Lista<Mueble>::posicion p;
    int indice;

    p = muebles.primera();
    indice = 0;
    while(indice < i && p!=muebles.fin()){ // Vamos moviendonos tantas posiciones como indique i
        p = muebles.siguiente(p);
        ++indice;
    }

    if(indice == i){ // Si hemos encontrado el mueble se elimina, si no, no hace nada.
        muebles.eliminar(p);
    }
}

Mueble Cocina::obtenerMueble(int i) const {
    typename Lista<Mueble>::posicion p;
    int indice;

    p = muebles.primera();
    indice = 0;
    while(indice < i && p!=muebles.fin()){ // Buscamos el mueble en la posicion i
        p = muebles.siguiente(p);
        ++indice;
    }
    return muebles.elemento(p); // Devuelve el último mueble si no lo encuentra...
}

void Cocina::moverMueble(int i) {
    typename Lista<Mueble>::posicion p;
    int indice;
    Mueble anterior, actual;

    p = muebles.primera();

    if(i>0){ // Si el mueble no es el primero
        indice = 0;
        while(indice < i && p!=muebles.fin()){ // Buscamos la posicion i-ésima
            p = muebles.siguiente(p);
            ++indice;
        }
        if(indice == i){ // Si encontramos el mueble
            anterior = muebles.elemento(muebles.anterior(p)); // El que está a su izquierda
            muebles.elemento(p).posicion() = anterior.posicion()+anterior.anchura(); // Hacemos coincidir los extremos
        }
    }
    else{
        muebles.elemento(p).posicion() = 0; // Movemos el primer mueble hasta la izquierda
    }
}

void Cocina::pintar() const {
    typename Lista<Mueble>::posicion p;
    Mueble actual;
    int raya;
    int tam;

    p = muebles.primera();
    raya = 0;
    while(p != muebles.fin()){
        actual = muebles.elemento(p);
        while(raya<actual.posicion()) {
            std::cout << raya;
            ++raya;
        }
        tam = 0;
        while(tam < actual.anchura()){
            std::cout << "m";
            ++tam;
            ++raya;
        }
        p = muebles.siguiente(p);
    }
    while(raya<= this->longitud_){
        std::cout << raya;
        ++raya;
    }
    std::cout << std::endl << "-----------------------" << std::endl;
    p = muebles.primera();
    int i= 1;
    while(p!=muebles.fin()){
        actual = muebles.elemento(p);
        std::cout << i << ") Poscion: " << actual.posicion() << " Anchura: " << actual.anchura() << std::endl;
        p = muebles.siguiente(p);
        ++i;
    }
}

Cocina::~Cocina(){
    muebles.~Lista();
}

#endif
