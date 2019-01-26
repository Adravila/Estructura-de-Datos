#include <iostream>
#include "cola_enla.hpp"
#include "pila_enla.hpp"

struct Simbolo{
	double operando;
	char operador;
	Simbolo(char opr = ' ') : operador(opr), operando(0) {}
	Simbolo(double opn = 0) : operador(' '), operando(opn) {}
};

typedef Cola<Simbolo> expresion;

class PostFijo{
public:
	PostFijo(){}
	double evaluar(expresion& e);
	bool esOperando(const Simbolo& s) const;
	Simbolo operar(const Simbolo& o1, const Simbolo& o2, const Simbolo& r);
	Simbolo siguienteSimbolo(expresion& e);
private:
	Pila<Simbolo> P;
};

Simbolo PostFijo::siguienteSimbolo(expresion& e){
	Simbolo s = e.frente();
	e.pop();
	return s;
}

bool PostFijo::esOperando(const Simbolo& s) const{
	return s.operador == ' ';
}

Simbolo PostFijo::operar(const Simbolo& o1, const Simbolo& o2, const Simbolo& r){
	switch(r.operador){
		case '+': return o1.operando + o2.operando;
		case '-': return o1.operando - o2.operando;
		case '/': return o1.operando / o2.operando;
		case '*': return o1.operando * o2.operando;
	}
}

double PostFijo::evaluar(expresion& e){
	Simbolo s(' ');
	Simbolo o1(0.), o2(0.), r(0.);

	do{
		s = siguienteSimbolo(e);
		if(esOperando(s))
			P.push(s);
		else{
			o2 = P.tope();
			P.pop();
			o1 = P.tope();
			P.pop();
			r = operar(o1,o2,s);
			P.push(r);
		}
	}while(!e.vacia());
	return P.tope().operando;
}
