#ifndef SIMBOLO_HPP_INCLUDED
#define SIMBOLO_HPP_INCLUDED
#include <iostream>
#include "Lista_doble.h"

/**
	Vamos a usar el TAD Lista para manipular todos los trazos del símbolo en un orden lineal O(n),
	utilizaremos la representación con celdas doblemente enlazadas, ya que en la operación DeshacerTrazo
	se recorre los elementos de la lista desde el final hasta la primera posición (por lo que al usar esta
	representación el coste las operaciones fin y anterior serán de O(1) en vez de O(n)), 
	además de esto, no será necesario controlar el número de elementos que tendrá en la lista 
	por lo que vamos a utilizar las siguientes operaciones: 
		
		- Lista()
		- void insertar(const T& x, posicion p)
		- void eliminar(posicion p);
		- posicion primera();
		- posicion fin();
		- posicion siguiente(primera p);
		- const T& elemento() const;
		- T& elemento();

	ESPECIFICACIÓN DEL TAD Símbolo

	Postcondición: Crea un constructor de Símbolo vacío
	Simbolo();

	Precondición: Recibe un caracter que sea 'I', 'D', 'S' y 'B'
	Postcondición: Añade un caracter a la lista
	void AgregarTrazo(const char x);

	Precondición: Recibe un entero mayor o igual que cero
	Postcondición: Elimina el número de trazos según el parámetro de tipo entero a usarse
	void DeshacerTrazo(unsigned n = 0);

	Postcondición: Convierte un trazo 'I' o 'D' su inversa
	void SimetricaX(); 

	Postcondición: Convierte un trazo 'S' o 'B' su inversa
	void SimetricaY(); 

	Precondición: Recibe un parámetro que indica el eje de abscisa (X o Y) o ambos ejes (A)
	Postcondición: Devuelve el símbolo simétrico respecto el eje de abscisas
	void Simetrica(char t); 
**/

typedef char tTrazo, tEje;

class Simbolo
{
	public:
		Simbolo();
		void AgregarTrazo(const tTrazo& x);
		void DeshacerTrazo(unsigned n = 0);
		void Simetrica(const tTrazo& t); 

		void mostrarSimbolo(); // Exclusiva 
	private:
		void SimetricaX(); 
		void SimetricaY(); 
		Lista<tTrazo> L;
		Lista<tTrazo>::posicion p;
};

Simbolo::Simbolo(){}

void Simbolo::AgregarTrazo(const tTrazo& x)
{
	p = L.fin();
	if('I' == x || 'D' == x || 'S' == x || 'B' == x)
		L.insertar(x,p);
}

void Simbolo::DeshacerTrazo(unsigned n)
{	
	p = L.fin();
	p = L.anterior(p);

	if(n == 0)
	{
		while(p != L.primera())
		{
			L.eliminar(p);
			p = L.anterior(p);
		}
	}
	else
	{
		while(p != L.primera() && n > 0)
		{
			L.eliminar(p);
			p = L.anterior(p);
			--n;
		}
	}
	L.eliminar(p);
}

void Simbolo::Simetrica(const tEje& t)
{
	p = L.primera();

	while(p != L.fin())
	{
		if(t == 'X' || t == 'A') SimetricaX();
		if(t == 'Y' || t == 'A') SimetricaY();
		p = L.siguiente(p);
	}	
}

void Simbolo::SimetricaX()
{
	if(L.elemento(p) == 'I')
	{
		L.elemento(p) = 'D';
	}
	else if(L.elemento(p) == 'D')
	{
		L.elemento(p) = 'I';
	}
}

void Simbolo::SimetricaY()
{
	if(L.elemento(p) == 'S')
	{
		L.elemento(p) = 'B';
	}
	else if(L.elemento(p) == 'B')
	{
		L.elemento(p) = 'S';
	}
}

void Simbolo::mostrarSimbolo()
{
	p = L.primera();
	while(p != L.fin())
	{
		std::cout << L.elemento(p) << " ";
		p = L.siguiente(p);
	}
}
#endif // SIMBOLO_HPP_INCLUDED
