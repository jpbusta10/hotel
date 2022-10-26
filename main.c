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
    checkIn(arbol);



    return 0;
}
