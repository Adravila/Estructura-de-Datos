#ifndef BINARIO_H_INCLUDED
#define BINARIO_H_INCLUDED
#include <iostream>
#include "ListaD.h"
class Binario{
public:
Binario(const char *cadena);//Solo se llamara al constructor con una cadena de caracteres
Binario(const Binario& b);//constructor de copia
Binario& operator=(const Binario& b);//operador de asignacion
Binario opand(const Binario& bin);
Binario opor(const Binario& bin);
Binario opxor(const Binario& bin);
void desizq(const int ndes);
void desder(const int ndes);
void muestraelementos();
~Binario();//Destructor
private:
ListaD<int> elementos;//Lista de elementos que conforman el numero binario
};
Binario::Binario(const char *cadena)
{
ListaD<int>::posicion p;
int contador;
p=elementos.primera();
contador=0;
while(cadena[contador]!= '\0')//Recorro la cadena
{
elementos.insertar((cadena[contador])-48,p);
p=elementos.siguiente(p);
contador++;
}
}
Binario::Binario(const Binario& b)//Constructor de copia
{
elementos=b.elementos;
}
Binario& Binario::operator=(const Binario& b)//operador de asignacion
{
if (this!=&b) {
this->~Binario();
elementos=b.elementos;
}
return *this;
}

Binario Binario::opand(const Binario& bin)
{
Binario mezcla("");
ListaD<int>::posicion r,q,p;

r=mezcla.elementos.primera();
p=(elementos.fin());
q=(bin.elementos.fin());
while(p!=elementos.primera() && q!=bin.elementos.primera())//Al ser una estructura doblemente enlazada terminara una vez llegue al nodo Cabecera
{
//Evitamos que en la ultima iteracion se acceda al nodo cabecera... salta el assert
p=elementos.anterior(p);
//Evitamos que en la ultima iteracion se acceda al nodo cabecera... salta el assert
q=bin.elementos.anterior(q);
if(elementos.elemento(p)==1 && bin.elementos.elemento(q)==1)
mezcla.elementos.insertar(1,r);
else if(elementos.elemento(p)==1 && bin.elementos.elemento(q)==0)
mezcla.elementos.insertar(0,r);
else if(elementos.elemento(p)==0 && bin.elementos.elemento(q)==1)
mezcla.elementos.insertar(0,r);
else
mezcla.elementos.insertar(0,r);
}
//En este momento almenos uno de los dos binarios ha llegado a fin
if(p!=elementos.primera())//Aun quedan elementos aqui
{
while(p!=elementos.primera())
{
p=elementos.anterior(p);
mezcla.elementos.insertar(0,r);
}
}
if(q!=bin.elementos.primera())
{//Aun quedan elementos en el otro sitio
while(q!=bin.elementos.primera())
{
q=bin.elementos.anterior(q);
mezcla.elementos.insertar(0,r);
}
}
return mezcla;
}
Binario Binario::opor(const Binario& bin)
{
Binario mezcla("");
ListaD<int>::posicion r=mezcla.elementos.primera();
ListaD<int>::posicion p=(elementos.fin());
ListaD<int>::posicion q=(bin.elementos.fin());

while(p!=elementos.primera() && q!=bin.elementos.primera())//Al ser una estructura doblemente enlazada terminara una vez llegue al nodo Cabecera
{
p=elementos.anterior(p);
q=bin.elementos.anterior(q);
if(elementos.elemento(p)==1 && bin.elementos.elemento(q)==1)
mezcla.elementos.insertar(1,r);
else if(elementos.elemento(p)==1 && bin.elementos.elemento(q)==0)
mezcla.elementos.insertar(1,r);
else if(elementos.elemento(p)==0 && bin.elementos.elemento(q)==1)
mezcla.elementos.insertar(1,r);
else
mezcla.elementos.insertar(0,r);
}
//En este momento almenos uno de los dos binarios ha llegado a fin
if(p!=elementos.primera())//Aun quedan elementos aqui
{
while(p!=elementos.primera())
{
if(elementos.elemento(p)==1)
{
p=elementos.anterior(p);
mezcla.elementos.insertar(1,r);
}
else
{
p=elementos.anterior(p);
mezcla.elementos.insertar(0,r);
}
}
}

if(q!=bin.elementos.primera())//Aun quedan elementos aqui
{
while(q!=bin.elementos.primera())
{
if(bin.elementos.elemento(q)==1)
{
q=bin.elementos.anterior(q);
mezcla.elementos.insertar(1,r);
}
else
{
q=bin.elementos.anterior(q);
mezcla.elementos.insertar(0,r);
}
}
}

return mezcla;
}
Binario Binario::opxor(const Binario& bin)
{
Binario mezcla("");
ListaD<int>::posicion r=mezcla.elementos.primera();
ListaD<int>::posicion p=(elementos.fin());
ListaD<int>::posicion q=(bin.elementos.fin());
while(p!=elementos.primera() && q!=bin.elementos.primera())//Al ser una estructura doblemente enlazada terminara una vez llegue al nodo Cabecera
{
p=elementos.anterior(p);
q=bin.elementos.anterior(q);
if(elementos.elemento(p)==1 && bin.elementos.elemento(q)==1)
mezcla.elementos.insertar(0,r);
else if(elementos.elemento(p)==1 && bin.elementos.elemento(q)==0)
mezcla.elementos.insertar(1,r);
else if(elementos.elemento(p)==0 && bin.elementos.elemento(q)==1)
mezcla.elementos.insertar(1,r);
else
mezcla.elementos.insertar(0,r);
}
//En este momento almenos uno de los dos binarios ha llegado a fin
if(p!=elementos.primera())
{//Aun quedan elementos aqui
while(p!=elementos.primera())
{
if(elementos.elemento(p)==1)
{
p=elementos.anterior(p);
mezcla.elementos.insertar(1,r);
}
else
{
p=elementos.anterior(p);;
mezcla.elementos.insertar(0,r);
}
}
}
if(q!=bin.elementos.primera())
{//Aun quedan elementos aqui
while(q!=bin.elementos.primera())
{
if(bin.elementos.elemento(q)==1)
{
q=bin.elementos.anterior(q);
mezcla.elementos.insertar(1,r);
}
else
{
q=bin.elementos.anterior(q);
mezcla.elementos.insertar(0,r);
}
}
}

return mezcla;
}
void Binario::desizq(const int ndes)
{
int cont=ndes;
while(cont!=0)
{
elementos.eliminar(elementos.primera());
elementos.insertar(0,elementos.fin());
cont--;
}
}
void Binario::desder(const int ndes)
{
int cont=ndes;
while(cont!=0)
{
elementos.insertar(0,elementos.primera());
elementos.eliminar(elementos.anterior(elementos.fin()));
cont--;
}
}

void Binario::muestraelementos(){
ListaD<int>::posicion p=elementos.primera();
while(p!=elementos.fin())
{
std::cout<<elementos.elemento(p)<<" ";
p=elementos.siguiente(p);
}
std::cout<<std::endl;
}
Binario::~Binario(){}
#endif // BINARIO_H_INCLUDED
