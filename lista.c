#include "lista.h"

nodoLista*inicListaCliente()
{
    return NULL;
}

nodoLista*crearNodo(cliente nuevoCliente)
{
    nodoLista*nuevoNodo = (nodoLista*)malloc(sizeof(nodoLista));
    nuevoNodo->miCliente = nuevoCliente;
    nuevoNodo->siguiente=NULL;

    return nuevoNodo;
}

nodoLista*agregarPrincipio(nodoLista*lista,cliente nuevoCliente)
{
    nodoLista*nuevoNodo=crearNodo(nuevoCliente);

    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}
void mostrarNodo(nodoLista*aMostrar)
{
    printf("NOMBRE: %s\n",aMostrar->miCliente.nombre);
    printf("DNI: %s\n",aMostrar->miCliente.DNI);
    printf("CIUDAD DE ORIGEN: %s\n",aMostrar->miCliente.ciudadOrigen);

}
void mostrarLista(nodoLista*lista)
{
    nodoLista*seguidora=lista;
    while(seguidora!=NULL)
    {
        mostrarNodo(seguidora);
        printf("\n");
        seguidora=seguidora->siguiente;
    }
}

cliente cargaCliente()
{
    cliente nuevoCliente;
    printf("ingrese el nombre del cliente\n");
    fflush(stdin);
    gets(nuevoCliente.nombre);
    printf("ingrese el DNI\n");
    fflush(stdin);
    gets(nuevoCliente.DNI);
    printf("ingrese la ciudad de origen\n");
    fflush(stdin);
    gets(nuevoCliente.ciudadOrigen);
    return nuevoCliente;
}


