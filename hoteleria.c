#include "hoteleria.h"

nodoArbol*checkIn(nodoArbol*arbol)///realizamos check in de habitacion
{
    nodoLista*nuevosClientes=inicListaCliente();
    cliente nuevoCliente;
    int cantidadClientes=0;///guardamos la cantidad de clientes
    char continuar;

    do///cargamos la lista con los clientes
    {
        nuevoCliente=cargaCliente();
        nuevosClientes=agregarPrincipio(nuevosClientes,nuevoCliente);
        cantidadClientes++;
        printf("desea agregar mas clientes?\n");
        fflush(stdin);
        scanf("%c",&continuar);
    }while(continuar=='s'||continuar=='S');

    if(cantidadClientes<=5)
    {

    }


}
