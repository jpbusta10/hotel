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
    bool menuLimpieza = true;
    bool menuEstadisticas = true;
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
        printf("5.estadisticas\n");
        printf("6.Buscar Habitacion\n");
        printf("7.Menu limpieza\n");
        printf("9.salir\n");
        scanf("%i",&option);
        system("cls");
        switch(option)
        {
            case 1:
                checkIn(arbol);
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
            case 5:
                menuEstadisticas = true;
                while(menuEstadisticas)
                {
                    float promedio=0;
                    int habitacionesOcupadas=0;
                    int acumulador=0;
                    float ocupacion=0;
                    printf("1.promedio de pasajeros por habitacion\n");
                    printf("2.ocupacion\n");
                    printf("9.volver al menu principal\n");
                    scanf("%i",&option);

                    switch(option)
                    {
                    case 1:
                        pasajerosPorHabitacion(arbol,&acumulador,&habitacionesOcupadas);
                        promedio = (float)acumulador / (float)habitacionesOcupadas;
                        printf("promedio pasajeros por habitacion: %.2f\n",promedio);
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        pasajerosPorHabitacion(arbol,&acumulador,&habitacionesOcupadas);
                        ocupacion = ((float)habitacionesOcupadas / (float)habitacionesHotel)*100;
                        printf("la ocupacion es de: %.2f %%\n",ocupacion);
                        system("pause");
                        system("cls");
                        break;

                    case 9:
                        menuEstadisticas = false;
                        system("pause");
                        system("cls");
                        break;

                    }
                }
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
                menuLimpieza = true;
                NodoLimpieza* auxiliar2=inicListaLimpieza();
                auxiliar2=despersistenciaLimpieza(auxiliar2);
                pasarListaAFila(&filin,auxiliar2);
                while(menuLimpieza)
                {
                    system("cls");
                    printf("1.limpiar una habitacion\n");
                    printf("2.ver habitaciones sucias\n");
                    printf("3.ver base de datos limpieza\n");
                    printf("4.volver al menu principal\n");
                    option = 0;
                    scanf("%i",&option);

                    switch(option)
                    {
                    case 1:
                        limpiarHabitacion(&filin,arbol);
                        system("pause");
                        break;
                    case 2:
                        mostrarArchivolimpieza();
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        mostrarBDL();
                        system("pause");
                        system("cls");
                    case 4:
                        menuLimpieza=false;
                        break;
                    }
                }
                system("cls");
                break;
            case 9:

                seguir=false;
                break;

        }
    }


    return 0;
}
