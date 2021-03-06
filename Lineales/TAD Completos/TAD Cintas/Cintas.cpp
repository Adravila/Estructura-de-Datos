#include <iostream>
#include <vector>
#include "Lista_vec.h"

using namespace std;

/*
    ESPECIFICACIÓN DEL TAD CINTAS:
        
        - Postcondición: Construye la cinta transportadora, su estructura está compuesta por
        - posiciones vacias, cada una de estas posiciones se utilizarán para transportar un
         determinado paquete
        Cintas(const size_t n);

         - Precondición: El paquete debe estar en la cinta y no debe situarse al extremo derecho (límite)
         - Postcondición: Mueve el paquete una posición a la derecha
        void moverFrenteCinta(unsigned int n = 1);

         - Precondición: El paquete debe estar en la cinta y no debe situarse al extremo izquierdo (límite)
         - Postcondición: Mueve el paquete una posición a la izquierda
        void moverAtrasCinta(unsigned int n = 1);

         - Precondición: No debe haber más de un paquete en la cinta transportadora
         - Postcondición: Se añade un paquete en la posición central de la cinta
        void cargarPaquete(const tPaquete &p);

         - Postcondición: Retira el paquete de la cinta. Recordamos que si se extrae del lateral 
          izquierdo es para un embalaje frágil, al otro lado debe ser rígido.
        void descargarPaquete();

         - Postcondición: Devuelve true si el paquete de la lista es frágil, en caso contrario devuelve false
        bool comprobarPaqueteFragil(const Lista<tPaquete>::posicion &p) const;

         - Postcondición: Muestra el estado actual de la cinta transportadora
        void mostrarCinta();
 */

struct tPaquete
{
    tPaquete() : ind('O'){};
    char ind; // indicador X (hueco), O (paquete)
    vector<const char *> contenido;
};

class Cintas
{
public:
    Cintas(const size_t n);
    void moverFrenteCinta(unsigned int n = 1);
    void moverAtrasCinta(unsigned int n = 1);
    void cargarPaquete(const tPaquete &p);
    void descargarPaquete();
    void mostrarCinta();
    bool comprobarPaqueteFragil(const Lista<tPaquete>::posicion &p) const;

private:
    Lista<tPaquete> L;
    typename Lista<tPaquete>::posicion p;
    typename Lista<tPaquete>::posicion pos_paq;
    tPaquete C, N;
    size_t tam;
};

Cintas::Cintas(const size_t n)
    : L(n), tam(n)
{
    N.ind = 'X';
    C.ind = 'X';
    int cont = 0;
    bool encontrado = false;
    p = L.primera();
    while (cont < tam)
    {
        if (cont >= (int)(n / 2) && !encontrado)
        {
            pos_paq = p;
            encontrado = true;
        }
        L.insertar(N, p);
        p = L.siguiente(p);
        cont++;
    }
}

void Cintas::cargarPaquete(const tPaquete &p)
{
    if (C.ind == 'X')
    {
        L.elemento(pos_paq) = p;
        C = p;
    }
    else
    {
        cout << "No se puede añadir más paquetes en la cinta." << endl;
    }
}

void Cintas::descargarPaquete()
{
    if (pos_paq == L.primera())
    {
        if (comprobarPaqueteFragil(pos_paq))
        {
            L.elemento(pos_paq) = N;
            C = N;
            pos_paq = ((Lista<tPaquete>::posicion)(int)(tam / 2));
            cout << "Paquete descargado de la maquinaria extrema izquierda" << endl;
        }
        else
        {
            cout << "El contenido del embalaje no es frágil, se descarta su extracción" << endl;
        }
    }
    else if (pos_paq == L.anterior(L.fin()))
    {
        if (!comprobarPaqueteFragil(pos_paq))
        {
            L.elemento(pos_paq) = N;
            C = N;
            pos_paq = ((Lista<tPaquete>::posicion)(int)(tam / 2));
            cout << "Paquete descargado de la maquinaria extrema derecha" << endl;
        }
        else
        {
            cout << "El contenido del embalaje es frágil, se descarta su extracción" << endl;
        }
    }
    else
    {
        cout << "No hay ningún paquete disponible" << endl;
    }
}

