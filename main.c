#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbolHabitaciones.h"
#include "hoteleria.h"
int main()
{
    srand(time(NULL));
    nodoArbol*arbol=inicArbol();
    int habitacionesHotel=300;
    arbol=habitaciones(arbol,habitacionesHotel);
    inOrder(arbol);
    nodoArbol*buscado=buscarPorCapacidad(arbol,300,4);
    printf("habitacion: %i , capacidad: %i \n",buscado->numeroHabitacion,buscado->estado.capacidad);



    return 0;
}
