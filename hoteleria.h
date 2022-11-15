#ifndef HOTELERIA_H_INCLUDED
#define HOTELERIA_H_INCLUDED
#include "arbolHabitaciones.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define historial "historialClientes.bin"
#define clientesActuales "clienteshospedados.bin"
#include "filalimpieza.h"
typedef struct
{
    char nombre[50];
    char dni[10];
    char ciudadOrigen[100];
    int habitacion;
}baseClientes;
typedef struct
{
    baseClientes dato;
    struct nodoListaBase*siguiente;
}nodoListaBase;



///prototipados
void checkIn(nodoArbol*arbol);
void checkOut(nodoArbol*arbol,FilaLimpieza* filin);
void persistenciaCliente(nodoArbol*nodo,char nombreArchivo[100]);
void muestraArcivo(char nombreArchivo[100]);
nodoArbol*despersistenciaClientesActuales(nodoArbol*arbol);
nodoListaBase*inicListaBase();
nodoListaBase*agregarPrincipioBase(nodoListaBase*lista,baseClientes dato);
void mostrarListaBase(nodoListaBase*aMostrar);
void mostrarListaBase(nodoListaBase*lista);
nodoListaBase*borrarNodoBase(nodoListaBase*lista,int habitacion);
void borrarDeHospedados(int habitacion);///borra del archivo de hospedadosActuales
int buscarNodoHabitacion(nodoListaBase*lista,int habitacion);
nodoListaBase*borramosListaHab(nodoListaBase*lista,int habitacion);
void menuEstadisticas(nodoArbol*);
#endif // HOTELERIA_H_INCLUDED
