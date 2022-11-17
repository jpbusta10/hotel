#include "filalimpieza.h"


NodoLimpieza* crearNodoLimpieza(Limpieza dato)
{
    NodoLimpieza* aux=malloc(sizeof(NodoLimpieza));
    aux->dato=dato;
    aux->siguiente=NULL;
    return aux;
}

NodoLimpieza* agregarPrincipioLimpieza(NodoLimpieza* lista,NodoLimpieza* nuevonodo)
{
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        nuevonodo->siguiente=lista;
        lista=nuevonodo;
    }
    return lista;
}

NodoLimpieza* agregarFinalLimpieza(NodoLimpieza* lista,NodoLimpieza*nn)
{
    if(lista==NULL)
    {
        lista=nn;
    }
    else
    {
        NodoLimpieza* seguidora=lista;
        while(seguidora->siguiente!=NULL)
        {
            seguidora=seguidora->siguiente;
        }
        seguidora->siguiente=nn;
    }
    return lista;
}

void mostrarNodoLimpieza(NodoLimpieza*aMostrar)
{
    printf("Numero Habitacion: %i\n",aMostrar->dato.numeroHabitacion);
    printf("Estado Habitacion: %i\n",aMostrar->dato.estadoHabitacion);
}

void mostrarListaLimpieza(NodoLimpieza*lista)
{
    NodoLimpieza*seguidora=lista;
    while(seguidora!=NULL)
    {
        puts("-----------\n");
        mostrarNodoLimpieza(seguidora);
        printf("\n");
        seguidora=seguidora->siguiente;
    }
}

NodoLimpieza* inicListaLimpieza()
{
    return NULL;
}

void inicFila(FilaLimpieza* fila)
{
    fila->cabecera=inicListaLimpieza();
    fila->ultimo=inicListaLimpieza();
}

void AgregarFila(FilaLimpieza*filin,Limpieza dato)
{
        NodoLimpieza* nuevo=crearNodoLimpieza(dato);
        if(filin->cabecera==NULL)
        {
            filin->cabecera=nuevo;
            filin->ultimo=nuevo;
        }
        else
        {
            filin->cabecera=agregarFinalLimpieza(filin->cabecera,nuevo);
            filin->ultimo=nuevo;
        }

}
void empleadosLimpiezaRandom(char* aux)
{
    int numero=rand()%3+1;
    if(numero==1)
    {
        strcpy(aux,"Nelida");
    }
    else if(numero==2)
    {
        strcpy(aux,"Patricia");
    }
    else
    {
        strcpy(aux,"Pedro");
    }
}

Limpieza extraer(FilaLimpieza*filin)
{
    Limpieza rsp;
    if(filin->cabecera!=NULL)
    {
        rsp=filin->cabecera->dato;
        filin->cabecera=borrarPrimero(filin->cabecera);
        if(filin->cabecera==NULL)
        {
            filin->ultimo=inicListaLimpieza();
        }
    }
    return rsp;
}

NodoLimpieza* borrarPrimero(NodoLimpieza* lista)
{
    NodoLimpieza* aborrar=lista;
    if(lista!=NULL)
    {
        lista=lista->siguiente;
        free(aborrar);
    }
    return lista;
}


void persistenciaLimpias(BaseDatosLimpieza dato)
{
    BaseDatosLimpieza aux;
    FILE* archi=fopen(archivolimpieza,"a+b");
    int flag=0;
    if(archi!=NULL)
    {
        fwrite(&dato,sizeof(BaseDatosLimpieza),1,archi);
    }
    fclose(archi);
}



void mostrarBDL()
{
    FILE* archi=fopen(archivolimpieza,"rb");
    BaseDatosLimpieza aux;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(BaseDatosLimpieza),1,archi)>0)
        {
                puts("------------\n");
                printf("numero habitacion: %d\n",aux.numeroHabitacion);
                printf("empleado: %s\n",aux.nombreEmpleado);
                printf("condicion: %d\n",aux.bajaLogica);
                puts("-----------\n");
        }
    }
    fclose(archi);
}

