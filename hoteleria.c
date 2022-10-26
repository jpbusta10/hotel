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

    for(int i=0;i<cantHabitaciones;i++)///iteramos hasta que se tengan todas las habitaciones requeridas
    {
        printf("\nhabitacion: %i\n",i+1);
        printf("cuantos huespedes en la habitacion?\n");
        scanf("%i",&huespedesEnHabitacion);
        nodoLista*clientesHabitacion=inicListaCliente();
        nodoLista*buscado=NULL;
        for(int i=0; i<huespedesEnHabitacion; i++)
        {
            buscado=NULL;
            while(buscado==NULL)
            {
                printf("\ningrese el nombre del huesped de estos.\n");
                mostrarLista(nuevosClientes);
                fflush(stdin);
                gets(auxiliar);
                buscado=buscarNodo(nuevosClientes,auxiliar);
            }
            clientesHabitacion=agregarPrincipio(clientesHabitacion,buscado->miCliente);
            nuevosClientes=borrarNodo(nuevosClientes,buscado->miCliente.nombre);
            hab=buscarPorCapacidad(arbol,huespedesEnHabitacion);
            hab->estado.Listacliente=clientesHabitacion;
            hab->estado.condicion=1;
            mostrarNodoArbol(hab);
        }



    }
}
