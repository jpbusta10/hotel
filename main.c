#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbolHabitaciones.h"
int main()
{
    nodoArbol*arbol;
    nodoArbol*inicArbol();
    int habitacion=200;
    arbol=cargaArbol(arbol,habitacion);
    habitacion=50;
    //arbol=cargaArbol(arbol,habitacion);
    muestraPreorder(arbol);
    return 0;
}
