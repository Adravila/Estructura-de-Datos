#include <iostream>
#include "cola_vec.hpp"
#include "pila_vec.hpp"

using namespace std;

bool sonIsomorficas(Pila<int>p, Cola<int>c, int N)
{
	int cont = 0;

	// Creamos una cola para almacenar elementos de las posiciones pares de la pila
	Pila<int> p_aux(N);
	
	for(int i = 1; i <= N; ++i)
	{
		if(!p.vacia())
		{
			if(i % 2 == 0)
			{
				p_aux.push(p.tope());
				++cont;
			}
			p.pop();
		}
	}

	// Comprobamos si es isomórfica
	for(int i = 1; i <= cont; ++i)
	{
		if(!p_aux.vacia() && !c.vacia())
		{
			if(i % 2 == 1)
			{
				if(p_aux.tope() != c.frente())
				{
					return false;
				}
				p_aux.pop();
				c.pop();
			}
			else
				c.pop();
		}
		else
			return false;
	}

	return true;
}

int main()
{
	int N = 10;

	// Creamos una pila y una cola para que sean isomórficas
	Pila<int> p(N);
	for(int i = 1; i <= N; ++i)
		p.push(i);
	Cola<int> c(N);
	for(int i = 1; i <= N; ++i)
		c.push(i);
	cout << "Es isomorfica: ";
	if(sonIsomorficas(p,c,N))
		cout << "SÍ" << endl;
	else
		cout << "NO" << endl;
}