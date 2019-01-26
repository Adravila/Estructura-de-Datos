#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED
#include "lista_enla.h"
#include <iostream>
using namespace std;

class Texto{
	public:
		Texto(const Lista<Lista<char>>& nuevoTexto);
		void MostrarTexto();
	private:
		Lista<Lista<char>> texto;
};

Texto::Texto(const Lista<Lista<char>>& nuevoTexto){
	texto = nuevoTexto;
}

void Texto::MostrarTexto(){
	Lista<char>::posicion posTexto, posFrase;
	Lista<char> frase;
	bool procesar, arrobaSeguido;
	
	posTexto = texto.primera();
	
	while(posTexto != texto.fin()){
		frase = texto.elemento(pos);
		posFrase = frase.primera();
		procesar = true;
		arrobaSeguido = false;
		
		while(posFrase != frase.fin()){
			if(frase.elemento(posFrase) == '#'){
				texto.eliminar(posTexto);
				procesar = false;				
			}
			else if(frase.elemento(posFrase) == '@'){
				if(!arrobaSeguido){
					frase.eliminar(frase.anterior(posFrase));
					arrobaSeguido = true;
				}
				frase.eliminar(posFrase);
			}
			else{
				arrobaSeguido = false;
				posFrase = frase.siguiente(posFrase);
			}
		}
		
		if(procesar){
			posFrase = frase.primera();
		
			while(posFrase != frase.fin()){
				cout << frase.elemento(posFrase);
				posFrase = frase.siguiente(posFrase);
			}
			
			cout << endl;
			posTexto = texto.siguiente(posTexto);
		}				
	}
}
#endif // TEXTO_H_INCLUDED
