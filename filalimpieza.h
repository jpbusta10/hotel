#ifndef FILALIMPIEZA_H_INCLUDED
#define FILALIMPIEZA_H_INCLUDED
#include "arbolHabitaciones.h"
#include <stdio.h>
#include <stdlib.h>
#define archivolimpieza "ArchivoLimpieza.bin"
#include <stdbool.h>
#include <time.h>

typedef struct{
    int estadoHabitacion;
    int numeroHabitacion;
}Limpieza;

typedef struct{
    Limpieza dato;
    struct NodoLimpieza* siguiente;
}NodoLimpieza;

typedef struct{
    NodoLimpieza* cabecera;
    NodoLimpieza* ultimo;
}FilaLimpieza;

typedef struct{
    char nombreEmpleado[20];
    int bajaLogica;/// 0 =limpia 1= sucia;
    int numeroHabitacion;
}BaseDatosLimpieza;

void muestraArbolSucias(nodoArbol*);
void mostrarListaLimpieza(NodoLimpieza*);
void mostrarNodoLimpieza(NodoLimpieza*);
NodoLimpieza* agregarPrincipioLimpieza(NodoLimpieza*,NodoLimpieza*);
NodoLimpieza* crearNodoLimpieza(Limpieza);
NodoLimpieza* agregarFinalLimpieza(NodoLimpieza*,NodoLimpieza*);
NodoLimpieza* borrarPrimero(NodoLimpieza* lista);
NodoLimpieza* extraer(FilaLimpieza*);
void AgregarFila(FilaLimpieza*,Limpieza);
void inicFila(FilaLimpieza*);
nodoArbol* buscarSucia(nodoArbol*);
void pasarArbolToFila(FilaLimpieza*,nodoArbol*);
void persistenciaSucias(BaseDatosLimpieza);
void levantarArchivo(FilaLimpieza*);
void limpiarHabitacion(FilaLimpieza*,nodoArbol*);
void mostrarArchivoSucias();
NodoLimpieza* inicListaLimpieza();
void cargarFilaAuto(FilaLimpieza* filin);
void empleadosLimpiezaRandom(char*);
#endif // FILALIMPIEZA_H_INCLUDED
