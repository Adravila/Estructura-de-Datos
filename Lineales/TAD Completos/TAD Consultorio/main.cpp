#include <iostream>
#include "consultorio.hpp"

int main()
{
    tMedico t1("Pablo"), t2("Joaquin"), t3("Elena"), t4("Rosa");
    tPaciente p1 = 1, p2 = 2, p3 = 3, p4 = 4, p5 = 5, p6 = 6, p7 = 7;
 
    Consultorio c;
    c.AltaMedico(t1);
    c.AltaMedico(t2);
    c.AltaMedico(t3);
    c.AltaMedico(t4);
    c.ListaEspera(p1,t1);
    c.ListaEspera(p2,t1);
    c.ListaEspera(p3,t1);
    c.ListaEspera(p4,t3);
    c.ListaEspera(p5,t4);
    std::cout << "Cod paciente: " << c.ConsultarPaciente(t1) << std::endl;
    std::cout << "Cod paciente: " << c.ConsultarPaciente(t3) << std::endl;
    std::cout << "Cod paciente: " << c.ConsultarPaciente(t4) << std::endl;
    c.BajaMedico(t1);
    c.AltaMedico(t1);
    c.ListaEspera(p3,t1);
    c.AtenderPaciente(t1);
    std::cout << "Tiene pacientes: ";
    if(c.tienePacientes(t1))
    {
        std::cout << "Sí" << std::endl;
        c.ConsultarPaciente(t1);
    }
    else
    {
      std::cout << "No" << std::endl;  
    }
}