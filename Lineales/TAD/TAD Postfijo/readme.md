## Enunciado TAD Postfijo [Sin Implementar/Especificar]
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
