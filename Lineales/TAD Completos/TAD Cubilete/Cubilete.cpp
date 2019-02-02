#include <iostream>
#include "Pila_enla.h"

using namespace std;

struct tCubo
{
	int altura;
	int anchura;
	tCubo(int n, int a) : altura(a), anchura(n) {}
};

Pila<tCubo> Ordena(const Pila<tCubo>& P)
{
	Pila<tCubo> Porg, Pnew, Paux;
	Porg = P;

	while(!Porg.vacia())
	{
		if(Porg.tope().altura < 0)
		{
			tCubo c = Porg.tope();
			c.altura *= -1; 
			Porg.pop();
			Porg.push(c);
		}
		if(Pnew.vacia())
		{
			Pnew.push(Porg.tope());
			Porg.pop();
		}
		else if(Pnew.tope().anchura < Porg.tope().anchura)
		{
			Paux.push(Pnew.tope());
			Pnew.pop();
		}
		else
		{
			Pnew.push(Porg.tope());
			Porg.pop();
			while(!Paux.vacia())
			{
				Pnew.push(Paux.tope());
				Paux.pop();
			}
		}
	}
	return Pnew;
}

int main()
{
	Pila<tCubo> P;
	tCubo t1(4,4), t2(9,-5), t3(3,-6), t4(1,4), t5(10,5), t6(20,5), t7(2,-3), t8(7,2);
	P.push(t1);
	P.push(t2);
	P.push(t3);
	P.push(t4);
	P.push(t5);
	P.push(t6);
	P.push(t7);
	P.push(t8);
	
	P = Ordena(P);
	
	while(!P.vacia())
	{
		cout << "Anchura: " << P.tope().anchura << " y altura: " << P.tope().altura << endl;
		P.pop();
	}	
}
