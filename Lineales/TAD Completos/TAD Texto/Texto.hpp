#include <iostream>
#include "Lista_doble.h"

class Texto
{
	public:
		Texto(const Lista<Lista<char>>& nuevoTexto);
		void MostrarTexto();
	private:
		Lista<Lista<char>> texto;
};

Texto::Texto(const Lista<Lista<char>>& nuevoTexto)
{
	texto = nuevoTexto;
}

void Texto::MostrarTexto()
{
	Lista<char>::posicion posFrase;
    Lista<Lista<char>>::posicion posTexto;
	Lista<char> frase;
	bool procesar, arrobaSeguido;

	posTexto = texto.primera();
	
	while(posTexto != texto.fin())
    {
		frase = texto.elemento(posTexto);
		posFrase = frase.primera();
		procesar = true;
		arrobaSeguido = false;

		while(posFrase != frase.fin())
        {
			if(frase.elemento(posFrase) == '#') // '#' indica el borrado de la línea completa.
            {
				if(!procesar)
				{
					std::cout << "#";	// Si aparecen varias igual, sólo aparecerá al final de la línea.
				}
				procesar = false;	
				posFrase = frase.siguiente(posFrase);	
			}
			else if(frase.elemento(posFrase) == '@' && !arrobaSeguido)	// '@' indica el borrado del carácter anterior
            {
				if(posFrase != frase.primera())
                {
                    frase.eliminar(posFrase);
                    posFrase = frase.anterior(posFrase);
					arrobaSeguido = true;
				}
				frase.eliminar(posFrase);
			}
			// En caso de que aparezcan varios consecutivos, sólo tiene un efecto el primero; 
			// el resto aunque se almacena, se ignora.
            else if(arrobaSeguido && frase.elemento(posFrase) == '@') 
            {
                posFrase = frase.siguiente(posFrase);
            }
			else
            {
				arrobaSeguido = false;
				posFrase = frase.siguiente(posFrase);
			}
		}
		
		if(procesar)
        {
			posFrase = frase.primera();
			while(posFrase != frase.fin())
            {
				std::cout << frase.elemento(posFrase);
				posFrase = frase.siguiente(posFrase);
			}
			std::cout << std::endl;
			posTexto = texto.siguiente(posTexto);
		}
		else
		{
			texto.eliminar(posTexto);
			std::cout << std::endl;
		}
				
	}
}