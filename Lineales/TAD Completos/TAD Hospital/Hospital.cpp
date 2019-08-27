#include <iostream>
#include "Lista_vec.h"

using namespace std;

/**
 * Especificad e implemetad el TAD Hospital. Este TAD representa los pacientes (código de paciente) 
 * ingresados en el mismo. La gravedad de los pacientes se indica mediante un dígito decimal 
 * (en orden decreciente de gravedad). Si un paciente tiene una gravedad entre 1 y 5, estará 
 * ingresado en la U.C.I. (Unidad de Cuidados Intensivos), si su gravedad se encuentra 
 * entre 6 y 9, estará en planta. Sobra decir que la gravedad 0 implica que el paciente ingresa 
 * en la morgue. Obviamente, la capacidad de la U.C.I. y de la planta es limitada, por lo tanto, 
 * si un paciente tiene que ingresar en la U.C.I. y ésta se encuentra completamente ocupada, el paciente 
 * menos grave de la misma pasará a planta, y si sucede lo mismo con un ingreso en planta, se dará de 
 * alta al paciente con mejor estado de salud. Esta situación anómala (tener pacientes con gravedad 
 * U.C.I. en planta, será resuelta lo antes posible, volviendo dichos pacientes a U.C.I. a la primera oportunidad).
*/

class Hospital
{
public:
    explicit Hospital(unsigned int tam_uci, unsigned int tam_planta);
    void ingresoPaciente(unsigned int id, unsigned int grav);
    void altaPaciente();
    void matarPaciente(unsigned int id);
    void pacientesUCI();
    void pacientesPlanta();
    void pacientesGravedad(unsigned int grav);
    ~Hospital();

private:
    struct tPaciente
    {
        unsigned int grav, id;
        tPaciente(unsigned id_ = 0, unsigned int grav_ = 0) : id(id_), grav(grav_) {}
        bool operator==(const tPaciente &p) const { return id == p.id; }
    };
    Lista<tPaciente> Lp, Lu;
    unsigned int tam_p, tam_u, current_p, current_u;
};

// Postcondición: Construye un hospital un nuevo hospital de tamaño limitado
Hospital::Hospital(unsigned int tam_uci, unsigned int tam_planta)
    : tam_p(tam_planta), tam_u(tam_uci),
      Lp{Lista<tPaciente>{tam_planta}},
      Lu{Lista<tPaciente>{tam_uci}},
      current_p(0), current_u(0) {}

// Precondición: La gravedad debe ser entre 0 y 9, id del paciente debe ser distinto.
// Postcondición: Ingresa un paciente en la planta según su gravedad y espacio
void Hospital::ingresoPaciente(unsigned int id, unsigned int grav)
{
    assert(grav < 10); // La gravedad no puede ser mayor que 9 (0-9)
    assert(current_u < tam_u || current_p < tam_p);

    Lista<tPaciente>::posicion p_u, p_p;
    tPaciente pa(id, grav); // Creamos el paciente

    p_u = Lu.buscar(pa);
    p_p = Lp.buscar(pa);
    assert(p_u == Lu.fin() && p_p == Lp.fin()); // Si coincide ID se termina (¿?¿¿)

    if (grav == 0) // Paciente entra en la morgue
    {
        cout << "El paciente está en la morgue." << endl;
        return; // Para el procedimiento.
    }

    if (grav > 0 && grav < 6) // Ingresar en la UCI
    {
        // Insertar pacientes en la UCI (modo normal)
        p_u = Lu.primera();

        if (p_u == Lu.fin()) // No hay pacientes en la UCI
        {
            Lu.insertar(pa, p_u);
            ++current_u;
            return;
        }

        if (current_u >= tam_u) // Si está llena la UCI, se traslada el paciente menos grave
        {                       // a la planta (primera prioridad según su gravedad)
            tPaciente pw = Lu.elemento(Lu.anterior(Lu.fin()));
            Lu.eliminar(Lu.anterior(Lu.fin()));
            Lp.insertar(pw, Lu.primera());
            --current_u;
            ++current_p;
        }
        while (p_u != Lu.fin())
        {
            if (grav < Lu.elemento(p_u).grav)
            {
                Lu.insertar(pa, p_u);
                ++current_u;
                return;
            }
            else
            {
                p_u = Lu.siguiente(p_u);
                if (p_u == Lu.fin())
                {
                    Lu.insertar(pa, p_u);
                    ++current_u;
                    return;
                }
            }
        }
    }

    // Si continua, es porque no se ha añadido ningún paciente,
    // Vamos a añadirlo en la Planta
    p_p = Lp.primera();

    if (p_p == Lp.fin()) // No hay pacientes en la UCI
    {
        Lp.insertar(pa, p_p);
        ++current_p;
        return;
    }

    // Ingresar en la Planta
    while (p_p != Lp.fin())
    {
        if (grav < Lp.elemento(p_p).grav)
        {
            Lp.insertar(pa, p_p);
            ++current_p;
            return;
        }
        else
        {
            p_p = Lp.siguiente(p_p);
            if (p_p == Lp.fin())
            {
                Lp.insertar(pa, p_p);
                ++current_p;
                return;
            }
        }
    }
}

