#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbolHabitaciones.h"
int main()
{
    nodoArbol*arbol=inicArbol();
    int habitacion=111;
    arbol=habitaciones(arbol,habitacion);
    inOrder(arbol);
    return 0;
}
