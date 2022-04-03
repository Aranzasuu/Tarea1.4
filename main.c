#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "defFunciones.h"

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

    Biblioteca *biblioteca = crearBiblioteca();
    ImprimirMenu(biblioteca, archivo);

    return 0;
}