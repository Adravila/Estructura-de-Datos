#include <iostream>

template <typename T> 
class Bicola {
public:
	explicit Bicola(size_t TamaMax); //ctor., requiere ctor. T()
	Bicola(const Bicola<T>& BC);  //ctor. de copia, requiere ctor. T()
	Bicola<T> operator =(const Bicola<T> BC); // asig. colas, req. T()
	bool vacia() const;
	bool llena() const;
	const T& frenteFin() const;
	const T& frenteInicio() const;
	void BicolaPopFin();
	void BicolaPopInicio();
	void BicolaPushFin(const T& x);
	void BicolaPushInicio(const T& x);
	~Bicola();  //destructor
private:
	T elementos;  //vector de T
	int Lmax;  //tamaño vector
	int inicio, fin;
};

template <typename T> 
void Bicola<T>::BicolaPopFin(){
	assert(!vacia());
	fin = (Lmax + fin - 1) % Lmax;
}

template <typename T> 
void Bicola<T>::BicolaPushInicio(const T& x){
	assert(!llena());
	inicio = (Lmax + inicio - 1) % Lmax;
	elementos[inicio] = x;
}

// El resto de las operaciones son del TAD Cola

template <typename T>
void Bicola<T>::BicolaPopInicio(){
	assert(!vacia());
	inicio = (inicio + 1) % Lmax;
}

template <typename T>
void Bicola<T>::BicolaPushFin(const T& x){
	assert(!llena());
	fin = (fin + 1) % Lmax;
}
