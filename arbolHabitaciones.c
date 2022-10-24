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
nodoArbol*habitaciones(nodoArbol*arbol,int cantidadHabitaciones)///carga la habitaciones
{
    int primerElemento=cantidadHabitaciones/2;
    arbol=cargaArbol(arbol,primerElemento);
    for(int i=0;i<=cantidadHabitaciones;i++)
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







