#ifndef AUTOMATA_H_INCLUDED
#define AUTOMATA_H_INCLUDED
/*creacion de los estados de transición del autómata el cual se va a llamar Estado y tambien
se crea la opcion validarJson para poder validar el JSON creado*/
typedef enum {
    Q0_INICIO,
    Q1_CORCHETE_INICIO,
    Q2_EMPLOYEES,
    Q3_DOSPUNTOS,
    Q4_LLAVE,
    Q5_OBJETO,
    Q6_FIRSTNAME,
    Q7_VALOR1,
    Q8_COMA,
    Q9_LASTNAME,
    Q10_DOSPUNTOS,
    Q11_VALOR2,
    Q12_FINOBJETO,
    Q13_CONTINUAR,
    Q14_FIN

} Estado;

int validarJSON(const char *input);


#endif // AUTOMATA_H_INCLUDED
