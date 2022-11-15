#include "hoteleria.h"
#include "filalimpieza.h"
void checkIn(nodoArbol*arbol)///realizamos check in de habitacion
{
    nodoLista*nuevosClientes=inicListaCliente();
    cliente nuevoCliente;
    int cantidadClientes=0;///guardamos la cantidad de clientes
    char continuar;
    int cantHabitaciones=100;
    int huespedesEnHabitacion=0;
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
    continuar='s';
    printf("\ncuantas habitaciones desea?\n");
    while(cantHabitaciones>cantidadClientes)
    {
        scanf("%i",&cantHabitaciones);
        if(cantHabitaciones>cantidadClientes)
        {
            printf("no puede ingresar tantas habitacion. \nTrate de nuevo\n");
        }
    }
    system("cls");
    if(cantHabitaciones==1){
        hab=buscarPorCapacidad(arbol,huespedesEnHabitacion);
        hab->estado.condicion=1;
        while(nuevosClientes!=NULL){
            hab->estado.Listacliente=agregarPrincipio(hab->estado.Listacliente,nuevosClientes->miCliente);
            persistenciaCliente(hab,clientesActuales);
            nuevosClientes=eliminarPri(nuevosClientes);
        }
        mostrarNodoArbol(hab);
        system("pause");
    }else{
        for(int i=0; i<cantHabitaciones; i++) ///iteramos hasta que se tengan todas las habitaciones requeridas
        {
            if(cantidadClientes!=cantHabitaciones){
                while(continuar=='s'){
                    printf("\nhabitacion: %i\n",i+1);
                    printf("cuantos huespedes en la habitacion?\n");
                    scanf("%i",&huespedesEnHabitacion);
                    if(huespedesEnHabitacion>6){
                            printf("no se puede ingresar esa cantidad, intente de nuevo\n");
                            system("pause");
                            system("cls");
                        continuar='s';
                    }else{
                        continuar='n';
                    }
                }
            }else{
                huespedesEnHabitacion=1;
            }
            hab=buscarPorCapacidad(arbol,huespedesEnHabitacion);///asigno la habitacion de acuerdo a la capacidad que busco
            hab->estado.condicion=1;
            nodoLista*clientesHabitacion=inicListaCliente();
            nodoLista*buscado=NULL;
            if(huespedesEnHabitacion==1){
                hab->estado.Listacliente=crearNodo(nuevosClientes->miCliente);
                nuevosClientes=eliminarPri(nuevosClientes);
                persistenciaCliente(hab,clientesActuales);
                system("cls");
                mostrarNodoArbol(hab);
                system("pause");
            }else{
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
                persistenciaCliente(hab,clientesActuales);
                system("cls");
                mostrarNodoArbol(hab);
                system("pause");
            }
        }
    }
}

