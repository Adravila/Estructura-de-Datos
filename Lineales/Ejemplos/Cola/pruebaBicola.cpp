#include <iostream>
#include "bicola.h"

using namespace std;

int main()
{
	Bicola<int> B;
	
	B.push(1);
	B.push(2);
	B.push(3);
	B.push(4);
	B.push(5);
	B.push(6);
	B.push(7);
    B.popFin();
    B.popFin();
    B.pushIni(6);
    B.pushIni(3);
    B.popFin();
    B.push(4);
    B.popFin();
    B.popFin();
    B.popFin();
    B.popFin();

	while(!B.vacia())
	{
		cout << B.frente();
		B.pop();
	}

}