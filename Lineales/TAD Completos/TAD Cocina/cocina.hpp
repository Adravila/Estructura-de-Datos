#include <iostream>
#include "Lista_vec.h"

static int cont;

class tMueble
{
    public:
        // Constructor
        tMueble(int ubicacion, int anchura) : id_(cont), ubicacion_(ubicacion), anchura_(anchura) 
        { 
            cont += 1; // ID contador
        }
        // Constructor predeterminado
        tMueble(){}
        int ubicacion() const { return ubicacion_; }
        int& ubicacion() { return ubicacion_; } // Modificador
        int anchura() const { return anchura_; }
        int id() const{ return id_; }
    private:
        int id_, ubicacion_, anchura_;
};

class Cocina
{
    public:
        Cocina(size_t n);
        bool posicionPermitida(const tMueble& m, Lista<tMueble>::posicion p) const;
        void insertar(const tMueble& m);
        void eliminar(int i); // Elimina el mueble i-ésimo
        tMueble obtenerMueble(int i) const; // Devuelve el mueble i-ésimo
        void moverMueble(int i); // Mueve el mueble i-ésimo hacia la izquierda
        void pintar() const; // Pinta en consola una representación de la cocina
    private:
        Lista<tMueble>::posicion longitud;
        Lista<tMueble> muebles;
};

Cocina::Cocina(size_t n) : muebles(n), longitud(n)
{ 
    assert(n > 0);
    tMueble vacio;
    Lista<tMueble>::posicion pos;
    pos = muebles.primera();
    while(pos != longitud)
    {
        muebles.insertar(vacio,pos);
        pos = muebles.siguiente(pos);
    }
}

bool Cocina::posicionPermitida(const tMueble& m, Lista<tMueble>::posicion p) const
{
    int anchura = m.anchura();
    if(m.id() == 0) // Comprobamos si cabe en la posición inicial
    {
        while(anchura != 0)
        {
           if(m.id() != 0) // En caso de que encuentre otro mueble, no cabe en dicha posición
           {
               return false;
           }
           --anchura;
        }
        return true;
    }
}

void Cocina::insertar(const tMueble& m)
{
    Lista<tMueble>::posicion pos;
    pos = muebles.primera();
    
    while(pos != muebles.fin())
    {
        assert(posicionPermitida(m,pos));
        int anchura = m.anchura();
        while(anchura != 0)
        {
            muebles.insertar(m,pos);
            pos = muebles.siguiente(pos);
            --anchura;
        }
        pos = muebles.siguiente(pos);
    }
}

void Cocina::pintar() const
{
    Lista<tMueble>::posicion pos;
    pos = muebles.primera();
    while(pos != muebles.fin())
    {
        std::cout << muebles.elemento(pos).id();
        pos = muebles.siguiente(pos);
    }
}