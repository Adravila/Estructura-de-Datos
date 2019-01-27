## Enunciado TAD Tren [OK]
Realizar la especificación e implementación de un **TAD Tren** que sirva para representar secuencias (de longitud arbitraria) de vagones (se supone que el tipo vagón está predefinido). Si la secuencia no está vacía, hay un vagón del tren denominado 'activo' sobre el que puede actuar un robot manipulador. Las operaciones que se piden son:
 - Crear un tren
 - **Desplazar a la izquierda**: Mueve un tren una posición a la izquierda de manera que el nuevo vagón activo es el que está inmediatamente a la derecha del actual. Si no hay vagón a la derecha no se hace nada.
 - **Desplazar a la derecha**: Simétrica a la anterior.
 - **Eliminar el vagón activo**: Se suprime el vagón activo y se convierte en activo el que está inmediatamente a su derecha. Si éste no existe, se activa el de su izquierda. Y si éste último tampoco existe, el tren queda vacío.
 - **Insertar vagón activo**: Añade un nuevo vagón al tren desplazando el actual vagón activo y los siguientes una posición hacia la derecha.
 - **Observar el vagón activo**: Una cámara fija situada sobre el robot devuelve el vagón activo.
 - **Tren vacío**: indica si el tren tiene vagones.

**Nota:** se prohíbe expresamente utilizar una estructura doblemente enlazada. Y se exige que el coste de todas las operaciones sea constante, es decir, independiente del número de vagones del tren.

Fechas implicadas en los exámenes: Junio 2014, Junio 2015

## Especificación del TAD:
Realizaremos un TAD Tren mediante una pila enlazada por celdas debido a que no se indica el tamaño límite de los vagones del tren y que éste es orden constante O(1).

Operaciones:

**Tren::Tren()**
- Postcondición: Crea un tren vacío

**void Tren::desplazarIzq()**
- Postcondición: Mueve un tren una posición anterior de manera que el nuevo vagón activo pasa a ser el que está en su posición posterior del actual.

**void Tren::desplazarDrch()**
- Postcondición: Mueve un tren una posición posterior de manera que el nuevo vagón activo pasa a ser el que está en su posición anterior del actual.

**void Tren::insertarVagon(const vagon& v)**
- Postcondición: Inserta un nuevo vagón al tren desplazando el actual vagón activo y los siguientes una posición hacia la derecha.
- Precondición: Recibe un vagón como parámetro.

**void Tren::eliminarVagon()**
- Postcondición: Se suprime el vagón activo y se convierte en activo el que está inmediatamente a su derecha. Si éste no existe, se activa el de su izquierda. Y si éste último tampoco existe, el tren queda vacío. 

**bool Tren::trenVacio() const**
- Postcondición: Devuelve verdadero si el tren está vacío, si no lo está devuelve falso.

**const vagon& Tren::vagonActivo() const noexcept**
- Postcondición: Devuelve el vagón activo.
