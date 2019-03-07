#include <iostream>
#include "Lista_vec.h"

struct tPaciente
{
    tPaciente(){}
    tPaciente(unsigned cod, unsigned grv) : cod_(cod), grv_(grv)
    {
        assert(grv >= 0 && grv <= 9);
    }
    unsigned cod_, grv_;
};

bool operator == (const tPacinete& p1, const tPaciente& p2)
{
    return (p1.cod == p2.cod);
}

class Hospital
{
    public:
        Hospital(unsigned tamUCI, unsigned tamPL);
        void IngresoUCI(const tPaciente& p);
        void AltaPaciente(const tPaciente& p);
        void MuertePaciente(const tPaciente& p);
        void PacientesUCI();
        void PacientesPlanta();
        void PacientesGravedad(unsigned grv);
        ~Hospital();
    private:
        Lista<tPaciente> LUCI, LPL;
        unsigned tamUCI_, tamPL_;
        unsigned p_uci, p_pl;
}

Hospital::Hospital(unsigned tamUCI, , unsigned tamPL) 
    : LUCI(tamUCI), LPLA(tamPL), tamUCI_(tamUCI), tamPL_(tamPL), p_uci(0), p_pl(0) {}

Hospital::~Hospital()
{
    ~LUCI();
    ~LPL();
    tamUCI_ = 0;
    tamPL_ = 0;
    p_uci = 0;
    p_pl = 0;
}

void Hospital::IngresoUCI(const tPaciente& p)
{
    Lista<tPaciente>::posicion pos_UCI, pos_PL;

    if(p_uci != tamUCI_)
    {
        if(p.grv_ >= 1 && p.grv_ <= 5)
        {
            pos_UCI = LUCI.fin();
            LUCI.insertar(p,pos_UCI);
            ++p_uci;
        }
    }
    else if(p_uci == tamUCI_) // No cabe más en la UCI, realizar desplazamiento del menos grave a la planta
    {
        unsigned max = 0;
        pos_UCI = LUCI.primera();
        Lista<tPaciente>::posicion p_aux;
        while(pos_UCI != LUCI.fin())
        {
            if(max < LUCI.elemento(pos_UCI).grv_)
            {
                max = LUCI.elemento(pos_UCI).grv_;
                p_aux = pos_UCI;
            }
        }
        if(p_pl != tamPL_)  // Cabe en la planta
        {
            pos_PL = LPLA.fin();
            pos_UCI = LUCI.fin();
            LPLA.insertar(LUCI.elemento(p_aux),pos_PL);  // Desplazamiento a la planta el paciente con menos gravedad
            LUCI.eliminar(p_aux);   // Eliminar de la lista el paciente con menos gravedad en la UCI
            LUCI.insertar(p,pos_UCI);   // Añade el nuevo paciente más grave que el anterior
            ++p_pl; // Añadido en la planta
        }
        else // No cabe en la planta...
        {
            unsigned max = 0;
            pos_PL = LPLA.primera();
            Lista<tPaciente>::posicion p_aux_2;

            while(pos_PL != LPLA.fin())
            {
                if(max < LPLA.elemento(pos_PL).grv_)
                {
                    max = LPLA.elemento(pos_PL).grv_;
                    p_aux_2 = pos_UCI;
                }
            }
            LPLA.eliminar(p_aux_2);
            LPLA.insertar(LUCI.elemento(p_aux),p_aux_2);
            LUCI.eliminar(p_aux);
            LUCI.insertar(p,pos_UCI); 
        }
    }
}

void Hospital::AltaPaciente(const tPaciente& p)
{
    // Primero daremos de la alta a los que están en la Planta con mayor gravedad

    Lista<tPaciente>::posicion p, p_min, p_max;
    p = LPLA.primera();
    int max = 0;
    bool alta = false;

    // Obtener el paciente más grave y el menos grave de la PLANTA
    while(p != LPLA.fin())
    {
        if(max < LPLA.elemento(p))
        {
            max = LPLA.elemento(p).grv_;
            p_aux = p;
        }
        if(min > LPLA.elemento(p))
        {
            min = LPLA.elemento(p).grv_;
            p_min = p;
        }
        p = LPLA.siguiente(p);
    }
    LPLA.eliminar(p_max);
}

void Hospital::Muerte(const tPaciente& p)
{
    
}