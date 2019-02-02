#include <iostream>
#include "Diccionario.hpp"

int main()
{
	Palabra free("Free");
	Diccionario D;
	D.insertarTraduccionESPtoENG("Free","Gratis");
	D.insertarTraduccionESPtoENG("Free","Libre");
	D.insertarTraduccionESPtoENG("Free","Casa");
	D.eliminarTraduccionESPtoENG("Free","Casa");
	D.consultarTraduccionENG("Free");
}
