#include "filalimpieza.h"


NodoLimpieza* crearNodoLimpieza(Limpieza dato){
    NodoLimpieza* aux=malloc(sizeof(NodoLimpieza));
    aux->dato=dato;
    aux->siguiente=NULL;
    return aux;
}

NodoLimpieza* agregarPrincipioLimpieza(NodoLimpieza* lista,NodoLimpieza* nuevonodo){
    if(lista==NULL){
        lista=nuevonodo;
    }else{
        nuevonodo->siguiente=lista;
        lista=nuevonodo;
    }
    return lista;
}

NodoLimpieza* agregarFinalLimpieza(NodoLimpieza* lista,NodoLimpieza*nn){
    if(lista==NULL){
        lista=nn;
    }else{
        NodoLimpieza* seguidora=lista;
        while(seguidora->siguiente!=NULL){
            seguidora=seguidora->siguiente;
        }
        seguidora->siguiente=nn;
    }
    return lista;
}

void mostrarNodoLimpieza(NodoLimpieza*aMostrar){
    printf("Numero Habitacion: %i\n",aMostrar->dato.numeroHabitacion);
    printf("Estado Habitacion: %i\n",aMostrar->dato.estadoHabitacion);
}

void mostrarListaLimpieza(NodoLimpieza*lista){
    NodoLimpieza*seguidora=lista;
    while(seguidora!=NULL){
        puts("-----ENTRO------\n");
        mostrarNodoLimpieza(seguidora);
        printf("\n");
        seguidora=seguidora->siguiente;
    }
}

NodoLimpieza* inicListaLimpieza(){
    return NULL;
}

void inicFila(FilaLimpieza* fila){
    fila->cabecera=inicListaLimpieza();
    fila->ultimo=inicListaLimpieza();
}

void AgregarFila(FilaLimpieza*filin,Limpieza dato){
    NodoLimpieza* nuevo=crearNodoLimpieza(dato);
    if(filin->cabecera==NULL){
        filin->cabecera=nuevo;
        filin->ultimo=nuevo;
    } else{
        filin->cabecera=agregarFinalLimpieza(filin->cabecera,nuevo);
        filin->ultimo=nuevo;
    }
}

NodoLimpieza* extraer(FilaLimpieza*filin){
    NodoLimpieza* rsp=inicListaCliente();
    if(filin->cabecera!=NULL){
        rsp=filin->cabecera;
        filin->cabecera=borrarPrimero(filin->cabecera);
        if(filin->cabecera==NULL){
            filin->ultimo=inicListaLimpieza();
        }
    }
    return rsp;
}

NodoLimpieza* borrarPrimero(NodoLimpieza* lista){
    NodoLimpieza* aborrar=lista;
    if(lista!=NULL){
        lista=lista->siguiente;
        free(aborrar);
    }
    return lista;
}

nodoArbol* buscarSucia(nodoArbol* arbol){
    nodoArbol* rta=NULL;
    if(arbol!=NULL){
        if(arbol->estado.estadoLimpieza==1){
            rta=arbol;
        }else{
            rta=buscarSucia(arbol->izquierda);
            if(rta==NULL){
                rta=buscarSucia(arbol->derecha);
            }
        }
    }
    return rta;
}

void muestraArbolSucias(nodoArbol*arbol){
    if(arbol!=NULL)
    {
        if(arbol->estado.estadoLimpieza==1)
        {
            puts("-----MUESTRA-ARBOL-SUCIAS------\n");
            printf("numero habitacion: %d\n",arbol->numeroHabitacion);
            puts("-----------\n");
        }else{
            muestraArbolSucias(arbol->izquierda);
            muestraArbolSucias(arbol->derecha);
        }
    }
}

void pasarArbolToFila(FilaLimpieza* fila,nodoArbol* arbol){
    Limpieza aux;
    nodoArbol* aLimpiar=buscarSucia(arbol);
    if(aLimpiar!=NULL){
        aux.estadoHabitacion=aLimpiar->estado.estadoLimpieza;
        aux.numeroHabitacion=aLimpiar->numeroHabitacion;
        AgregarFila(fila,aux);
        pasarArbolToFila(fila,arbol->izquierda);
        pasarArbolToFila(fila,arbol->derecha);
    }else{
        printf("no hay habitaciones sucias\n");
    }
}

void persistenciaSucias(FilaLimpieza filin){
    FILE* archi=fopen(archivolimpieza,"ab");
    Limpieza cargador;
    if(archi!=NULL){
        while(filin.cabecera!=NULL){
            NodoLimpieza* aux=extraer(&filin);
            if(aux!=NULL){
                cargador.estadoHabitacion=aux->dato.estadoHabitacion;
                cargador.numeroHabitacion=aux->dato.numeroHabitacion;
                fwrite(&cargador,sizeof(Limpieza),1,archi);
                puts("-----cargo-un-dato----\n");
            }
        }
    }
    fclose(archi);
}


void mostrarArchivoSucias(){
    FILE* archi=fopen(archivolimpieza,"rb");
    Limpieza aux;
    if(archi!=NULL){
        while(fread(&aux,sizeof(Limpieza),1,archi)>0){
            puts("----MOSTRAR-ARCHIVO-------\n");
            printf("numero habitacion: %d\n",aux.numeroHabitacion);
            puts("-----------\n");
        }
    }
    printf("salio del while");
    fclose(archi);
}

void levantarArchivo(FilaLimpieza* filin){
    FILE* archi=fopen(archivolimpieza,"rb");
    if(archi!=NULL){
        Limpieza aux;
        while(fread(&aux,sizeof(Limpieza),1,archi)>0){
            AgregarFila(filin,aux);
        }
        fclose(archi);
    }
    FILE* archi2=fopen(archivolimpieza,"wb");
    fclose(archi2);
}

void limpiarHabitaciones(FilaLimpieza* filin,nodoArbol* arbol){
    NodoLimpieza* extraido;
    nodoArbol* comodin;
    while(filin->cabecera!=NULL){
        extraido=extraer(filin);
        comodin=buscarPorHabitacion(arbol,extraido->dato.numeroHabitacion);
        comodin->estado.estadoLimpieza=0;
    }

}

void cargarFilaAuto(FilaLimpieza* filin){
    Limpieza aux;
    int numerohabitacion;
    int i=0;
    while(i<10){
        numerohabitacion=rand()%100+1;
        aux.estadoHabitacion=1;
        aux.numeroHabitacion=numerohabitacion;

        AgregarFila(filin,aux);

        i++;
    }

}
