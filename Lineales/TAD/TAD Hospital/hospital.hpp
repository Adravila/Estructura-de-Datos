#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <iostream>
#include "lista_vec.hpp"

using namespace std;

struct tPaciente{
	tPaciente(int cod = 0, float g = 0): cod_pac(cod), grav(g) {}
	int cod_pac;
	float grav;
	
	bool operator == (const tPaciente &p) const { return cod_pac == p.cod_pac;}
};

class Hospital{
public:
	Hospital(int tam, int tam2);
	void ingreso(tPaciente &p);
	void alta(tPaciente &p);
	void mostrar() const;
	void gravedad(const float g);
	~Hospital();
private:
	Lista<tPaciente> UCI;
	Lista<tPaciente> PL;
	int maxPl, maxUci;
	int pacPl, pacUci;
};

Hospital::Hospital(int tam, int tam2): UCI(tam), PL(tam2), maxPl(tam2), maxUci(tam), pacPl(0), pacUci(0) { }

void Hospital::ingreso(tPaciente &p){
	Lista<tPaciente>::posicion a, b;
	bool encontrado = false;
	a = UCI.buscar(p);
	b = PL.buscar(p);

	if(a == UCI.fin() && b == PL.fin()) //Usuario no encontrado{
		a = UCI.primera();
		if(p.grav >= 1 && p.grav < 6){ //Esto es UCI
			if(pacUci == 0){ //Uci sin pacientes
				UCI.insertar(p,a);
				pacUci ++;
			}
			else if(pacUci < maxUci){ //Uci con algun paciente pero sin estar llena
				while(a != UCI.fin() && !encontrado){
					if(p.grav < UCI.elemento(a).grav){
						UCI.insertar(p,a);
						encontrado = true;
						pacUci++;
					}
					a = UCI.siguiente(a);
				}
				if(!encontrado){
					UCI.insertar(p,a);
					pacUci++;
				}
			}
			else if(pacUci == maxUci){ //Uci llena
				a = UCI.fin();
				b = PL.fin();
				if(pacPl == maxPl){
					b = PL.anterior(b);
					cout << "Hola planta llena" << endl;
					PL.eliminar(b);
					pacPl--;
					PL.insertar(UCI.elemento(a),b);
					pacPl++;
					UCI.eliminar(a);
					pacUci--;
				}
				else{
					tPaciente aux = UCI.elemento(UCI.anterior(a));
					PL.insertar(aux,b);
					pacPl++;
					UCI.eliminar(UCI.anterior(a));
					pacUci--;
				}
			}
		}
		else if (p.grav >= 6 && p.grav <= 9){
			if(pacPl < maxPl){ //Hay sitio en planta
				Lista<tPaciente>::posicion e;
				bool bande = false;
				e = PL.primera();
				while (e != PL.fin() && !bande){
					if(p.grav < PL.elemento(e).grav){
						UCI.insertar(p,e);
						bande = true;
						pacPl++;
					}
					e = PL.siguiente(e);
				}
				if(!bande){
					PL.insertar(p,e);
					pacPl++;
				}
			}
			else{ //Esta lleno
			
				Lista<tPaciente>::posicion w;
				w = PL.anterior(PL.fin());
				if(p.grav > PL.elemento(w).grav){ //Si es mas grave el paciente que entra al mas grave en planta
					alta(PL.elemento(w)); //Al paciente que este en la posicion final (esta ordenado asi)
					PL.insertar(p,w);
				}
				else{
					bool band = false;
					w = PL.primera();
					while (w != PL.fin() && !band){
						if(p.grav < PL.elemento(w).grav){
							UCI.insertar(p,w);
							band = true;
							pacPl++;
						}
						w = PL.siguiente(w);
					}
					if(!band){
						PL.insertar(p,w);
						pacPl++;
					}
				}
			}
		}
		else if (p.grav == 0)
			cout << "Paciente numero: " << p.cod_pac << " descanse en paz." << endl;
		else
			cout << "Gravedad no valida, el rango ha de ser entre 1 y 9 o 0 en caso de morgue." << endl;
	}
	else //Si lo encuentra
		cout << "Usuario ya ingresado." << endl;
}

void Hospital::alta(tPaciente &p){
	bool encontrado = false;
	Lista<tPaciente>::posicion a, b;
	a = UCI.buscar(p);
	if(a != UCI.fin()){
		UCI.eliminar(a);
		encontrado = true;
		pacUci--;
	}

	if(!encontrado){
		b = PL.buscar(p);
		if(b != PL.fin()){
			PL.eliminar(b);
			pacPl--;
		}
	}
}

void Hospital::mostrar() const{
	Lista<tPaciente>::posicion p, q;
	p = UCI.primera();
	q = PL.primera();
	cout << "--- UCI ---" << endl;
	while (p != UCI.fin()){
		cout << "Cod_usuario: " << UCI.elemento(p).cod_pac << " Gravedad: " << UCI.elemento(p).grav << endl;
		p = UCI.siguiente(p);
	}

	cout << "--- PLANTA --- " << endl;
	while (q != PL.fin()){
		cout << "Cod_usuario: " << PL.elemento(q).cod_pac << " Gravedad: " << PL.elemento(q).grav << endl;
		q = PL.siguiente(q);
	}
}

void Hospital::gravedad(const float g){
	Lista<tPaciente>::posicion p;
	p = UCI.primera();
	cout << " En UCI " << endl;
	while (p != UCI.fin()){
			if(g == UCI.elemento(p).grav)
				cout << "Paciente numero: " << UCI.elemento(p).cod_pac << " gravedad:" << UCI.elemento(p).grav << endl;
			p = UCI.siguiente(p);
	}
	Lista<tPaciente>::posicion q;
	q = PL.primera();
	cout << " En PLANTA " << endl;
	while (q != PL.fin()){
		if(g == PL.elemento(q).grav)
			cout << "Paciente numero: " << PL.elemento(q).cod_pac << " gravedad:" << PL.elemento(q).grav << endl;
		q = PL.siguiente(q);
	}
}

Hospital::~Hospital(){
	/*UCI.~Lista();
	PL.~Lista();*/ // Con esto me da error.
}

#endif