bool Cintas::comprobarPaqueteFragil(const Lista<tPaquete>::posicion &p) const
{
    for (int i = 0; i < C.contenido.size(); ++i)
    {
        if (C.contenido[i] == "ESPUMA-POLI" || C.contenido[i] == "PROT-BURBUJAS" || C.contenido[i] == "FILM-AGUJ" ||
            C.contenido[i] == "COJINES-AIRE" || C.contenido[i] == "SOPORT-CART-GOM")
        {
            return true; // contenido frágil
        }
    }
    return false; // contenido no frágil
}

void Cintas::mostrarCinta()
{
    p = L.primera();
    while (p != L.fin())
    {
        cout << L.elemento(p).ind << " ";
        p = L.siguiente(p);
    }
    cout << endl;
}

void Cintas::moverFrenteCinta(unsigned int n)
{
    while (n > 0)
    {
        if (pos_paq != L.anterior(L.fin()))
        {
            L.elemento(pos_paq) = N;
            pos_paq = L.siguiente(pos_paq);
            L.elemento(pos_paq) = C;
        }
        --n;
    }
}

void Cintas::moverAtrasCinta(unsigned int n)
{
    while (n > 0)
    {
        if (pos_paq != L.primera())
        {
            L.elemento(pos_paq) = N;
            pos_paq = L.anterior(pos_paq);
            L.elemento(pos_paq) = C;
        }
        --n;
    }
}

int main()
{
    Cintas c(11);
    unsigned int op = 0;
    unsigned int cont = 0, cant = 0;
    bool tiene[4] = {false, false, false, false};
    do
    {
        cout << "M e n u " << endl;
        cout << "*********************************" << endl;
        cout << "1. Mover paquete a la izquierda" << endl;
        cout << "2. Mover paquete por unidades a la izquierda" << endl;
        cout << "3. Mover paquete a la derecha" << endl;
        cout << "4. Mover paquete por unidades a la derecha" << endl;
        cout << "5. Cargar paquete" << endl;
        cout << "6. Descargar paquete" << endl;
        cout << "7. Salir" << endl;
        cout << "ESTADO: ";
        c.mostrarCinta();
        cout << "ELEGIR: ";
        cin >> op;
        tPaquete p;
        switch (op)
        {
        case 1:
            c.moverAtrasCinta();
            break;
        case 2:
            cout << "Número de unidades a mover (izquierda): ";
            cin >> cant;
            c.moverAtrasCinta(cant);
            break;
        case 3:
            c.moverFrenteCinta();
            break;
        case 4:
            cout << "Número de unidades a mover (derecha): ";
            cin >> cant;
            c.moverFrenteCinta(cant);
            break;
        case 5:
            cont = 0;
            do
            {
                cout << "Contenido del paquete: " << endl;
                if (!tiene[0])
                    cout << "1. ESPUMA-POLI" << endl;
                if (!tiene[1])
                    cout << "2. PROT-BURBUJAS" << endl;
                if (!tiene[2])
                    cout << "3. COJINES-AIRE" << endl;
                if (!tiene[3])
                    cout << "4. FILM-AGUJ" << endl;
                if (!tiene[4])
                    cout << "5. SOPORT-CART-GOM" << endl;
                cout << "6. Procesar contenido" << endl;
                cout << "Elegir: ";
                cin >> cont;
                switch (cont)
                {
                case 1:
                    p.contenido.push_back("ESPUMA-POLI");
                    tiene[0] = true;
                    break;
                case 2:
                    p.contenido.push_back("PROT-BURBUJAS");
                    tiene[1] = true;
                    break;
                case 3:
                    p.contenido.push_back("COJINES-AIRE");
                    tiene[2] = true;
                    break;
                case 4:
                    p.contenido.push_back("FILM-AGUJ");
                    tiene[3] = true;
                    break;
                case 5:
                    p.contenido.push_back("SOPORT-CART-GOM");
                    tiene[4] = true;
                    break;
                case 6:
                    break;
                default:
                    break;
                }
            } while (cont != 6);
            c.cargarPaquete(p);
            break;
        case 6:
            c.descargarPaquete();
            break;
        case 7:
            break;
        default:
            break;
        }
        tiene[0] = false;
        tiene[1] = false;
        tiene[2] = false;
        tiene[3] = false;
        tiene[4] = false;
    } while (op != 7);
}