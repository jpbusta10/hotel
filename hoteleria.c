#include "hoteleria.h"

void checkIn(nodoArbol*arbol)///realizamos check in de habitacion
{
    nodoLista*nuevosClientes=inicListaCliente();
    cliente nuevoCliente;
    int cantidadClientes=0;///guardamos la cantidad de clientes
    char continuar;
    int cantHabitaciones;
    char auxiliar[50];
    nodoArbol*hab;

    do///cargamos la lista con los clientes
    {
        nuevoCliente=cargaCliente();
        nuevosClientes=agregarPrincipio(nuevosClientes,nuevoCliente);
        cantidadClientes++;
        printf("desea agregar mas clientes?\n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    while(continuar=='s'||continuar=='S');

    printf("\ncuantas habitaciones desea?\n");
    scanf("%i",&cantHabitaciones);

    while(cantHabitaciones!=0)
    {
        printf("\nprimer habitacion:\n");
        mostrarLista(nuevosClientes);
        printf("\nelija el huesped:\n");
        gets(auxiliar);
        nodoLista*seguidora=nuevosClientes;
       /* while(seguidora!=NULL)
        {

        }*/

    }
    }
