#include <iostream>
#include "cola_vec.hpp"
#include "pila_vec.hpp"
#include <vector>
#include <algorithm>

using namespace std;

void rellenarCola(Cola<int>& c, vector<int>v)
{  	
	for(auto it = v.begin(); it != v.end(); ++it)
	{
		c.push(*it);
		cout << " " << *it;
	}
	cout << "\n";
}

void mostrarCola(Cola<int>& c)
{
	Cola<int> c_aux = c;

	while(!c_aux.vacia())
	{
		cout << " " << c_aux.frente();
		c_aux.pop();
	}
	cout << "\n";
}

int main()
{
	int N = 19;
	vector<int> v = {4,7,8,9,9,1,8,6,7,9,6,2,4,8,9,3,2,1,0};

	Cola<int> C(N), C_aux(N);
	Pila<int> P(N);

	rellenarCola(C,v);

	int a = 1, b = 2;
	bool encontrado = false, terminado = false;
	int cont = 0;

	while(!C.vacia())
	{
		if(C.frente() == a && !encontrado)
		{
			while(C.frente() != b && !C.vacia())
			{
				P.push(C.frente());
				C.pop();
			}
			P.push(C.frente());
			C.pop();
			encontrado = true;
		}
		else
		{
			C_aux.push(C.frente());
			C.pop();
			if(!encontrado) ++cont;
		}
	}

	int i = 0;

	while(!C_aux.vacia())
	{
		if(i == cont && !P.vacia())
		{
			while(!P.vacia())
			{
				C.push(P.tope());
				P.pop();
			}
		}
		else
		{
			C.push(C_aux.frente());
			C_aux.pop();
		}
		++i;
	}

	mostrarCola(C);
}