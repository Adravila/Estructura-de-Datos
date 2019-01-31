#include <iostream>
#include "Lista_enla.h"
#include "Cola_enla.h"
#include <cassert>

typedef int tPaciente;

struct tMedico
{
	Cola<tPaciente>cola;
	const char* nombre;
};

class Consultorio
{
	public:
		Consultorio(){}
		void AltaMedico(const tMedico& m);
		void BajaMedico(const tMedico& m);
		void ListaEspera(const tPaciente& pa, const tMedico& m);
		tPaciente ConsultarPaciente(const tMedico& m);
		void AtenderPaciente(const tMedico& m);
		bool tienePacientes(const tMedico& m);
	private:
		Lista<tMedico> med;
		Lista<tMedico>::posicion p;
};

bool operator == (const tMedico& m1, const tMedico& m2){
	return m1.nombre == m2.nombre;
}

void Consultorio::AltaMedico(const tMedico& m){
	p = med.fin();
	med.insertar(m,p);
}

void Consultorio::BajaMedico(const tMedico& m){
	p = med.buscar(m);
	if(p != med.fin())
		med.eliminar(p);
}

void Consultorio::ListaEspera(const tPaciente& pa, const tMedico& m){
	p = med.buscar(m);
	if(p != med.fin())
		med.elemento(p).cola.push(pa);
}

tPaciente Consultorio::ConsultarPaciente(const tMedico& m){
	p = med.buscar(m);
	assert(p != med.fin());
	assert(!med.elemento(p).cola.vacia());
	return med.elemento(p).cola.frente();
}

bool Consultorio::tienePacientes(const tMedico& m){
	p = med.buscar(m);
	assert(p != med.fin());
	return !med.elemento(p).cola.vacia();	
}

void Consultorio::AtenderPaciente(const tMedico& m){
	p = med.buscar(m);
	if(p != med.fin()){
		assert(!med.elemento(p).cola.vacia());
		med.elemento(p).cola.pop();
	}
}
