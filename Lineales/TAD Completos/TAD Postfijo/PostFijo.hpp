#include <iostream>
#include "Pila_enla.h"
#include "Lista_enla.h"
#include <stdlib.h>
#include <cstring>

struct tVariable
{
	explicit tVariable(char var_, int val_) : val(val_), var(var_) {}
	tVariable() {}
	char var;
	int val;
};

int calcularPostfijo(const char *c, const Lista<tVariable> &L)
{
	Pila<char> P_OP;
	Lista<tVariable>::posicion p;
	int cont = 0;
	int val_1 = 0, val_2 = 0;

	// Para contar cuantos operandos existen
	for (int i = 0; i < (unsigned)strlen(c); ++i)
	{
		cont++;
	}

	while (cont >= 0)
	{
		if (c[cont] == '+' || c[cont] == '-' || c[cont] == '*' || c[cont] == '/')
		{
			P_OP.push(c[cont]);
			--cont;
		}
		else
		{
			p = L.primera();
			while (p != L.fin()) // Para buscar los valores que corresponden
			{
				if (c[cont] == L.elemento(p).var)
				{
					if (val_2 == 0)
					{
						val_2 = L.elemento(p).val;
					}
					else
					{
						val_1 = L.elemento(p).val;
					}
					p = L.fin();
				}
				else
				{
					p = L.siguiente(p);
				}
			}
			--cont;
		}
		if(val_1 != 0 && val_2 != 0)
		{
			switch (P_OP.tope())
			{
			case '+':
				val_2 = val_1 + val_2;
				break;
			case '-':
				val_2 = val_1 - val_2;
				break;
			case '*':
				val_2 = val_1 * val_2;
				break;
			case '/':
				val_2 = val_1 / val_2;
				break;
			default:
				std::cout << "Error, no existe dicho operador" << std::endl;
			}
			P_OP.pop();
			val_1 = 0;
		}
	}

	return val_2;
}
