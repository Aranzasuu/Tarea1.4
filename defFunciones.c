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

void ImprimirMenu(int op, int op2)
{
    printf("opcion 1. Agregar Cancion\n");
    printf("opcion 2. Buscar Cancion\n");
    printf("opcion 3. Eliminar Cancion\n");
    printf("opcion 4. Mostrar Nombres Listas\n");
    printf("opcion 5. Mostrar Lista\n");
    printf("opcion 6. Mostrar todas las Canciones\n");
    scanf("%d", &op);

    switch(op)
    {
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
                    printf("Ingrese el nombre: ");
                    // BuscarPorNombre(General);
                    break;
                case 2:
                    printf("Ingrese el artista: ");
                    break;
                case 3:
                    printf("Ingrese el genero: ");
                    break;
            }
            break;
        case 3:
            printf("Función en proceso\n");
            break;
        case 4:
            printf("Función en proceso\n");
            break;
        case 5:
            printf("Función en proceso\n");
            break;
        case 6:
            printf("Función en proceso\n");
            break;
        break;
    }
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

        pushFront(biblioteca->ListaCanciones, cancion); // pushBack

        Reproduccion* reproAux = existeReproduccion(biblioteca, cancion->NombreLista);
        if (reproAux != NULL)
        {
            printf("Existe: %s", reproAux->NombreList);
            
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
    printf("Archivo importado!\n");
    //return listGeneral;
}

Reproduccion* existeReproduccion(Biblioteca* biblioteca, char* nombreList)
{
    Reproduccion* repro = firstList(biblioteca->ListaGeneral);
    while (repro != NULL)
    {
        if (strcmp(repro->NombreList, nombreList) == 0)
        {
            printf("* %s\n", repro->NombreList);
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

// const char *get_csv_field (char * tmp, int k) {
//     int open_mark = 0;
//     char *ret = (char *) malloc (150 * sizeof(char));
//     int ini_i = 0, i = 0, j = 0;
//     while(tmp[i+1] != '\0'){

//         if(tmp[i] == '\"'){
//             open_mark = 1 - open_mark;
//             if(open_mark) ini_i = i + 1;
//             i++;
//             continue;
//         }

//         if(open_mark || tmp[i] != ','){
//             if(k == j) ret[i-ini_i] = tmp[i];
//             i++;
//             continue;
//         }

//         if(tmp[i] == ','){
//             if(k == j) {
//                ret[i-ini_i] = 0;
//                return ret;
//             }
//             j++; ini_i = i + 1;
//         }
//         i++;
//     }

//     if(k == j){

//         i = i - 1;
//         for (i; tmp[i] != '\0'; i++)
//         {
//             ret[i - ini_i] =  tmp[i];
//         }
//        ret[i - ini_i] = 0;
//        return ret;
//     }
//     return NULL;
// }

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

/*
void BuscarPorNombre(Biblioteca *lista, List* canciones){
    char *cancionBuscada;
    scanf("%s", cancionBuscada);
    Canciones *cancion = firstList(canciones);
    int flag = 0;
    
    while(cancion != NULL){        
        if(strcmp(cancion -> Nombre, cancionBuscada)==0){
            printf("Nombre: %s", cancion -> Nombre);
            printf("Artista: %s", cancion -> Artista);
            printf("Genero: %s", cancion -> Genero);
            printf("Año: %s", cancion -> year);
            printf("Lista de: %s", cancion -> Lista);
            flag = 1;            
            break;
        }
        cancion = nextList(canciones);
    }
    if (flag == 0)
        printf("La cancion buscada no se encuentra");
}
*/ 