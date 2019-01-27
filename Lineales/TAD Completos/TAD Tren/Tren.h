#ifndef TREN_H_INCLUDED
#define TREN_H_INCLUDED
#include "Pila_enla.h"

struct vagon{
    int n_vagon;
};

vagon vagonVacio{};
// Toda estructura vacía generará sus atributos por defecto,
// en este caso como n_vagon es entero por defecto tendrá 0.

class Tren{
public:
    Tren();
    void insertarVagon(const vagon& v);
    void desplazarIzq();
    void desplazarDer();
    void eliminarVagon();
    bool trenVacio() const;
    const vagon& vagonActivo() const noexcept;
private:
    Pila<vagon>pDer;
    Pila<vagon>pIzq;
};

inline Tren::Tren(){
    Pila<vagon>pDer = Pila<vagon>();
    Pila<vagon>pIzq = Pila<vagon>();
}

inline void Tren::insertarVagon(const vagon& v){ pDer.push(v); }

void Tren::desplazarIzq(){
    if(!pDer.vacia()){
        vagon v_a = pDer.tope();
        pDer.pop();
        if(pDer.vacia())
            pDer.push(v_a); // No se puede desplazar a la izquierda porque es el último vagón activo a la derecha.
        else
            pIzq.push(v_a); // Como hay más vagones a la derecha, el siguiente al actual será el vagón activo.
    }
}

inline void Tren::desplazarDer(){
    if(!pIzq.vacia()){
        pDer.push(pIzq.tope());
        pIzq.pop();
    }
}

inline void Tren::eliminarVagon(){
    if(!pDer.vacia())
        pDer.pop();
    else if(!pIzq.vacia()){
        pDer.push(pIzq.tope());
        pIzq.pop();
    }
}

inline bool Tren::trenVacio() const{
    return pDer.vacia() && pIzq.vacia();
}

inline const vagon& Tren::vagonActivo() const noexcept{
    	if(!pDer.vacia())
            return pDer.tope();
        return vagonVacio;
}

#endif // TREN_H_INCLUDED
