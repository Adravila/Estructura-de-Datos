#include <iostream>
#include "lista_enla.hpp"
#include "cola_enla.hpp"
#include <cassert>

typedef int Paciente;

struct Medico{
	Cola<Paciente>cola;
	const char* nombre;
};

class Consultorio{
public:
	Consultorio(){}
	void AltaMedico(const Medico& m);
	void BajaMedico(const Medico& m);
	void ListaEspera(const Paciente& pa, const Medico& m);
	Paciente ConsultarPaciente(const Medico& m);
	void AtenderPaciente(const Medico& m);
	bool tienePacientes(const Medico& m);
private:
	Lista<Medico> med;
	Lista<Medico>::posicion p;
};

bool operator == (const Medico& m1, const Medico& m2){
	return m1.nombre == m2.nombre;
}

void Consultorio::AltaMedico(const Medico& m){
	p = med.fin();
	med.insertar(m,p);
}

void Consultorio::BajaMedico(const Medico& m){
	p = med.buscar(m);
	if(p != med.fin())
		med.eliminar(p);
}

void Consultorio::ListaEspera(const Paciente& pa, const Medico& m){
	p = med.buscar(m);
	if(p != med.fin())
		med.elemento(p).cola.push(pa);
}

Paciente Consultorio::ConsultarPaciente(const Medico& m){
	p = med.buscar(m);
	assert(p != med.fin());
	assert(!med.elemento(p).cola.vacia());
	return med.elemento(p).cola.frente();
}

bool Consultorio::tienePacientes(const Medico& m){
	p = med.buscar(m);
	assert(p != med.fin());
	return med.elemento(p).cola.vacia();	
}

void Consultorio::AtenderPaciente(const Medico& m){
	p = med.buscar(m);
	if(p != med.fin()){
		assert(!med.elemento(p).cola.vacia());
		med.elemento(p).cola.pop();
	}
}
