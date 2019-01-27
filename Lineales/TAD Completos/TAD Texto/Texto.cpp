#include <iostream>
#include "lista_enla.hpp"
#include <string>
/**
	ESPECIFICACIÓN DEL TAD TEXTO:

	void Texto::mostrarTexto()
	Postcondición: Muestra el mensaje contenido del texto.

	void Texto::limpiarTexto(linea& l)
	Precondición: Recibe linea una lista de tipo char.
	Postcondición: Si hay un '@' se elimina el carácter anterior a éste, si hay un '#' se eliminará la línea antes de '#'. 
				   Se debe cumplir también las condiciones que indica en el enunciado para su realización.

	void Texto::insertarLinea(string cad)
	Precondición: Recibe una cadena de caracteres
	Postcondición: Inserta la cadena de caracteres a la línea del texto.

**/

using namespace std;

typedef Lista<char> linea;

class Texto{
public:
	void mostrarTexto();
	void limpiarTexto(linea& l);
	void insertarLinea(string cad);
private:
	Lista<linea> T;
};

void Texto::insertarLinea(string cad){
	linea l;
	linea::posicion p = l.primera();
	Lista<linea>::posicion q = T.fin();
	for(int i = 0; i < cad.length(); ++i){
		l.insertar(cad[i],p);
		p = l.siguiente(p);
	}
	limpiarTexto(l);
	T.insertar(l,q);
}

void Texto::limpiarTexto(linea& l){
	linea::posicion p = l.fin();
	p = l.anterior(p);
	while(p != l.primera()){
		if(l.elemento(p) == '#'){
			l.eliminar(p);
			p = l.anterior(p); 	
			while(l.elemento(p) == '#')
				p = l.anterior(p);
			while(p != l.primera()){
				l.eliminar(p);	
				p = l.anterior(p);
			}	
			l.eliminar(p);			
		}
		if(l.elemento(p) == '@'){
			l.eliminar(p);
			p = l.anterior(p);
			if(l.elemento(p) != '@')
				l.eliminar(p);
			else
				while(l.elemento(p) == '@')
					p = l.anterior(p);
		}
		if(p != l.primera())
			p = l.anterior(p);
	}
}

void Texto::mostrarTexto(){
	Lista<linea>::posicion p = T.primera();
	while(p != T.fin()){
		linea l = T.elemento(p);
		linea::posicion q = l.primera();
		while(q != l.fin()){
			std::cout << T.elemento(p).elemento(q);
			q = l.siguiente(q);
		}
		std::cout << std::endl;
		p = T.siguiente(p);
	}
}

int main(){
	Texto T;
	T.insertarLinea("@BORRAR ESTO POR FAVOR###Holañ@ que tañ@l vamos esos 4 arrobas @@@@@");
	T.insertarLinea("Ligare@s@");
	T.insertarLinea("El municipl@io");
	T.mostrarTexto();
}
