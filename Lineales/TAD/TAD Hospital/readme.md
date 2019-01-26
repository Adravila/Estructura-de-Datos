## TAD Hospital [Completado]
Especificad e implemetad el **TAD Hospital**. Este TAD representa los pacientes (código de paciente) ingresados en el mismo. La gravedad de los pacientes se indica mediante un dígito decimal (en orden decreciente de gravedad). Si un paciente tiene una gravedad entre 1 y 5, estará ingresado en la **U.C.I. (Unidad de Cuidados Intensivos)**, si su gravedad se encuentra entre 6 y 9, estará en planta. Sobra decir que la gravedad 0 implica que el paciente ingresa en la morgue. Obviamente, la capacidad de la **U.C.I.** y de la planta es limitada, por lo tanto, si un paciente tiene que ingresar en la **U.C.I.** y ésta se encuentra completamente ocupada, el paciente menos grave de la misma pasará a planta, y si sucede lo mismo con un ingreso en planta, se dará de alta al paciente con mejor estado de salud. Esta situación anómala (tener pacientes con gravedad **U.C.I.** en planta, será resuelta lo antes posible, volviendo dichos pacientes a U.C.I. a la primera oportunidad).

Las **operaciones** del TAD serán las siguientes:
- CrearHospital
- Ingreso
- Alta
- Muerte
- Pacientes en la U.C.I.
- Pacientes en la Planta
- Pacientes de una gravedad determinada
- Destruir hospital
