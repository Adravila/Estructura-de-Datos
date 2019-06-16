#include <iostream>
#include "Lista_enla.h"

using namespace std;

typedef char tTrazo;

template <typename T>
class Simbolo
{
public:
	Simbolo();
	void agregarTrazo(const T &e);
	void deshacerTrazos(unsigned int n = 0);
	void simetricaX();
	void simetricaY();
	void simetricaXY();
	void mostrarSimbolo() const;
private:
	Lista<tTrazo> L;
};

template <typename T>
Simbolo<T>::Simbolo() : L(Lista<tTrazo>()) {}

template <typename T>
void Simbolo<T>::agregarTrazo(const T &e)
{
	tTrazo t = toupper(e);
	assert(t == 'I' || t == 'D' || t == 'S' || t == 'B');
	Lista<tTrazo>::posicion p;
	p = L.fin();
	L.insertar(toupper(t), p);
}

template <typename T>
void Simbolo<T>::deshacerTrazos(unsigned int n)
{
	Lista<tTrazo>::posicion p;
	assert(L.primera() != L.fin()); // Debe haber elementos (al menos uno)
	p = L.fin();
	p = L.anterior(p);

	unsigned int cont;

	if (n == 0)
		cont = 1;
	else
		cont = n;

	while (cont > 0 && p != L.primera())
	{
		L.eliminar(p);
		p = L.anterior(p);
		if (p == L.primera())
		{
			L.eliminar(p);
		}
		--cont;
	}
}

template <typename T>
void Simbolo<T>::simetricaX()
{
	Lista<tTrazo>::posicion p;

	p = L.primera();
	while (p != L.fin())
	{
		if (L.elemento(p) == 'I')
		{
			L.elemento(p) = 'D';
		}
		else if (L.elemento(p) == 'D')
		{
			L.elemento(p) == 'I';
		}
		p = L.siguiente(p);
	}
}

template <typename T>
void Simbolo<T>::simetricaY()
{
	Lista<tTrazo>::posicion p;
	p = L.primera();
	while (p != L.fin())
	{
		if (L.elemento(p) == 'S')
		{
			L.elemento(p) = 'B';
		}
		else if (L.elemento(p) == 'B')
		{
			L.elemento(p) = 'S';
		}
		p = L.siguiente(p);
	}
}

template <typename T>
void Simbolo<T>::simetricaXY()
{
	simetricaX();
	simetricaY();
}

template <typename T>
void Simbolo<T>::mostrarSimbolo() const
{
	Lista<tTrazo>::posicion p;
	p = L.primera();
	while (p != L.fin())
	{
		cout << L.elemento(p) << " ";
		p = L.siguiente(p);
	}
	cout << endl;
}

int main()
{
	Simbolo<tTrazo> s1, s2, s3, s4;
	s1.agregarTrazo('I');
	s1.agregarTrazo('b');
	s1.agregarTrazo('B');
	s1.agregarTrazo('d');
	s1.agregarTrazo('s');
	s1.agregarTrazo('I');
	// Realizamos las operaciones para hacer los símbolos simétricos según el eje de abscisas
	s1.mostrarSimbolo();
	s2 = s1;
	s2.simetricaX();
	s2.mostrarSimbolo();
	s3 = s1;
	s3.simetricaY();
	s3.mostrarSimbolo();
	s4 = s1;
	s4.simetricaXY();
	s4.mostrarSimbolo();
	// OK, ahora vamos a eliminar una secuencia de elementos
	// Comprobamos con s4, en princio su resultado es: DSSDBD
	// Vamos a eliminar los 4 últimos trazos
	s4.deshacerTrazos(4);
	// En el que debe quedar como DS
	s4.mostrarSimbolo();
	// Comprobamos con s3, en princio su resultado es: ISSDBI
	// Vamos a eliminar solo un único trazo, se elimina por defecto si no pasamos el parámetro
	s3.deshacerTrazos();
	// En el que debe quedar como ISSDB
	s3.mostrarSimbolo();
}