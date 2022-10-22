#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[50];
    char DNI[7];
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
#endif // LISTA_H_INCLUDED
