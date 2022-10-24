#ifndef ARBOLHABITACIONES_H_INCLUDED
#define ARBOLHABITACIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct
{
    int condicion;///1 esta vacia 0 esta llena
    int estadoLimpieza;//si es 0 esta limpio si es 1 es sucia
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

#endif // ARBOLHABITACIONES_H_INCLUDED
