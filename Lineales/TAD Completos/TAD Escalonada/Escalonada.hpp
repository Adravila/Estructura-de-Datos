#define ESCALONADA
#include <iostream>
#include <cstdlib>
#include "Lista.h"

struct Escalon {
	double cx, cy;
	Escalon(double a, double b) : cx(a), cy(b) {}
};

class Funcion {
public:
	Funcion(double cord);
	void insertar(const Escalon& e);
	void eliminar(const Escalon& e);
	Escalon ver(const Escalon& e);
	Escalon min();
	Escalon max();
	Escalon tras(double w, double z);
	~Funcion();
private:
	Lista<Escalon> L1;
	int saltos;
};

Funcion::Funcion(double cord) {
	typename Lista<Escalon>::posicion x = L1.primera();
	Escalon e;
	L1.insertar(e, x);
	L1.elemento(x).cx = cord;
	L1.elemento(x).cy = 0;
}

void Funcion::insertar(const Escalon& e) {
	typename Lista<Escalon>::posicion x = L1.primera();
	bool encontrado = false;
	while(x != L1.fin() && encontrado == false) {
		if(x == L1.primera() && e.cx < L1.elemento(x).cx) {
			cout << "No existe funcion en el punto." << endl;
			encontrado = true;
		}
		if(e.cx < L1.elemento(x).cx){
			L1.insertar(e, x);
			encontrado = true;
		}
		else if(e.cx == L1.elemento(x).cx) {
				L1.elemento(x).cy = e.cy;
				encontrado = true;
		}
		else if(e.cx > L1.elemento(x).cx) {
			L1.insertar(e, L1.anterior(x));
			encontrado = true;
		}
		else if(L1.siguiente(x) == L1.fin()) {
			L1.insertar(e, L1.siguiente(x));
			encontrado = true;
		}
		x = L1.siguiente(x);
	}
}

void Funcion::eliminar(const Escalon& e) {
typename Lista<Escalon>::posicion x = L1.primera();
	while(x != L1.fin()) {
		if(e.cx == L1.elemento(x).cx)
			L1.eliminar(x);
		else if(e.cx > L1.elemento(x).cx)
			L1.eliminar(L1.anterior(x));
		x = L1.siguiente(x);
	}
}

Escalon Funcion::ver(const Escalon& e) {
	typename Lista<Escalon>::posicion x = L1.primera();
	while(x != L1.fin()) {
		if(L1.elemento(x).cx > e.cx)
			return L1.elemento(L1.anterior(x)).cy;
		else if(L1.siguiente(x) == L1.fin())
			return L1.elemento(x).cy;
		else
			cout << "No existe punto." << endl; 
		x = L1.siguiente(x);
	}
}

Escalon Funcion::min() {
	typename Lista<Escalon>::posicion x = L1.primera();
	double min = L1.elemento(x).cy;
	while(x != L1.fin()) {
		x = L1.siguiente(x);
		if(L1.elemento(x).cy < min)
			min = L1.elemento(x).cy;
	}
	return min;
}

Escalon Funcion::max() {
	typename Lista<Escalon>::posicion x = L1.primera();
	double max = L1.elemento(x).cy;
	while(x != L1.fin()) {
		x = L1.siguiente(x);
		if(L1.elemento(x).cy > max)
			max = L1.elemento(x).cy;
	}
	return max;
}

Escalon Funcion::tras(double w, double z) {
	typename Lista<Escalon>::posicion x = L1.primera();
	while(x != L1.fin()) {
		L1.elemento(x).cx = L1.elemento(x).cx + w;
		L1.elemento(x).cy = L1.elemento(x).cy + z;
		x = L1.siguiente(x);
	}
}

Funcion::~Funcion() {
	L1.~Lista();
}

#endif
