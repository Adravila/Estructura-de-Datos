#include <iostream>
#include "Pila_enla.h"

using namespace std;

template <typename T>
class Cursor
{
    public:
        Cursor(){}
        void avanzarCursor();
        void retrocederCursor();
        void irFinalLinea();
        void irPrincipioLinea();
        void borrarEnCursor();
        void borrarAnteriorCursor();
        void insertarEnCursor(const T& x);
        void insertarAnteriorCursor(const T& x);
        void sobreescribirCursor(const T& x);
        void mostrarCursor();
    private:
        Pila<char> C_IZQ, C_DRCH;
};

template <typename T>
void Cursor<T>::avanzarCursor()
{
    if(!C_DRCH.vacia())
    {
        C_IZQ.push(C_DRCH.tope());
        C_DRCH.pop();
    }   
}

template <typename T>
void Cursor<T>::retrocederCursor()
{
    if(!C_IZQ.vacia())
    {
        C_DRCH.push(C_IZQ.tope());
        C_IZQ.pop();
    }
}

template <typename T>
void Cursor<T>::irFinalLinea()
{
    while(!C_DRCH.vacia())
    {
        C_IZQ.push(C_DRCH.tope());
        C_DRCH.pop();
    }   
}

template <typename T>
void Cursor<T>::irPrincipioLinea()
{
    while(!C_IZQ.vacia())
    {
        C_DRCH.push(C_IZQ.tope());
        C_IZQ.pop();
    }
}

template <typename T>
void Cursor<T>::borrarEnCursor()
{
    if(!C_DRCH.vacia()) 
    {
        C_DRCH.pop();
    }
}

template <typename T>
void Cursor<T>::borrarAnteriorCursor()
{
    if(!C_IZQ.vacia()) 
    {
        C_IZQ.pop();
    }
}

template <typename T>
void Cursor<T>::insertarEnCursor(const T& x)
{
    C_IZQ.push(x);
}

template <typename T>
void Cursor<T>::sobreescribirCursor(const T& x)
{
    if(!C_DRCH.vacia()) 
    {
        C_DRCH.pop();
        C_DRCH.push(x);
    }}

template <typename T>
void Cursor<T>::mostrarCursor()
{
    Pila<T> P1 = C_IZQ, P2 = C_DRCH, P_AUX;
    
    while(!P1.vacia())
    {
        P_AUX.push(P1.tope());
        P1.pop();
    }

    while(!P_AUX.vacia())
    {
        cout << P_AUX.tope();
        P_AUX.pop();
    }

    cout  << "|";

    while(!P2.vacia())
    {
        cout << P2.tope();
        P2.pop();
    }
    cout << endl;
}

int main()
{
    Cursor<char> C;
    char val;
    int op = 0;
    do{
        cout << "Menu cursor" << endl;
        cout << "1. Avanzar el cursor una posición" << endl;
        cout << "2. Retrasar el cursor una posición" << endl;
        cout << "3. Ir al final de la línea" << endl;
        cout << "4. Ir al principio de la línea" << endl;
        cout << "5. Borrar el carácter de la posición del cursor" << endl;
        cout << "6. Borrar el carácter anterior al cursor" << endl;
        cout << "7. Insertar un carácter en la posición del cursor" << endl;
        cout << "8. Sobreescribir el carácter del cursor" << endl;
        cout << "Resultado: "; C.mostrarCursor();
        cout << "Elegir: ";
        cin >> op;
        switch (op)
        {
            case 1 : C.avanzarCursor(); break;
            case 2 : C.retrocederCursor(); break;
            case 3 : C.irFinalLinea(); break;
            case 4 : C.irPrincipioLinea(); break;
            case 5 : C.borrarEnCursor(); break;
            case 6 : C.borrarAnteriorCursor(); break;
            case 7 : cout << "Introduzca un carácter: "; cin >> val; C.insertarEnCursor(val); break;
            case 8 : cout << "Introduzca un carácter: "; cin >> val; C.sobreescribirCursor(val); break;
            case 9 : break;
            default: cout << "No se ha introducido una opción correcta.";
        }
    }while(op != 9);
}