#ifndef ARBOLHABITACIONES_H_INCLUDED
#define ARBOLHABITACIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int condicion;///1 esta vacia 0 esta llena
    int estadoLimpieza;//si es 0 esta limpio si es 1 es sucia
    nodoLista*Listacliente;
}habitacion;

typedef struct
{
    habitacion estado;
    int numeroHabitacion;
    nodoArbol*izquierda;
    nodoArbol*derecha;
}nodoArbol;

#endif // ARBOLHABITACIONES_H_INCLUDED
