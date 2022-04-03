#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "defFunciones.h"

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char *ret = (char *) malloc (150 * sizeof(char));
    int ini_i = 0, i = 0, j = 0;
    while(tmp[i+1] != '\0'){

        if(tmp[i] == '\"'){
            open_mark = 1 - open_mark;
            if(open_mark) ini_i = i + 1;
            i++;
            continue;
        }

        if(open_mark || tmp[i] != ','){
            if(k == j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i] == ','){
            if(k == j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i + 1;
        }
        i++;
    }

    if(k == j){

        i = i - 1;
        for (i; tmp[i] != '\0'; i++)
        {
            ret[i - ini_i] =  tmp[i];
        }
       ret[i - ini_i] = 0;
       return ret;
    }
    return NULL;
}

Biblioteca* crearBiblioteca()
{
    Biblioteca* biblioteca = (Biblioteca*)malloc(sizeof(Biblioteca));
    biblioteca->cantidadListas = 0;
    biblioteca->ListaCanciones = createList();
    biblioteca->ListaGeneral = createList();
    return biblioteca;
}

void imprimirCancion(Cancion* a){
    printf("------------------------------------------------\n");

    printf("Nombre : %s \n", a->Nombre);
    printf("Artista : %s \n", a->Artista);
    printf("Genero : %s \n", a->Genero);
    printf("Anyo : %s \n", a->year);
    printf("Lista : %s \n", a->NombreLista);

    return;
}

void ImprimirMenu(Biblioteca *biblioteca, FILE *archivo)
{
    int op, op2;
    printf("Ingresar 0 para comenzar\n");
    scanf("%d", &op);


    while(op != 8)
    {
        printf("\nopcion 0. Importar\n");
        printf("opcion 1. Agregar Cancion\n");
        printf("opcion 2. Buscar Cancion\n");
        printf("opcion 3. Eliminar Cancion\n");
        printf("opcion 4. Mostrar Nombres Listas\n");
        printf("opcion 5. Mostrar Lista\n");
        printf("opcion 6. Mostrar todas las Canciones\n");
        printf("opcion 7. Exportar\n");
        printf("opcion 8. Salir\n");
        scanf("%d", &op);

        while(op < 0 || op > 8)
        {
            printf("ingrese una opcion valido\n");
            scanf("%d", &op);
        }
        
        switch(op)
        {
            case 0:
                importar(archivo, biblioteca);
                break;
            case 1:
                printf("Función en proceso\n");
                break; 
            case 2:
                printf("opcion 1. Nombre\n");
                printf("opcion 2. Artista\n");
                printf("opcion 3. Genero\n");
                scanf("%d", &op2);
                switch(op2)
                {
                    case 1:
                        /*printf("Ingrese el nombre: ");
                        char cancionBuscada[35];
                        scanf("%s",cancionBuscada);
                        printf("cancion b = %s",cancionBuscada);
                        //cancionBuscada = "Hey ya!";*/ 
                        BuscarPorNombre(biblioteca -> ListaCanciones);
                        break;
                    case 2:
                        Buscar_artista(biblioteca -> ListaCanciones);
                        break;
                    case 3:
                        printf("Ingrese el genero: ");
                        break;
                }
                break;
            case 3:
                eliminarCancion(biblioteca);
                break;
            case 4:
                printf("Funcion en proceso\n");
                break;
            case 5:
                mostrarReproduccion(biblioteca, "Lista1");
                break;
            case 6:
                printf("Funcion en proceso\n");
                break;
            case 7:
                printf("Funcion en proceso\n");
                break;
            case 8:
                break;
            printf("\n\n");
        }
    }
    printf("\n\n");
}

void importar(FILE *archivo, Biblioteca* biblioteca)
{
    int i;
    //int k = 0;
    char linea[1024];

    while (fgets(linea, 1024, archivo) != NULL)
    {
        linea[strcspn(linea, "\n")] = 0;
        Cancion* cancion = (Cancion *) malloc(sizeof(Cancion));
        cancion->Artista = (char*) malloc(sizeof(char) * 35);
        cancion->Genero = (char*) malloc(sizeof(char) * 35);
        cancion->Nombre = (char*) malloc(sizeof(char) * 35);
        cancion->year = (char*) malloc(sizeof(char) * 4);
        cancion->NombreLista = (char*) malloc(sizeof(char) * 35);

        for (int i = 0; i < 5; i++)
        {
            const char* aux = get_csv_field(linea, i);

            switch (i)
            {
                case 0:
                    strcpy(cancion->Nombre, aux);
                    break;
                case 1:
                    strcpy(cancion->Artista, aux); 
                    break;
                case 2:
                    strcpy(cancion->Genero, aux);
                    break;
                case 3:
                    strcpy(cancion->year, aux);
                    break;
                case 4:
                    strcpy(cancion->NombreLista, aux);
                    break;
            }
        }

        pushBack(biblioteca->ListaCanciones, cancion); // pushBack

        Reproduccion* reproAux = existeReproduccion(biblioteca, cancion->NombreLista);
        if (reproAux != NULL)
        {
            //printf("Existe: %s", reproAux->NombreList);
            
            reproAux->cantidadCanciones += 1;
            pushFront(reproAux->ListaReprod, cancion);
        }
        else
        {
            Reproduccion* repro = (Reproduccion *) malloc (sizeof(Reproduccion));
            repro->cantidadCanciones = 1;
            repro->ListaReprod = createList();
            repro->NombreList = (char*)malloc(sizeof(char) * 35);
            strcpy(repro->NombreList, cancion->NombreLista);
            pushFront(repro->ListaReprod, cancion);

            pushFront(biblioteca->ListaGeneral, repro);
        }

        //listaGlobal->cantidadCanciones += 1;
        //if (k < 5) imprimirCancion(cancion);
        //k++;
    }
    
    fclose(archivo);
    printf("Archivo importado!\n\n");
    //return listGeneral;
}

