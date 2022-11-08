#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbolHabitaciones.h"
#include "hoteleria.h"
#include "filalimpieza.h"
#include <stdbool.h>
int main()
{
    FilaLimpieza filin;
    inicFila(&filin);
    srand(time(NULL));
    bool seguir = true;
    nodoArbol*arbol=inicArbol();
    nodoArbol*auxiliar;///auxiliar para buscar habitacion
    int habitacionesHotel=200;
    arbol=habitaciones(arbol,habitacionesHotel);
    arbol=despersistenciaClientesActuales(arbol);
    int option=0;
    int aux=0;
    while(seguir==true)
    {
        printf("1.realizar un check In\n");
        printf("2.realizar un check Out\n");
        printf("3.mostrar clientes hospedados\n");
        printf("4.mostrar base de clientes\n");
        printf("5.ver habitaciones sucias\n");
        printf("6.limpiar una habitacion\n");
        printf("7.archvo sucias\n");
        printf("9.salir\n");
        scanf("%i",&option);
        system("cls");
        switch(option)
        {
            case 1:
                checkIn(arbol);

                system("pause");
                system("cls");
                break;
            case 2:
                checkOut(arbol,&filin);
                system("pause");
                system("cls");
                break;
            case 3:
                muestraArbolOcupados(arbol);
                system("pause");
                system("cls");
                break;
            case 4:
                muestraArcivo(historial);
                system("pause");
                system("cls");
                break;
            case 6:
                printf("ingrese la habitacion que desea buscar..\n");
                scanf("%i",&aux);
                auxiliar=buscarPorHabitacion(arbol,aux);
                mostrarNodoArbol(auxiliar);
                system("pause");
                system("cls");
                break;
            case 7:
                cargarFilaAuto(&filin);
                mostrarArchivoSucias();
                system("pause");
                system("cls");
                break;
            case 9:

                seguir=false;
                break;

        }
    }



    return 0;
}
