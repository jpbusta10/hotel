#include "hoteleria.h"

void checkIn(nodoArbol*arbol)///realizamos check in de habitacion
{
    nodoLista*nuevosClientes=inicListaCliente();
    cliente nuevoCliente;
    int cantidadClientes=0;///guardamos la cantidad de clientes
    char continuar;
    nodoArbol*habDesignada;

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
         habDesignada=buscarPorCapacidad(arbol,cantidadClientes);
         if(habDesignada!=NULL)
         {
             habDesignada->estado.condicion=1;
             habDesignada->estado.Listacliente=nuevosClientes;
             printf("\nqueda asignada la habitacion: [%i]\n",habDesignada->numeroHabitacion);
         }
         else
         {
             printf("\nno hay habitaciones disponibles\n");
         }
    }

}
