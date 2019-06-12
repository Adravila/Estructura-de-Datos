#include <iostream>
#include "bicola.h"

using namespace std;

int main()
{
	Bicola<int> B;

	B.pushIni(5);
	B.pushIni(4);
	B.popFin();
	B.pushIni(3);
	B.pushIni(1);
	B.popFin();
	B.popFin();
	B.popFin();
	B.pushIni(2);
	B.pushIni(6);
	B.popFin();
	B.pushIni(3);
	B.pop();

	while (!B.vacia())
	{
		cout << B.frente();
		B.pop();
	}
}