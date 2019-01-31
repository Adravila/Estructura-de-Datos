#include <iostream>
#include "pilavec.h"

const int num = 8;

using namespace std;

Pila<int> ordena(Pila<int>& P)
{
	Pila<int> aux(num), bien(num);
	int n = 0;
	
	while(!P.vacia())
	{
		n = P.tope();
		P.pop();
		while(!P.vacia())
		{
			if(P.tope() < n)
			{
				aux.push(n);
				n = P.tope();
				P.pop();
			}
			else
			{
				aux.push(P.tope());
				P.pop();
			}
		}
		
		bien.push(n);

		n = aux.tope();
		aux.pop();
	 	while(!aux.vacia())
		{
			if(aux.tope() < n)
			{
				P.push(n);
				n = aux.tope();
				aux.pop();
			}
			else
			{
				P.push(aux.tope());
				aux.pop();
			}
		}
		bien.push(n);	
	}
	
	while(!bien.vacia())
	{
		P.push(bien.tope());
		bien.pop();
	}
	
	return P;	
}	

int main()
{
	Pila<int> P(num);
	P.push(4);
	P.push(9);
	P.push(3);
	P.push(1);
	P.push(10);
	P.push(20);
	P.push(2);
	P.push(7);
	
	P = ordena(P);
	
	while(!P.vacia())
	{
		cout << P.tope() << endl;
		P.pop();
	}	
}
