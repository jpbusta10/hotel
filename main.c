#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbolHabitaciones.h"
#include "hoteleria.h"
int main()
{
    nodoArbol*arbol=inicArbol();
    int habitacionesHotel=300;
    arbol=habitaciones(arbol,habitacionesHotel);
    inOrder(arbol);
    nodoArbol*buscado=buscarPorHabitacion(arbol,40);


    return 0;
}
