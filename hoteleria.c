#include "hoteleria.h"

void checkIn(nodoArbol*arbol)///realizamos check in de habitacion
{
    nodoLista*nuevosClientes=inicListaCliente();
    cliente nuevoCliente;
    int cantidadClientes=0;///guardamos la cantidad de clientes
    char continuar;
    int cantHabitaciones;
    int huespedesEnHabitacion;
    char auxiliar[50];
    nodoArbol*hab;

    do///cargamos la lista con los clientes
    {
        system("cls");
        nuevoCliente=cargaCliente();
        nuevosClientes=agregarPrincipio(nuevosClientes,nuevoCliente);
        cantidadClientes++;
        printf("desea agregar mas clientes? s/n\n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    while(continuar=='s'||continuar=='S');
    system("cls");
    printf("\ncuantas habitaciones desea?\n");
    scanf("%i",&cantHabitaciones);
    system("cls");
    for(int i=0; i<cantHabitaciones; i++) ///iteramos hasta que se tengan todas las habitaciones requeridas
    {
        printf("\nhabitacion: %i\n",i+1);
        printf("cuantos huespedes en la habitacion?\n");
        scanf("%i",&huespedesEnHabitacion);
        hab=buscarPorCapacidad(arbol,huespedesEnHabitacion);///asigno la habitacion de acuerdo a la capacidad que busco
        hab->estado.condicion=1;
        nodoLista*clientesHabitacion=inicListaCliente();
        nodoLista*buscado=NULL;
        for(int i=0; i<huespedesEnHabitacion; i++)///itero para cargar la cantidad que quiero en la habitacion
        {
            buscado=NULL;
            while(buscado==NULL)///para seleccionar el cliente que deseo mientras este en la lista que tengo
            {
                system("cls");
                printf("\ningrese el nombre del huesped de estos.\n");
                mostrarLista(nuevosClientes);
                fflush(stdin);
                gets(auxiliar);
                buscado=buscarNodo(nuevosClientes,auxiliar);
            }
            clientesHabitacion=agregarPrincipio(clientesHabitacion,buscado->miCliente);
            nuevosClientes=borrarNodo(nuevosClientes,buscado->miCliente.nombre);

        }
        hab->estado.Listacliente=clientesHabitacion;///agrego la lista de clientes a la de la habitacion
        system("cls");
        mostrarNodoArbol(hab);
        system("pause");
    }
}
