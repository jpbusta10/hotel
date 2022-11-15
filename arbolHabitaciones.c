#include "arbolHabitaciones.h"

nodoArbol*inicArbol()
{
    return NULL;
}
nodoArbol*crearNodoArbol(int dato)
{
    nodoArbol*nuevoNodo = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevoNodo->derecha=NULL;
    nuevoNodo->izquierda=NULL;
    nuevoNodo->numeroHabitacion=dato;
    nuevoNodo->estado.Listacliente=inicListaCliente();
    nuevoNodo->estado.estadoLimpieza=0;
    nuevoNodo->estado.condicion=0;
    nuevoNodo->estado.capacidad=rand()%5+1;///generamos una capacidad de la habitacion de manera ramdom para simplificar las operaciones

    return nuevoNodo;
}

nodoArbol*cargaArbol(nodoArbol*arbol,int numeroHabitacion)
{
    nodoArbol*nuevoNodo=crearNodoArbol(numeroHabitacion);
    if(arbol==NULL)
    {
        arbol=nuevoNodo;
    }
    else
    {
        if(numeroHabitacion>arbol->numeroHabitacion)
        {
            arbol->derecha=cargaArbol(arbol->derecha,numeroHabitacion);
        }
        else
        {
            arbol->izquierda=cargaArbol(arbol->izquierda,numeroHabitacion);
        }
    }
    return arbol;
}
void muestraPreorder(nodoArbol*arbol)
{
    if(arbol!=NULL)
    {
        printf("[%i]",arbol->numeroHabitacion);
        muestraPreorder(arbol->izquierda);
        muestraPreorder(arbol->derecha);
    }
}
void inOrder(nodoArbol*arbol)
{
    if(arbol!=NULL)
    {
        inOrder(arbol->izquierda);
        printf("[%i]",arbol->numeroHabitacion);
        inOrder(arbol->derecha);
    }
}
nodoArbol*habitaciones(nodoArbol*arbol,int cantidadHabitaciones)///carga las habitaciones dependiendo de cuantas queramos
{
    int primerElemento=cantidadHabitaciones/2;
    arbol=cargaArbol(arbol,primerElemento);
    for(int i=1; i<=cantidadHabitaciones; i++)
    {
        if(i!=primerElemento)
        {
            arbol=cargaArbol(arbol,i);
        }
    }
    return arbol;
}
nodoArbol*buscarPorHabitacion(nodoArbol*arbol,int habitacion)
{
    nodoArbol*rta=NULL;
    if (arbol!=NULL)
    {
        if(habitacion==arbol->numeroHabitacion)
        {
            rta=arbol;
        }
        else
        {
            if(habitacion>arbol->numeroHabitacion)
            {
                rta=buscarPorHabitacion(arbol->derecha,habitacion);
            }
            else
            {
                rta=buscarPorHabitacion(arbol->izquierda,habitacion);
            }
        }

    }
    return rta;
}
nodoArbol*buscarPorCapacidad(nodoArbol*arbol,int capacidad)///devuelve la primer habitacion libre y limpia con esa capacidad
{
    nodoArbol*rta=NULL;
    if(arbol!=NULL)
    {
        if((arbol->estado.capacidad>=capacidad)&&(arbol->estado.condicion==0)&&(arbol->estado.estadoLimpieza==0))
        {
            rta=arbol;
        }
        else
        {
            rta=buscarPorCapacidad(arbol->izquierda,capacidad);
            if(rta==NULL)
            {
                rta=buscarPorCapacidad(arbol->derecha,capacidad);
            }
        }
    }
    return rta;
}

void mostrarNodoArbol(nodoArbol*aMostrar)
{
    printf("\nnumero habitacion: %i\n",aMostrar->numeroHabitacion);
    if(aMostrar->estado.condicion==1)
    {
        printf("condicion: ocupada\n");
    }
    else
    {
        printf("condicion: desocupada\n");
    }
    if(aMostrar->estado.estadoLimpieza==0)
    {
        printf("limpia\n");
    }
    else
    {
        printf("sucia\n");
    }
    if(aMostrar->estado.Listacliente!=NULL)
    {
        printf("clientes:\n");
        mostrarLista(aMostrar->estado.Listacliente);
    }

}

void muestraArbolOcupados(nodoArbol*arbol)
{
    if(arbol!=NULL)
    {
        if(arbol->estado.condicion==1)
        {
            mostrarNodoArbol(arbol);
        }
        muestraArbolOcupados(arbol->izquierda);
        muestraArbolOcupados(arbol->derecha);

    }
}
nodoListaInt*inicListaInt()
{
    return NULL;
}
nodoListaInt*crearNodoListaInt(int dato)
{
    nodoListaInt*nuevoNodo = (nodoListaInt*)malloc(sizeof(nodoListaInt));
    nuevoNodo->dato=dato;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}
nodoListaInt*agregarPrincipioListaInt(nodoListaInt*lista, int dato)
{
    nodoListaInt*nuevoNodo = crearNodoListaInt(dato);
    if(lista==NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}
void pasajerosPorHabitacion(nodoArbol*arbol,float*promedio)///retorna el promedio de pasajeros por habitacion
{
    nodoListaInt*pasajerosPHab = inicListaInt();///cantidad de pasajeros por habitacion
    int habitacionesOcupadas = 0;
    int cantidadPasajeros;
    int acumulador=0;
    nodoLista*seguidora;
    if(arbol!=NULL)
    {
        if(arbol->estado.condicion==1)
        {
            habitacionesOcupadas++;
            seguidora=arbol->estado.Listacliente;
            while(seguidora!=NULL)
            {
                seguidora=seguidora->siguiente;
                cantidadPasajeros++;
            }
            pasajerosPHab=agregarPrincipioListaInt(pasajerosPHab,cantidadPasajeros);
            cantidadPasajeros=0;
        }
        pasajerosPorHabitacion(arbol->izquierda,promedio);
        pasajerosPorHabitacion(arbol->derecha,promedio);
    }
    else
    {
        while(pasajerosPHab!=NULL)
        {
            acumulador=acumulador=pasajerosPHab->dato;
            pasajerosPHab = pasajerosPHab->siguiente;
        }
        (*promedio) = (float)acumulador / (float)habitacionesOcupadas;
    }
}
