#include <iostream>
#include "pila_enla.hpp"

struct tCubo{
	bool boca_abajo;
	int anchura;
	tCubo(int n, bool ba) : boca_abajo(ba), anchura(n) {}
};

class Cubilete{
public:
	Cubilete(){}
	Pila<tCubo> apilarCubilete(const Pila<tCubo> P);
private:
	bool cubileteValido(const Pila<tCubo> P);
};


bool Cubilete::cubileteValido(const Pila<tCubo> P){
	Pila<tCubo> Paux, Paux2;
	Paux = P;
	while(!Paux.vacia()){
		tCubo c = Paux.tope();
		Paux.pop();
		Paux2 = Paux;
		while(!Paux2.vacia()){
			if(c.anchura == Paux2.tope().anchura)
				return false;
			Paux2.pop();
		}
	}
	return true;
}

Pila<tCubo> Cubilete::apilarCubilete(const Pila<tCubo> P){
	Pila<tCubo>Porg, Pnew, Paux;
	Porg = P;

	if(cubileteValido(P)){
		while(!Porg.vacia()){
			tCubo c = Porg.tope();
			if(c.boca_abajo == false)
				c.boca_abajo = true;
			Porg.pop();

			if(Pnew.vacia()) // Insertando el primer elemento en Pnew
	 			Pnew.push(c);
	 		else{
	 			if(c.anchura < Pnew.tope().anchura) // Si la condición cumple es que el cubilete se posicionará justamente encima.
	 				Pnew.push(c);
	 			else{
					while(c.anchura > Pnew.tope().anchura){
						Paux.push(Pnew.tope());
						Pnew.pop();
						if(!Pnew.vacia()){
							if(Pnew.tope().anchura > c.anchura)
								Pnew.push(c);											
						}
						else
							Pnew.push(c);
					}
					while(!Paux.vacia()){
						Pnew.push(Paux.tope());
						Paux.pop();
					}
				}
			}

		}
		return Pnew;
	}
	return P;
}

int main(){
	tCubo c1(5,false);
	tCubo c2(2,false);
	tCubo c3(9,false);
	tCubo c4(8,false);
	tCubo c5(1,false);
	tCubo c6(4,false);
	tCubo c7(3,false);

	Pila<tCubo> PC;
	PC.push(c1);
	PC.push(c2);
	PC.push(c3);
	PC.push(c4);
	PC.push(c5);
	PC.push(c6);
	PC.push(c7);

	Cubilete c;
	PC = c.apilarCubilete(PC);
	while(!PC.vacia()){
		std::cout << PC.tope().anchura;
		PC.pop();
	}
}