Reproduccion* existeReproduccion(Biblioteca* biblioteca, char* nombreList)
{
    Reproduccion* repro = firstList(biblioteca->ListaGeneral);
    while (repro != NULL)
    {
        if (strcmp(repro->NombreList, nombreList) == 0)
        {
            //printf("* %s\n", repro->NombreList);
            break;
        }

        repro = nextList(biblioteca->ListaGeneral);
    }

    return repro;
}

void mostrarReproduccion(Biblioteca* biblioteca, char* nombreLista)
{
    Reproduccion* repro = existeReproduccion(biblioteca, nombreLista);

    if (repro == NULL)
        printf("NULL\n");

    if (repro != NULL)
    {
        printf("--- %s ---\n", nombreLista);

        Cancion* cancion = (Cancion*)firstList(repro->ListaReprod);
        while (cancion != NULL)
        {
            imprimirCancion(cancion);

            //if (strcmp(cancion->Artista, nombreABuscar) == 0)
            //    return cancion;

            cancion = (Cancion*)nextList(repro->ListaReprod);
        }

        //mostrarCanciones(repro->ListaReprod);
    }
}

void mostrarCanciones(List* listaCanciones)
{
    //char* nombreABuscar;

    Cancion* cancion = (Cancion*)firstList(listaCanciones);
    while (cancion != NULL)
    {
        imprimirCancion(cancion);

        //if (strcmp(cancion->Artista, nombreABuscar) == 0)
        //    return cancion;

        cancion = (Cancion*)nextList(listaCanciones);
    }

    //return NULL;
}

/*void obtenerGeneros(List * genero, const char *dato){
    printf("Aun no se crea esta funcion");
}


void LlenarLista(Biblioteca *listGeneral, char *linea)

{
    // for(int i = 0; i < 5; i++)
    // {
    //     const char *atributo = get_csv_field(linea, i);
    //     if(i == 0)
    //         strcpy(listGeneral -> cancion -> Nombre, atributo);
    //     else if (i == 1)
    //         strcpy(listGeneral -> cancion -> Artista, atributo);
    //     else if (i == 2)
    //         guardarGenero(listGeneral, atributo);
    //     else if(i == 3)
    //         listGeneral -> cancion -> year = atributo;
    //     else
    //         guardarLista(listGeneral,atributo);
    // }
}



void guardarLista(Biblioteca *lista, const char *atr)
{
    printf("Aun no se crea esta funcion");
}
*/

void BuscarPorNombre(List *ListaCanciones){
    char cancionBuscada[35];
    printf("Ingrese el nombre de la cancion: ");
    scanf("%[^\n]s",cancionBuscada);
    printf("cancion buscada: %s\n",cancionBuscada);
    //cancionBuscada = "Numb";
    //cancionBuscada[strcspn(cancionBuscada, "\n")] = 0;
    Cancion *canciones = (Cancion *) firstList(ListaCanciones);
    int flag = 0;
    
    while(canciones != NULL){    
        if(strcmp(canciones -> Nombre, cancionBuscada) == 0)
        {
            printf("\nNombre: %s\n", canciones -> Nombre);
            printf("Artista: %s\n", canciones -> Artista);
            printf("Genero: %s\n", canciones -> Genero);
            printf("Año: %s\n", canciones -> year);
            printf("Lista de: %s\n", canciones -> NombreLista);
            flag = 1;            
            break;
        }
        canciones = nextList(ListaCanciones);
    }
    if (flag == 0)
        printf("La cancion buscada no se encuentra");
    printf("\n");
}

void eliminarCancion(Biblioteca *biblioteca){
    char *cancionEliminada;
    //scanf("%[^\n]s", cancionEliminada);
    //printf("%s",cancionEliminada);
    cancionEliminada = "Welcome to the jungle";
    Cancion *eliminar = firstList(biblioteca -> ListaCanciones);
    int flag = 0;
    while(eliminar != NULL){
        if(strcmp(eliminar -> Nombre, cancionEliminada) == 0){
            popCurrent(biblioteca -> ListaCanciones);
            flag = 1;
            break;
        }
        eliminar = nextList(biblioteca -> ListaCanciones);
    }
    if (flag == 0){
        printf("No esta la cancion que desea eliminar\n");
    }
}

void Buscar_artista(List *ListaCanciones){
    char *art_buscado = (char *) malloc (35 * sizeof(char)); 
    int k = 0;
    scanf("%s", art_buscado);

    Cancion *canciones = firstList(ListaCanciones);

    while(canciones != NULL ){
        if (strcmp(canciones -> Artista, art_buscado) == 0){
            imprimirCancion(canciones);
            k = 1;
        }
        canciones = nextList(ListaCanciones);
    }

    if (k == 0) printf("No se encontro ninguna cancion de %s.\n" , art_buscado);
}
