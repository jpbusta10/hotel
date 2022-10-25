#ifndef ARBOLHABITACIONES_H_INCLUDED
#define ARBOLHABITACIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct
{
    int condicion;///0 esta vacia
    int estadoLimpieza;//si es 0 esta limpio si es 1 es sucia
    int capacidad;
    nodoLista*Listacliente;
} habitacion;

typedef struct
{
    habitacion estado;
    int numeroHabitacion;
    struct nodoArbol*izquierda;
    struct nodoArbol*derecha;
} nodoArbol;
///prototipado

nodoArbol*inicArbol();
nodoArbol*crearNodoArbol(int dato);
nodoArbol*cargaArbol(nodoArbol*arbol,int numeroHabitacion);
void muestraPreorder(nodoArbol*arbol);
void inOrder(nodoArbol*arbol);
nodoArbol*habitaciones(nodoArbol*arbol,int cantidadHabitaciones);
nodoArbol*buscarPorHabitacion(nodoArbol*arbol,int habitacion);
nodoArbol*buscarPorCapacidad(nodoArbol*arbol,int totalHabitaciones,int capacidad);
#endif // ARBOLHABITACIONES_H_INCLUDED
