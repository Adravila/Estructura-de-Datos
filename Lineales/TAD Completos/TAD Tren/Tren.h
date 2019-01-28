#ifndef TREN_H_INCLUDED
#define TREN_H_INCLUDED
#include "Pila_enla.h"

typedef int tVagon;

template<typename tVagon>
class Tren
{
    public:
        Tren();
        void DesplazarIzq();
        void DesplazarDrch();
        void InsertarVagon(const tVagon& v);
        void EliminarVagon();
        bool TrenVacio() const;
        const tVagon& VagonActivo() const noexcept;
        void MostrarTren(); // Exclusivo
    private:
        Pila<tVagon> P_IZQ, P_DRCH;
        tVagon vagonActivo;
};

template<typename tVagon>
Tren<tVagon>::Tren() : vagonActivo(-1) {}

template<typename tVagon>
void Tren<tVagon>::DesplazarIzq()
{
    if(!P_DRCH.vacia())
    {
        P_IZQ.push(vagonActivo);
        vagonActivo = P_DRCH.tope();
        P_DRCH.pop();
    }
}

template<typename tVagon>
void Tren<tVagon>::DesplazarDrch()
{
    if(!P_IZQ.vacia())
    {
        P_DRCH.push(vagonActivo);
        vagonActivo = P_IZQ.tope();
        P_IZQ.pop();
    }
}

template<typename tVagon>
void Tren<tVagon>::InsertarVagon(const tVagon& v)
{
    if(vagonActivo != -1)
    {
        P_DRCH.push(vagonActivo);
    }
    vagonActivo = v;    
}

template<typename tVagon>
void Tren<tVagon>::EliminarVagon()
{
    if(!P_DRCH.vacia())
    {
        vagonActivo = P_DRCH.tope();
        P_DRCH.pop();
    }
    else if(!P_IZQ.vacia())
    {
        vagonActivo = P_IZQ.tope();
        P_IZQ.pop();  
    }
    else
    {
        vagonActivo = -1;
    }
    
}

template<typename tVagon>
bool Tren<tVagon>::TrenVacio() const
{
    return vagonActivo == -1;
}

template<typename tVagon>
const tVagon& Tren<tVagon>::VagonActivo() const noexcept
{
    return vagonActivo;
}

template<typename tVagon>
void Tren<tVagon>::MostrarTren()
{
	Pila<tVagon> i, d, aux;
	
	i = P_IZQ;
	d = P_DRCH;
	
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
	
	std::cout << "\nActivo: " << vagonActivo << std::endl;
	
	std::cout << "Der: ";
	while(!d.vacia()) 
	{
		std::cout << d.tope() << " ";
		d.pop();
	}
    std::cout << std::endl;
}

#endif // TREN_H_INCLUDED
