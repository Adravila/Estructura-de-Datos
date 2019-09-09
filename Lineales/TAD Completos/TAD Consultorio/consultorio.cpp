#include <iostream>
#include "Lista_enla.h"
#include "Cola_enla.h"
#include <cassert>

using namespace std;

/**
 * La dirección de un hospital quiere informatizar su consultorio médico que está en constante 
 * crecimiento por medio de un sistema que permita realizar al menos las siguientes operaciones:
 *  Generar un consultorio vacío, sin ninguna información.
 *  Dar de alta un nuevo médico. (altaMedico)
 *  Dar de baja a un médico. (bajaMedico)
 *  Poner a un paciente en la lista de espera de un médico. (PonerPacListaEspera)
 *  Consultar el paciente a quien le toca el turno para ser atendido por un médico. (consultarPaciente)
 *  Atender al paciente que le toque por parte de un médico. (atenderPaciente)
 *  Comprobar si un médico tiene pacientes pendientes o no. (hayPacientes)
**/

class Consultorio
{
public:
    explicit Consultorio();
    void altaMedico(unsigned int id);
    void bajaMedico(unsigned int id);
    void pacienteEspera(unsigned int id_medico, unsigned int id_paciente, const char *nombre_pac);
    void consultaPaciente(unsigned int id);
    void atenderPaciente(unsigned int id);
    bool tienePacientes(unsigned int id);
private:
    struct tPaciente
    {
        tPaciente(unsigned int n_ss_, const char *nombre_) : n_ss(n_ss_), nombre(nombre_) {}
        unsigned int n_ss;
        const char *nombre;
    };
    struct tMedico
    {
        tMedico(unsigned int id_ = 0) : id(id_){ C = Cola<tPaciente>(); }
        unsigned int id;
        Cola<tPaciente> C;
        inline bool operator==(const tMedico &m) { return id == m.id; }
    };
    Lista<tMedico> L;
};

// Postcondición: Construye un consultorio vacío
Consultorio::Consultorio()
{
    L = Lista<tMedico>();
}

// Precondición: No puede haber un médico con el mismo ID
// Postcondición: Crea un nuevo médico y se añade a la lista de éstos
void Consultorio::altaMedico(unsigned int id)
{
    Lista<tMedico>::posicion p;
    tMedico med(id);
    p = L.buscar(med);

    if (p != L.fin())
    {
        cout << "No se ha podido dar de alta el médico, ya existe uno con el mismo ID." << endl;
    }
    else
    {
        L.insertar(med, p);
    }
}

// Postcondición: Da de baja un médico, si no existe no se hace nada
void Consultorio::bajaMedico(unsigned int id)
{
    Lista<tMedico>::posicion p;
    tMedico med(id);
    p = L.buscar(med);

    if (p == L.fin())
    {
        cout << "No se ha podido encontrar el médico con dicho ID." << endl;
    }
    else
    {
        L.eliminar(p);
    }
}

// Precondición: Debe haber un médico en la lista de éstos
// Postcondición: Pone a la cola un nuevo paciente del médico asignado
void Consultorio::pacienteEspera(unsigned int id_medico, unsigned int id_paciente, const char *nombre_pac)
{
    tPaciente pa(id_paciente, nombre_pac);
    tMedico med(id_medico);
    Lista<tMedico>::posicion p;
    p = L.buscar(med);

    if (p == L.fin())
    {
        cout << "No se ha podido encontrar el médico con dicho ID." << endl;
    }
    else
    {
        L.elemento(p).C.push(pa);
    }
}

// Precondición: Debe haber un médico en la lista de éstos
// Postcondición: Muestra los datos del paciente del frente de la cola, si
// no hay pacientes no se mostrará nada.
void Consultorio::consultaPaciente(unsigned int id)
{
    tMedico med(id);
    Lista<tMedico>::posicion p;
    p = L.buscar(med);

    if (p == L.fin())
    {
        cout << "No se ha podido encontrar el médico con dicho ID." << endl;
    }
    else
    {
        if (!L.elemento(p).C.vacia())
        {
            cout << "Num seg social: " << L.elemento(p).C.frente().n_ss << endl;
            cout << "Nombre y apellidos: " << L.elemento(p).C.frente().nombre << endl;
        }
        else
        {
            cout << "No hay pacientes en la cola del médico." << endl;
        }
    }
}

// Precondición: Debe haber un médico en la lista de éstos
// Postcondición: Elimina de la cola un paciente a partir del médico asignado
void Consultorio::atenderPaciente(unsigned int id)
{
    tMedico med(id);
    Lista<tMedico>::posicion p;
    p = L.buscar(med);

    if (p != L.fin())
    {
        cout << "No se ha podido encontrar el médico con dicho ID." << endl;
    }
    else
    {
        if (!L.elemento(p).C.vacia())
        {
            L.elemento(p).C.pop();
        }
        else
        {
            cout << "No hay pacientes en la cola del médico." << endl;
        }
    }
}

// Postcondición: Si el médico no existe devuelve false, en caso de que
// sí exista, dentro de esto, comprueba si este médico tiene pacientes
// si tiene entonces devolverá true, en caso contrario false
bool Consultorio::tienePacientes(unsigned int id)
{
    tMedico med(id);
    Lista<tMedico>::posicion p;
    p = L.buscar(med);

    if (p != L.fin())
    {
        return !L.elemento(p).C.vacia();
    }
    else
    {
        return false;
    }
}

int main()
{
    Consultorio c;
    c.altaMedico(011111);
    c.altaMedico(022222);
    c.altaMedico(033333);
    c.altaMedico(044444);
    c.altaMedico(055555);
    c.pacienteEspera(055555, 111111, "Javier Gómez");
    c.pacienteEspera(055555, 122222, "Óscar Hernández");
    c.pacienteEspera(055555, 133333, "Julian López");
    c.pacienteEspera(055555, 144444, "Adriana Pérez");
    c.bajaMedico(033333);
    c.consultaPaciente(022222);
    c.atenderPaciente(055555);
    c.consultaPaciente(055555);
    cout << "¿055555 Tiene pacientes? ";
    c.tienePacientes(055555) ? cout << "SÍ\n" : cout << "NO\n";
    cout << "¿033333 Tiene pacientes? ";
    c.tienePacientes(033333) ? cout << "SÍ\n" : cout << "NO\n";
}