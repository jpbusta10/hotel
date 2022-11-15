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

nodoLista*borrarNodo(nodoLista*lista,char nombre [50])
{
    nodoLista*aBorrar=NULL;
    if(strcmp(lista->miCliente.nombre,nombre)==0)
    {
        aBorrar=lista;
        lista=lista->siguiente;
    }
    else
    {
        nodoLista*seguidora=lista;
        nodoLista*anterior=NULL;
        while((seguidora!=NULL)&&(strcmp(seguidora->miCliente.nombre,nombre)!=0))
        {
            anterior=seguidora;
            seguidora=seguidora->siguiente;
        }
        if(seguidora!=NULL)
        {
            anterior->siguiente=seguidora->siguiente;
            aBorrar=seguidora;
            free(aBorrar);
        }
    }
    return lista;
}
nodoLista*buscarNodo(nodoLista*lista,char nombre[50])
{
    nodoLista*buscado=NULL;///si es NULL no lo encuentra
    if(strcmp(lista->miCliente.nombre,nombre)==0)
    {
        buscado=lista;
    }
    else
    {
        nodoLista*seguidora=lista;
        while((seguidora!=NULL)&&(strcmp(seguidora->miCliente.nombre,nombre)!=0))
        {
            printf("entra al while\n");
            seguidora=seguidora->siguiente;
        }
        if(seguidora!=NULL)
        {
            buscado=seguidora;
        }
    }
    return buscado;

}

nodoLista* eliminarPri(nodoLista* lista){
    nodoLista* aBorrar=lista;
    if(lista!=NULL){
        lista=lista->siguiente;
        free(aBorrar);
    }
    return lista;
}
