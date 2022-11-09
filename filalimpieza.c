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
    BaseDatosLimpieza aux;
    aux.bajaLogica=1;
    aux.numeroHabitacion=dato.numeroHabitacion;
    char* aux2;
    empleadosLimpiezaRandom(aux2);
    strcpy(aux.nombreEmpleado,aux2);
    persistenciaSucias(aux);
}

void empleadosLimpiezaRandom(char* aux){
    int numero=rand()%3+1;
    if(numero==1){
        strcpy(aux,"Nelida");
    }else if(numero==2){
        strcpy(aux,"Patricia");
    }else{
       strcpy(aux,"Pedro");
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

void persistenciaSucias(BaseDatosLimpieza dato){
    FILE* archi=fopen(archivolimpieza,"ab");
    if(archi!=NULL){
        fwrite(&dato,sizeof(BaseDatosLimpieza),1,archi);

    }
    fclose(archi);
}

void mostrarArchivoSucias(){
    FILE* archi=fopen(archivolimpieza,"rb");
    BaseDatosLimpieza aux;
    if(archi!=NULL){
        while(fread(&aux,sizeof(BaseDatosLimpieza),1,archi)>0){
            if(aux.bajaLogica==1){
                puts("------------\n");
                printf("numero habitacion: %d\n",aux.numeroHabitacion);
                printf("nombre empleado: %s\n",aux.nombreEmpleado);
                puts("-----------\n");
            }
        }
    }
    fclose(archi);
}

void levantarArchivo(FilaLimpieza* filin){
    FILE* archi=fopen(archivolimpieza,"rb");
    if(archi!=NULL){
        BaseDatosLimpieza aux;
        Limpieza aux2;
        while(fread(&aux,sizeof(BaseDatosLimpieza),1,archi)>0){
            aux2.estadoHabitacion=aux.bajaLogica;
            aux2.numeroHabitacion=aux.numeroHabitacion;
            AgregarFila(filin,aux2);
        }
        fclose(archi);
    }
}

void limpiarHabitacion(FilaLimpieza* filin,nodoArbol* arbol){
    NodoLimpieza* extraido;
    nodoArbol* comodin;
    BaseDatosLimpieza auxiliar;
    int flag=0;
    FILE* archi=fopen(archivolimpieza,"r+b");
    if(archi!=NULL){
        if(filin->cabecera!=NULL){
            extraido=extraer(filin);
            comodin=buscarPorHabitacion(arbol,extraido->dato.numeroHabitacion);
            comodin->estado.estadoLimpieza=0;
        }
        while((fread(&auxiliar,sizeof(BaseDatosLimpieza),1,archi)>0)&&(flag==0)){
            if(auxiliar.numeroHabitacion==extraido->dato.numeroHabitacion){
                flag=1;
            }
        }
        fseek(archi,-1,SEEK_CUR);
        auxiliar.bajaLogica=0;
        fwrite(&auxiliar,sizeof(BaseDatosLimpieza),1,archi);
        fclose(archi);
    }
    ///borrar habitacion de archivo
    ///
}



void cargarFilaAuto(FilaLimpieza* filin){
    Limpieza aux;
    int numerohabitacion;
    int i=0;
    while(i<10){
        numerohabitacion=rand()%100+1;
        aux.estadoHabitacion=1;
        aux.numeroHabitacion=numerohabitacion;
        puts("el problema es lo de abajo");
        AgregarFila(filin,aux);
        i++;
    }

}
