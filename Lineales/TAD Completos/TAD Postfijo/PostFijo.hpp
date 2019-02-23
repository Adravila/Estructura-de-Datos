#include <iostream>
#include "Pila_enla.h"
#include "Cola_enla.h"

struct tVariable
{
	tVariable(int operando = 0) : val(operando), op(' ') {}
	tVariable(char operador = ' ') : val(0), op(operador) {}
	char op;
	int val;
};

int calcularPostfijo(const Cola<tVariable>& P)
{
	Pila<tVariable> P_OP;
	Cola<tVariable> C_ORG = P;

	while(!C_ORG.vacia())
	{
		if(C_ORG.frente().op == ' ')
		{
			P_OP.push(C_ORG.frente());
			C_ORG.pop();
		}
		else
		{
			tVariable val_1(0), val_2(0);
			val_1 = P_OP.tope();
			P_OP.pop();
			assert(!P_OP.vacia()); // No se puede operar si no se cumple esto
			val_2 = P_OP.tope();
			P_OP.pop();
			switch(C_ORG.frente().op)
			{
				case '+': P_OP.push(val_2.val + val_1.val); break;
				case '-': P_OP.push(val_2.val - val_1.val); break;
				case '*': P_OP.push(val_2.val * val_1.val); break;
				case '/': P_OP.push(val_2.val / val_1.val); break;
				default: std::cout << "Error, no existe dicho operador" << std::endl;
			}
			C_ORG.pop();
		}
	}
	return P_OP.tope().val;
}
