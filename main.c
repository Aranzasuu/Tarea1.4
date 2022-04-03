#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "defFunciones.h"

//typedef struct Node Node;
//typedef List List;

int main()
{   
    char *NombreArchivo;
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", NombreArchivo);
    FILE *archivo = fopen(NombreArchivo,"r");

    while(archivo == NULL)
    {
        printf("No se pudo abrir el archivo, ingrese un nombre valido\n");
        printf("Ingrese el nombre del archivo: ");
        scanf("%s", NombreArchivo);
        FILE *archivo = fopen(NombreArchivo,"r");
        if (archivo != NULL) break;
        //return(EXIT_FAILURE);
    }

    Biblioteca *biblioteca = crearBiblioteca();   // no recibe parámetros, porque retorna una lista, con la información ya dimensionada.
    // Reproduccion *lista_global = (Reproduccion *) malloc (sizeof(Reproduccion));
    // lista_global ->cantidadCanciones = 0;
    // lista_global -> ListaReprod = createList();
    // strcpy(lista_global -> NombreList , "Lista Global");

    //int a = 1;

    ImprimirMenu(biblioteca, archivo);
    
    /*while (a == 1)
    {
        importar(archivo, biblioteca);
        a = 0;
        //mostrarCanciones(biblioteca->ListaCanciones);
        //mostrarReproduccion(biblioteca, "Lista 1");
        //BuscarPorNombre(biblioteca -> ListaCanciones);

    }*/

    return 0;
}