# Enunciado TAD Escalonada [Sin especificar/implementar]
## Especificacion TAD Escalonada
Definicion: Se define el **TAD ESCALONADA** como una sucesion de funciones constantes en subintervalos disjuntos y contiguos, es
decir, f puede definirse mediante condiciones de la forma **f(x)= y**; si **xi <= z < xi+1** donde **yi** son distintas para los subintervalos subyacentes.
Necesitaremos por lo tanto una lista de elementos que denominaremos puntos compuesto por dos registros **x** e **y** donde "y" situa la altura de la funcion y "x" situa la coordenada en dicho eje que se prolonga hasta el siguiente salto.

## Operaciones:
  ```
  Funcion(double cord);
  Postcondicion: Crea una funcion escalonado f(x)=y definido a partir de xi.
  ```
  ```
  void insertar(const Escalon& e);
  Precondicion: Existe una funcion escalonado
  Postcondicion: Se modifica la funcion con el nuevo punto
  ```
  ```
  void eliminar(const Escalon& e);
  Precondicion: Existe una funcion escalonado
  Postcondicion: Se elimina el subintervalo al que pertence "e" y el anterior se prolonga hasta el siguiente.
  ```
  ```
  Escalon ver(const Escalon& e);
  Precondicion: Existe una funcion escalonado
  Postcondicion: Nos muestra el punto
  ```
  ```
  Escalon min(); 
  Precondicion: Existe una funcion escalonado
  Postcondicion: Devuelve el menor de los valores de "y"
  ```
  ```
  Escalon max();
  Precondicion: Existe una funcion escalonado
  Postcondicion: Devuelve el maximo de los valores de "y"
  ```
  ```
  Escalon tras(double w, double z);
  Precondicion: Existe una funcion escalonado
  Postcondicion: Se translada w unidades horizontales y z verticales.
  ```
  ```
  ~Funcion(); 
  Postcondicion: se destruye la funcion.
  ```
