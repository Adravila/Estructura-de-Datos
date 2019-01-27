#include <iostream>
#include "Pila_enla.h"

struct tVariable
{
	tVariable(int operando = 0) : val(operando), op(' ') {}
	tVariable(char operador = ' ') : val(0), op(operador) {}
	int getOperando() const { return val; }
	char getOperador() const { return op; }
	private:
		char op;
		int val;
};


int calcularPostfijo(const Pila<tVariable>& P)
{
	Pila<tVariable> Pila_OP, Pila_TOTAL;
	int val_1 = 0, val_2 = 0, res = 0;
	bool ope_pendientes = false;
	Pila_TOTAL = P; // Constructor implícito de copia
	while(!Pila_TOTAL.vacia())
	{
		if(Pila_TOTAL.tope().getOperador() != ' ') // Si es un operador
		{
			Pila_OP.push(Pila_TOTAL.tope().getOperador());
			Pila_TOTAL.pop();
		}
		else
		{
			// Para asegurarnos de que existan dos operandos hacemos lo siguiente,
			// para evitar errores en la ejecución.
			if(!ope_pendientes)
			{
				if(val_1 == 0)
				{
					val_1 = Pila_TOTAL.tope().getOperando();
					Pila_TOTAL.pop();
				}
				else
				{
					val_2 = Pila_TOTAL.tope().getOperando();
					Pila_TOTAL.pop();
				}
			}
			else
			{
				val_1 = res;
				val_2 = Pila_TOTAL.tope().getOperando();
				Pila_TOTAL.pop();	
			}
			
			if(val_1 != 0 && val_2 != 0)
			{
				switch(Pila_OP.tope().getOperador())
				{
					case '+' : res = val_2 + val_1; break;
					case '-' : res = val_2 - val_1; break;
					case '*' : res = val_2 * val_1;	break;  
					case '/' : res = val_2 / val_1; break;
				}
				val_1 = 0; val_2 = 0;
				ope_pendientes = true;
				Pila_OP.pop();	
			}
		}
	}
	return res;
}
