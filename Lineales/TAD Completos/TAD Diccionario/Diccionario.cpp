#include <iostream>
#include "Lista_enla.h"
#include <string>

/**
ESPECIFICACIÓN DEL TAD DICCIONARIO
void Diccionario::insertarTraduccionESPtoENG(string eng, string esp)
Postcondición: Inserta la traducción de una palabra español al inglés. Si no existe la palabra en inglés se le agrega.

void Diccionario::eliminarTraduccionESPtoENG(string eng, string esp)
Postcondición: Elimina la traducción de una palabra español al inglés. Si no existe la palabra no se hace nada.

void Diccionario::consultarTraduccionENG(string trad)
Postcondición: Muestra las palabras traducidas que contiene la palabra en inglés al español.
**/

using namespace std;

struct Palabra{
	Palabra(string pal = "") : english(pal) {}
	string english;
	Lista<string> Spanish;
};

class Diccionario{
public:
	void insertarTraduccionESPtoENG(string eng, string esp);
	void eliminarTraduccionESPtoENG(string eng, string esp);
	void consultarTraduccionENG(string trad);
private:
	Lista<Palabra> L;
};


void Diccionario::insertarTraduccionESPtoENG(string eng, string esp){
	Lista<Palabra>::posicion pos = L.primera();
	bool encontrado = false;

	while(pos != L.fin()){
		if(L.elemento(pos).english == eng){
			Lista<string>::posicion pos_p = L.elemento(pos).Spanish.fin();
			L.elemento(pos).Spanish.insertar(esp,pos_p);
			pos = L.fin();
			encontrado = true;
		}
	}
	if(encontrado == false){
		Palabra pal(eng);
		Lista<string>::posicion p = pal.Spanish.fin();
		pal.Spanish.insertar(esp,p);
		L.insertar(pal,pos);
	}
}

void Diccionario::eliminarTraduccionESPtoENG(string eng, string esp){
	Lista<Palabra>::posicion pos = L.primera();

	while(pos != L.fin()){
		if(L.elemento(pos).english == eng){
			Lista<string>::posicion pos_p = L.elemento(pos).Spanish.primera();
			while(pos_p != L.elemento(pos).Spanish.fin()){
				if(L.elemento(pos).Spanish.elemento(pos_p) == esp){
					L.elemento(pos).Spanish.eliminar(pos_p);
					pos_p = L.elemento(pos).Spanish.fin();
				}
				else
					pos_p = L.elemento(pos).Spanish.siguiente(pos_p);
			}
		}
		pos = L.siguiente(pos);
	}
}

void Diccionario::consultarTraduccionENG(string trad){
	Lista<Palabra>::posicion pos = L.primera();
	while(pos != L.fin()){
		if(L.elemento(pos).english == trad){
			cout << "La palabra en inglés '" << trad << "' se traduce en español: ";
			Lista<string>::posicion pos_p = L.elemento(pos).Spanish.primera();
			while(pos_p != L.elemento(pos).Spanish.fin()){
				cout << L.elemento(pos).Spanish.elemento(pos_p) << " ";
				pos_p = L.elemento(pos).Spanish.siguiente(pos_p);
			}
			cout << endl;
			pos = L.fin();
		}
	}
}

int main(){
	Palabra free("Free");
	Diccionario D;
	D.insertarTraduccionESPtoENG("Free","Gratis");
	D.insertarTraduccionESPtoENG("Free","Libre");
	D.insertarTraduccionESPtoENG("Free","Casa");
	D.eliminarTraduccionESPtoENG("Free","Casa");
	D.consultarTraduccionENG("Free");
}
