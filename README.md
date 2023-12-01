# conecta4

Información entorno a la implementación:
El algoritmo Minimax se implementa en juegos de dos jugadores con reglas claras y definidas para tomar decisiones óptimas. Primero, se define la representación del estado del juego, las acciones posibles y la función de evaluación. Luego, el algoritmo utiliza la recursión para explorar todas las secuencias de acciones posibles, asumiendo que el oponente juega de manera óptima.
La toma de decisiones se realiza seleccionando la acción que maximiza o minimiza el valor del estado, dependiendo de si es el turno del jugador o del oponente.

Desiciones de diseño:
El diseño de este codigo es el siguiente: Se parte creando la clase nodo que almacena un puntero doble (tablero), y un vector de nodos, tambien un booleano para saber si es hoja o no.
Luego se genera el arbol de posibilidades en la clase GenerarArbol por medio de la recursion y otros algoritmos.
Se implementa el main donde se realiza el menu y los distintos requerimientos, estos requerimientos se van coordinando con la clase Sistema, en donde esta clase posee basicamente la estructura del juego, en donde se insertan fichas, se imprime el tablero, se evalua la jugada, se guarda o carga la partida, etc, y aca es donde se implementa el algoritmo minimax.

Resultados de prueba (Comparación de minimax con y sin poda):
Para la comparación entre un algoritmo minimax con y sin poda, puedo añadir que es bastante notoria, ya que su implementación optimiza demasiado el codigo, ya que al comparar tantos nodos como tenga la rama de posibilidades el tiempo de demora del programa se demora muchisimo, si bien, en mi algoritmo minimax sin poda se demuestra un retraso de segundos(2 a 3 segundos) cuando implemento esta mejora llamada poda alfa-beta, aparece instantaneamente la ficha insertada por la columna, por este motivo, podemos concluir que el algoritmo minimax trabaja mucho mejor cuando se le implementa poda mejorando su eficiencia.

