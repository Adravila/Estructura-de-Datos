## Enunciado TAD Postfijo [Completado]
-**Infijo:** El operador está entre dos operandos

-**Postfijo:** El operador se escribe después de los operandos.
Para la expresión postfijo no hay ninguna regla de precedencia de operadores ni utilizan paréntesis ().

**Infijo --> Postfijo** 

(A+B)*(C+D) **-->** AB+CD+*

X/Y*Z+W **-->** XY/Z*W+

A-C+B/D **-->** AC-BD/+

Y*(A-X)/(Z+B) **-->** YAX-*ZB+/

W+X/Z*W/Y-Z **-->** WXZ/W*Y/+Z-

Dada una expresión postfijo y los valores de las variables que aparecen en la expresión, escribe un subprograma que devuelva el resultado de evaluar la expresión postfijo, usando el TAD Pila. Las expresiones son correctas, consta sólo de operadores +,-,*,/ y los operandos son variables cuyo nombre consta de un solo caracter.

Ejemplo: **A=3, B=5, C=6**

ABC*+= 33 **-->** A+(B*C) , AB+C*=48 **-->** (A+B)*C, CBA-/=3 **-->** C/(B-A)

Notación polaca inversa, más información: 
https://es.wikipedia.org/wiki/Notación_polaca_inversa

### Resultado:

En esta función se recibe como parámetro una cola del tipo *tVariable* (que puede ser un entero u operador), dicha cola se utilizará la representación mediante una estructura enlazada con dos punteros a los extremos del TAD Cola. Por lo tanto, O(1) en recorrer inicio y fin y O(1) en operaciones pop() y push(const T& x).

Se creará una **estructura de datos** tVariable
```
struct tVariable
{
  tVariable(){}
  tVariable(int val): val_(val), op_(' ') {}
  tVariable(char op): val_(0), op_(op) {}
  char op;
  int val;
};
```
Se hará sobrecarga para que pueda dar dos usos a tVariable: ser un **operador** o un **operando**.

Por otro lado, la función devolverá un entero, que es el resultado del **Postfijo**.

Operaciones de la representación mediante celdas enlazadas con dos punteros a los extremos del **TAD Cola**:

**PARTE PÚBLICA:**
```
bool vacia() const;
const T& frente() const;
void pop();
void push(const T& x);
// ...
```
**PARTE PRIVADA:**
```
struct nodo
{
  T elto;
  nodo *sig;
  nodo(const T &e, nodo *p = 0) : elto(e), sig(p) {}
};
nodo *inicio, *fin;
```