// Postcondición: Dar de alta un paciente con el mejor estado de salud
// Si no hay pacientes en la planta se traslada el paciente menos grave
// de la UCI a la planta, si no quedan pacientes en la planta y en la UCI
// no se hace nada.
void Hospital::altaPaciente()
{
    Lista<tPaciente>::posicion p_u, p_p;
    p_p = Lp.fin();
    if (p_p != Lp.primera()) // La planta no está vacía
    {
        p_p = Lp.anterior(p_p);
        Lp.eliminar(p_p);
        --current_p;
    }
    else
    {
        p_u = Lu.fin();
        if (p_u != Lu.primera()) // La UCI no está vacía, pero la planta sí
        {
            p_u = Lu.anterior(p_u);
            Lp.insertar(Lu.elemento(p_u), Lp.primera());
            Lu.eliminar(p_u);
            --current_u;
            ++current_p;
        }
        else
        {
            cout << "No se puede dar de alta, no hay pacientes..." << endl;
        }
    }
}

// Postcondición: Elimina a un paciente del hospital,
// si no se encuentre no se hace nada.
void Hospital::matarPaciente(unsigned int id)
{
    Lista<tPaciente>::posicion p_u, p_p;

    p_u = Lu.primera();
    while (p_u != Lu.fin())
    {
        if (id == Lu.elemento(p_u).id)
        {
            Lu.eliminar(p_u);
            --current_u;
            return;
        }
        p_u = Lu.siguiente(p_u);
    }

    p_p = Lp.primera();
    while (p_p != Lp.fin())
    {
        if (id == Lp.elemento(p_p).id)
        {
            Lp.eliminar(p_p);
            --current_p;
            return;
        }
        p_p = Lp.siguiente(p_p);
    }
}

// Postcondición: Muestra todos los pacientes de la UCI
void Hospital::pacientesUCI()
{
    Lista<tPaciente>::posicion p_u;
    p_u = Lu.primera();

    // Pacientes en la UCI
    cout << "UCI (" << current_u << " / " << tam_u << ") --------------------" << endl;
    while (p_u != Lu.fin())
    {
        cout << " ID: " << Lu.elemento(p_u).id << endl;
        cout << " Gravedad: " << Lu.elemento(p_u).grav << endl;
        p_u = Lu.siguiente(p_u);
    }
}

// Postcondición: Muestra todos los pacientes de la Planta
void Hospital::pacientesPlanta()
{
    Lista<tPaciente>::posicion p_p;
    p_p = Lp.primera();

    // Pacientes en la Planta
    cout << "Planta (" << current_p << " / " << tam_p << ") --------------------" << endl;
    while (p_p != Lp.fin())
    {
        cout << " ID: " << Lp.elemento(p_p).id << endl;
        cout << " Gravedad: " << Lp.elemento(p_p).grav << endl;
        p_p = Lp.siguiente(p_p);
    }
}

// Postcondición: Muestra todos los pacientes de la UCI que tengan una determinada gravedad
// Si no encuentra el paciente no mostrará la lista de éstos.
void Hospital::pacientesGravedad(unsigned int grav)
{
    Lista<tPaciente>::posicion p_u, p_p;
    p_u = Lu.primera();
    p_p = Lp.primera();

    cout << "\nPACIENTES CON GRAVEDAD: " << grav << endl;
    cout << "******************************************" << endl;

    // Pacientes en la UCI
    cout << "UCI --------------------" << endl;
    while (p_u != Lu.fin())
    {
        if (Lu.elemento(p_u).grav == grav)
        {
            cout << " ID: " << Lu.elemento(p_u).id << endl;
            cout << " Gravedad: " << Lu.elemento(p_u).grav << endl;
        }
        p_u = Lu.siguiente(p_u);
    }

    // Pacientes en la Planta
    cout << "Planta --------------------" << endl;
    while (p_p != Lp.fin())
    {
        if (Lp.elemento(p_p).grav == grav)
        {
            cout << " ID: " << Lp.elemento(p_p).id << endl;
            cout << " Gravedad: " << Lp.elemento(p_p).grav << endl;
        }
        p_p = Lp.siguiente(p_p);
    }
    cout << "******************************************" << endl;
}

Hospital::~Hospital()
{
    tam_p = 0;
    tam_u = 0;
    current_p = 0;
    current_u = 0;
    Lu.~Lista();
    Lp.~Lista();
}

int main()
{
    Hospital h(3, 3);
    h.ingresoPaciente(1, 1);
    h.ingresoPaciente(2, 4);
    h.ingresoPaciente(3, 3);
    h.ingresoPaciente(4, 5);
    h.ingresoPaciente(5, 2);
    h.pacientesUCI();
    h.pacientesPlanta();
    h.pacientesGravedad(1);
    return 0;
}