void limpiarHabitacion(FilaLimpieza* filin,nodoArbol* arbol)
{
    Limpieza extraido;
    nodoArbol* comodin;
    BaseDatosLimpieza auxiliar;
    if(filin->cabecera!=NULL){
            extraido=extraer(filin);
            printf("extraido: %d\n",extraido.numeroHabitacion);
            comodin=buscarPorHabitacion(arbol,extraido.numeroHabitacion);
            comodin->estado.estadoLimpieza=0;
            strcpy(auxiliar.nombreEmpleado,extraido.nombreEmpleado);
            auxiliar.bajaLogica=0;
            auxiliar.numeroHabitacion=extraido.numeroHabitacion;
            puts("------------\n");
            printf("La habitacion se ha limpiado correctamente\n");
            printf("numero habitacion: %d\n",auxiliar.numeroHabitacion);
            printf("nombre empleado: %s\n",auxiliar.nombreEmpleado);
            puts("-----------\n");
            persistenciaLimpias(auxiliar);

    }else{
        printf("no hay habitaciones sucias\n");
    }
}


void limpiarTodas(FilaLimpieza* filin,nodoArbol* arbol){
    if(filin->cabecera!=NULL){
        while(filin->cabecera!=NULL){
            limpiarHabitacion(filin,arbol);
        }
    }
}


void cargarFilaAuto(FilaLimpieza* filin)
{
    Limpieza aux;
    int numerohabitacion;
    int i=0;
    while(i<5)
    {
        numerohabitacion=rand()%100+1;
        aux.estadoHabitacion=1;
        aux.numeroHabitacion=numerohabitacion;
        empleadosLimpiezaRandom(aux.nombreEmpleado);
        AgregarFila(filin,aux);
        i++;
    }

}

NodoLimpieza* despersistenciaLimpieza(NodoLimpieza* nodin){
    FILE* archi=fopen(archivolimpieza,"rb");
    BaseDatosLimpieza aux;
    if(archi!=NULL){
        while(fread(&aux,sizeof(BaseDatosLimpieza),1,archi)>0){
            Limpieza aux2;
            aux2.estadoHabitacion=aux.bajaLogica;
            aux2.numeroHabitacion=aux.numeroHabitacion;
            strcpy(aux2.nombreEmpleado,aux.nombreEmpleado);
            NodoLimpieza* auxiliar=crearNodoLimpieza(aux2);
            nodin=agregarPrincipioLimpieza(nodin,auxiliar);
        }
    }
    fclose(archi);
   return nodin;
}

void limpiezaPorEmpleado(){
    char b=219,a=177;
    NodoLimpieza* auxiliar2=inicListaLimpieza();
    auxiliar2=despersistenciaLimpieza(auxiliar2);
    int contador=0;
    int patri=0,pedro=0,neli=0;
    if(auxiliar2!=NULL){
            while(auxiliar2!=NULL){
                if(auxiliar2->dato.estadoHabitacion==0){
                    contador++;
                    if(strcmp(auxiliar2->dato.nombreEmpleado,"Patricia")==0){
                        patri++;
                    }else if(strcmp(auxiliar2->dato.nombreEmpleado,"Nelida")==0){
                        neli++;
                    }else{
                        pedro++;
                    }
                    auxiliar2=borrarPrimero(auxiliar2);
                }else{
                    auxiliar2=borrarPrimero(auxiliar2);
                }
            }
    }
    float porcentajepatri,porcentajepedro,porcentajeneli;
    porcentajeneli=((float)neli/(float)contador)*100;
    porcentajepedro=((float)pedro/(float)contador)*100;
    porcentajepatri=((float)patri/(float)contador)*100;
    printf("\nPatri: %.2f %%",porcentajepatri);
    printf("\r");
    printf("\t\t\t");
    for (int i = 0; i < contador; i++) {
        printf("%c", a);
    }
    printf("\r");
    printf("\t\t\t");
    for (int i = 0; i < patri; i++) {
        printf("%c", b);

    }
    printf("\ncantidad de habitaciones limpiadas: %i\n",patri);
    printf("\nPedro: %.2f %%",porcentajepedro);
    printf("\r");
    printf("\t\t\t");
    for (int i = 0; i < contador; i++) {
        printf("%c", a);
    }
    printf("\r");
    printf("\t\t\t");
    for (int i = 0; i < pedro; i++) {
        printf("%c", b);

    }
    printf("\ncantidad de habitaciones limpiadas: %i\n",pedro);
    printf("\nNelida: %.2f %% ",porcentajeneli);
     printf("\r");
    printf("\t\t\t");
    for (int i = 0; i < contador; i++) {
        printf("%c", a);
    }
    printf("\r");
    printf("\t\t\t");
    for (int i = 0; i < neli; i++) {
        printf("%c", b);

    }
    printf("\ncantidad de habitaciones limpiadas: %i\n",neli);
    printf("\n");
    system("pause");
}
