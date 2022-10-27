#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_MAX_HAB 5 ///cantidad maxima de personas por habitacion
typedef struct
{
    char nombre[50];
    char DNI[10];
    char ciudadOrigen[50];
}cliente;

typedef struct
{
    cliente miCliente;
    struct nodoLista*siguiente;
}nodoLista;
///prototipado

nodoLista*inicListaCliente();
nodoLista*crearNodo(cliente nuevoCliente);
nodoLista*agregarPrincipio(nodoLista*lista,cliente nuevoCliente);
void mostrarNodo(nodoLista*aMostrar);
void mostrarLista(nodoLista*lista);
cliente cargaCliente();
nodoLista*borrarNodo(nodoLista*lista,char nombre [50]);
nodoLista*buscarNodo(nodoLista*lista,char nombre[50]);
#endif // LISTA_H_INCLUDED
