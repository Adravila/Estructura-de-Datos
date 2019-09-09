#include <iostream>
#include "Pila_enla.h"

typedef int tVagon;

class Tren
{
public:
    Tren() {}
    void desplazarIzqda();
    void desplazarDrcha();
    void eliminarVagonActivo();
    void insertarVagonActivo(const tVagon v);
    const tVagon observarVagonActivo() const;
    bool trenVacio() const;
    void MostrarTren();
private:
    Pila<tVagon> P_IZQ, P_DER;
};

void Tren::MostrarTren()
{
	Pila<tVagon> i, d, aux;
	
	i = P_IZQ;
	d = P_DER;
	
	while(!i.vacia())
	{
		aux.push(i.tope());
		i.pop();
	}
	
	std::cout << "Izq: ";
	while(!aux.vacia()) 
	{
		std::cout << aux.tope() << " ";
		aux.pop();
	}
	
	std::cout << "\nActivo: ";
    P_DER.vacia() ? std::cout << "0\n" : std::cout << P_DER.tope() << std::endl;
	
	std::cout << "Der: ";
	while(!d.vacia()) 
	{
		std::cout << d.tope() << " ";
		d.pop();
	}
    std::cout << std::endl;
}

void Tren::desplazarIzqda()
{
    if (!P_DER.vacia())
    {
        P_IZQ.push(P_DER.tope());
        P_DER.pop();
    }
}

void Tren::desplazarDrcha()
{
    if (!P_IZQ.vacia())
    {
        P_DER.push(P_IZQ.tope());
        P_IZQ.pop();
    }
}

void Tren::eliminarVagonActivo()
{
    if(!P_DER.vacia())
    {
        P_DER.pop();
    }
    if(P_DER.vacia() && !P_IZQ.vacia())
    {
        P_DER.push(P_IZQ.tope());
        P_IZQ.pop();
    }
}

void Tren::insertarVagonActivo(const tVagon v)
{
    P_DER.push(v);
}

const tVagon Tren::observarVagonActivo() const
{
    return P_DER.tope();
}

bool Tren::trenVacio() const
{
    return P_IZQ.vacia() && P_DER.vacia();
}

int main()
{
    Tren T;
    T.insertarVagonActivo(1);
    T.insertarVagonActivo(2);
    T.insertarVagonActivo(3);
    T.insertarVagonActivo(4);
    T.insertarVagonActivo(5);
    T.desplazarIzqda();
    T.desplazarIzqda();
    T.desplazarIzqda();
    T.desplazarDrcha();
    //T.eliminarVagonActivo();
    //T.eliminarVagonActivo();
    //T.eliminarVagonActivo();

    T.MostrarTren();
}