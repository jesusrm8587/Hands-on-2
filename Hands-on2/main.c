#include <stdio.h>
#include <string.h>
#include "automata.h"

#define MAX_LEN 1024  // longitud máxima del JSON que se puede ingresar

int main() {
    char input[MAX_LEN];

    printf("Ingresa JSONs para validar. Escribe 'salir' para terminar.\n");

    while (1) {
        printf("\nIngresa JSON: ");
        if (!fgets(input, MAX_LEN, stdin)) break; // fin de entrada
        input[strcspn(input, "\n")] = 0; // quitar el salto de línea al final

        if (strcmp(input, "salir") == 0) break;

        if (validarJSON(input)) {
            printf("JSON valido\n");
        } else {
            printf("JSON invalido\n");
        }
    }

    printf("Programa terminado.\n");
    return 0;
}
