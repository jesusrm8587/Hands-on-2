#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "automata.h"


// Función auxiliar: verifica si es una cadena alfanumérica que empieza con letra

int CadenaValida(const char *str) {
    if (!isalpha(str[0])) return 0;   // debe empezar con letra
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i])) return 0; // el resto debe ser alfanumérico
    }
    return 1;
}


// Función auxiliar: lee un string entre comillas "valor"
// retorna puntero al carácter después de la comilla de cierre

const char* leerString(const char *ptr, char *buffer) {
    if (*ptr != '\"') return NULL;
    ptr++;
    int i = 0;
    while (*ptr != '\"' && *ptr != '\0') {
        buffer[i++] = *ptr;
        ptr++;
    }
    if (*ptr != '\"') return NULL; // no cerró comilla
    buffer[i] = '\0';
    return ptr + 1;
}

//Funcionamiento del autómata
int validarJSON(const char *input) {
    Estado estado = Q0_INICIO;
    const char *ptr = input;
    char buffer[128];

    while (*ptr != '\0') {
        switch (estado) {

            case Q0_INICIO:
                if (*ptr == '{') {
                    estado = Q1_CORCHETE_INICIO;
                    ptr++;
                } else return 0;
                break;

            case Q1_CORCHETE_INICIO:
                if (strncmp(ptr, "\"employees\"", 11) == 0) {
                    ptr += 11;
                    estado = Q2_EMPLOYEES;
                } else return 0;
                break;

            case Q2_EMPLOYEES:
                if (*ptr == ':') {
                    estado = Q3_DOSPUNTOS;
                    ptr++;
                } else return 0;
                break;

            case Q3_DOSPUNTOS:
                if (*ptr == '[') {
                    estado = Q4_LLAVE;
                    ptr++;
                } else return 0;
                break;

            case Q4_LLAVE:
                if (*ptr == '{') {
                    estado = Q5_OBJETO;
                    ptr++;
                } else if (*ptr == ']') { //El arreglo está vacío
                    estado = Q14_FIN;
                    ptr++;
                } else return 0;
                break;

            case Q5_OBJETO:
                if (strncmp(ptr, "\"firstName\"", 11) == 0) {
                    ptr += 11;
                    estado = Q6_FIRSTNAME;
                } else return 0;
                break;

            case Q6_FIRSTNAME:
                if (*ptr == ':') {
                    estado = Q7_VALOR1;
                    ptr++;
                } else return 0;
                break;

            case Q7_VALOR1:
                if (*ptr == '\"') {
                    ptr = leerString(ptr, buffer);
                    if (!ptr || !CadenaValida(buffer)) return 0;
                    estado = Q8_COMA;
                } else return 0;
                break;

            case Q8_COMA:
                if (*ptr == ',') {
                    ptr++;
                    estado = Q9_LASTNAME;
                } else return 0;
                break;

            case Q9_LASTNAME:
                if (strncmp(ptr, "\"lastName\"", 10) == 0) {
                    ptr += 10;
                    estado = Q10_DOSPUNTOS;
                } else return 0;
                break;

            case Q10_DOSPUNTOS:
                if (*ptr == ':') {
                    ptr++;
                    estado = Q11_VALOR2;
                } else return 0;
                break;

            case Q11_VALOR2:
                if (*ptr == '\"') {
                    ptr = leerString(ptr, buffer);
                    if (!ptr || !CadenaValida(buffer)) return 0;
                    estado = Q12_FINOBJETO;
                } else return 0;
                break;

            case Q12_FINOBJETO:
                if (*ptr == '}') {
                    ptr++;
                    estado = Q13_CONTINUAR;
                } else return 0;
                break;

            case Q13_CONTINUAR:
                if (*ptr == ',') {
                    ptr++;
                    if (*ptr == '{') {
                        ptr++;
                        estado = Q5_OBJETO; //se indica la opción de seguir creando más objetos
                    } else return 0;
                } else if (*ptr == ']') {
                    ptr++;
                    estado = Q14_FIN;
                } else return 0;
                break;

            case Q14_FIN:
                if (*ptr == '}') {
                    return 1; //El JSON es válido
                } else return 0;
                break;

            default:
                return 0;
        }
    }

    return 0;
}
