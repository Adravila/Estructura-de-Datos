## Enunciado TAD Texto [OK]
Definir prototipos, operaciones del TAD. No hay carácter de salto de línea, el texto te lo dan a partir de la estructura.

Diseñe una estructura de datos para almacenar en memoria un texto del cual desconocemos el número de líneas y caracteres por línea. 
- Sabemos que el texto sólo consta de caracteres alfanuméricos y signos de puntuación, es decir, en él no aparecen caracteres de control como fin de línea, retorno de carro, etc.
- Sin embargo, hay caracteres especiales que pueden aparecer un número indeterminado de veces
- '@' indica el borrado del carácter anterior. En caso de que aparezcan varios consecutivos, sólo tiene un efecto el primero; el resto aunque se almacena, se ignora.
- '#' indica el borrado de la línea completa. Si aparecen varias igual, sólo aparecerá al final de la línea.
- Escribe una función MostrarTexto(). Al realizar este volcado a pantalla no te preocupes por el número de caracteres ni de líneas.

**Ejemplo**: 

**Texto original --> Texto impreso**

El municip**l@i**o **-->** El municipio

Ligar**e@s@** **-->** Ligar