void checkOut(nodoArbol*arbol,FilaLimpieza* filin)
{
    int numeroHabitacion=0;
    nodoArbol*habitacion=NULL;
    printf("habitaciones ocupada:\n");
    muestraArbolOcupados(arbol);
    Limpieza dato;
    inicFila(&filin);
    while(habitacion==NULL)
    {
        printf("A que habitacion desea realizarle el checkout?\n");
        scanf("%i",&numeroHabitacion);
        habitacion=buscarPorHabitacion(arbol,numeroHabitacion);
    }
    system("cls");
    if(habitacion->estado.condicion==1)
    {
        mostrarNodoArbol(habitacion);
        persistenciaCliente(habitacion,historial);
        borrarDeHospedados(habitacion->numeroHabitacion);
        habitacion->estado.condicion=0;
        habitacion->estado.Listacliente=inicListaCliente();
        habitacion->estado.estadoLimpieza=1;
        dato.estadoHabitacion=1;
        dato.numeroHabitacion=habitacion->numeroHabitacion;
        AgregarFila(&filin,dato);
        mostrarNodoArbol(habitacion);

    }
    else
    {
        printf("la habitacion esta vacia\n");
    }
}
void persistenciaCliente(nodoArbol*nodo,char nombreArchivo[100])
{
    FILE* fp;
    fp=fopen(nombreArchivo,"ab");
    baseClientes nuevoCliente;
    if(fp!=NULL)
    {
        nodoLista*lista=nodo->estado.Listacliente;
        while(lista!=NULL)
        {
            strcpy(nuevoCliente.nombre,lista->miCliente.nombre);
            strcpy(nuevoCliente.dni,lista->miCliente.DNI);
            strcpy(nuevoCliente.ciudadOrigen,lista->miCliente.ciudadOrigen);
            nuevoCliente.habitacion=nodo->numeroHabitacion;
            fwrite(&nuevoCliente,sizeof(baseClientes),1,fp);
            lista=lista->siguiente;
        }
        fclose(fp);
    }
}
void muestraArcivo(char nombreArchivo[100])
{
    FILE*fp;
    fp=fopen(nombreArchivo,"rb");
    baseClientes aMostrar;
    if(fp!=NULL)
    {
        while(fread(&aMostrar,sizeof(baseClientes),1,fp)>0)
        {
            printf("-----------------------------------------\n");
            printf("NOMBRE: %s\n",aMostrar.nombre);
            printf("DNI: %s\n",aMostrar.dni);
            printf("CIUDAD ORIGEN: %s\n",aMostrar.ciudadOrigen);
            printf("HABITACION: %i\n",aMostrar.habitacion);
        }
        fclose(fp);
    }
}
nodoArbol*despersistenciaClientesActuales(nodoArbol*arbol)
{
    baseClientes base;
    cliente nuevoCliente;
    nodoArbol*buscado;
    FILE*fp;
    fp=fopen(clientesActuales,"rb");
    if(fp!=NULL)
    {
        while(fread(&base,sizeof(baseClientes),1,fp)>0)
        {
            buscado=buscarPorHabitacion(arbol,base.habitacion);
            buscado->estado.condicion=1;
            strcpy(nuevoCliente.nombre,base.nombre);
            strcpy(nuevoCliente.DNI,base.dni);
            strcpy(nuevoCliente.ciudadOrigen,base.ciudadOrigen);
            buscado->estado.Listacliente=agregarPrincipio(buscado->estado.Listacliente,nuevoCliente);
        }
        fclose(fp);
    }
    return arbol;
}
nodoListaBase*inicListaBase()
{
    return NULL;
}
nodoListaBase*crearNodoBase(baseClientes dato)
{
    nodoListaBase*nuevoNodo=(nodoListaBase*)malloc(sizeof(nodoListaBase));
    nuevoNodo->dato=dato;
    nuevoNodo->siguiente=NULL;
    return nuevoNodo;
}
nodoListaBase*agregarPrincipioBase(nodoListaBase*lista,baseClientes dato)
{
    nodoListaBase*nuevoNodo=crearNodoBase(dato);

    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente=lista;
        lista=nuevoNodo;
    }
    return lista;
}
void mostrarNodoBase(nodoListaBase*aMostrar)
{
    printf("NOMBRE: %s\n",aMostrar->dato.nombre);
    printf("DNI: %s\n",aMostrar->dato.dni);
    printf("CIUDAD ORIGEN: %s\n",aMostrar->dato.ciudadOrigen);
    printf("HABITACION: %i\n",aMostrar->dato.habitacion);
}
void mostrarListaBase(nodoListaBase*lista)
{
    nodoListaBase*seguidora=lista;
    while(seguidora!=NULL)
    {
        mostrarNodoBase(seguidora);
        printf("\n");
        seguidora=seguidora->siguiente;
    }
}
int buscarNodoHabitacion(nodoListaBase*lista,int habitacion)
{
    int rta = 0;///si es 1 se encuentra el nodo
    while((lista!=NULL)&&(lista->dato.habitacion!=habitacion))
    {
        lista=lista->siguiente;
    }
    if(lista!=NULL)
    {
        rta=1;
    }
    return rta;
}

nodoListaBase*borrarNodoBase(nodoListaBase*lista,int habitacion)
{
    nodoListaBase*aBorrar;
    if(lista->dato.habitacion==habitacion)
    {
        aBorrar=lista;
        lista=lista->siguiente;
    }
    else
    {
        nodoListaBase*seguidora=lista->siguiente;
        nodoListaBase*anterior=lista;
        while((seguidora!=NULL)&&(seguidora->dato.habitacion!=habitacion))
        {
            anterior=seguidora;
            seguidora=seguidora->siguiente;
        }
        if(seguidora!=NULL)
        {
            anterior->siguiente=seguidora->siguiente;
            aBorrar=seguidora;
        }
    }
    free(aBorrar);
    return lista;
}
nodoListaBase*borramosListaHab(nodoListaBase*lista,int habitacion)
{
    int rta=buscarNodoHabitacion(lista,habitacion);
    while(rta==1)
    {
        lista=borrarNodoBase(lista,habitacion);
        rta=buscarNodoHabitacion(lista,habitacion);
    }
    return lista;
}
void borrarDeHospedados(int habitacion)///borra del archivo de hospedadosActuales
{
    nodoListaBase*seguidora;
    FILE*fp;
    nodoListaBase*lista=inicListaBase();
    baseClientes clienteArchivo;
    fp=fopen(clientesActuales,"rb");
    if(fp!=NULL)
    {
        while(fread(&clienteArchivo,sizeof(baseClientes),1,fp)>0)
        {
            lista=agregarPrincipioBase(lista,clienteArchivo);
        }

        lista=borramosListaHab(lista,habitacion);

        fclose(fp);

    }
    FILE*eq;
    eq=fopen(clientesActuales,"wb");
    if(eq!=NULL)
    {
        while(lista!=NULL)
        {
            clienteArchivo=lista->dato;
            fwrite(&clienteArchivo,sizeof(baseClientes),1,eq);
            lista=lista->siguiente;
        }
        fclose(eq);
    }

}
