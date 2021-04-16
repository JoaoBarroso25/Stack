/**
 *  @file Main - Ficheiro que contém a Função Principal do Programa e a Função Parse.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"
#include "parser.h"

/**
 * \brief Função ReadNewLine
 *
 * Função ReadNewLine
 *
 * @param  --> Recebe o endereço de memória da linha.
 *
 * @return --> O comprimento da String "aux" menos dois.
 */
int ReadNewLine(char* line)
{
    char aux[10240];

    assert(fgets(aux, 10240, stdin) != NULL);
    assert(aux[strlen(aux) - 1] == '\n');

    strncat(line, aux, strlen(aux)-1);

    return(strlen(aux) - 2);
}

/**
 * \brief Função Main
 *
 * Função Principal do Programa
 *
 * @return --> Retorna 0.
 */
int main() {
    char line[10240], aux[10240];
    STACK* s;
    int i,count;

    s = create_stack();
    assert(fgets(aux, 10240, stdin) != NULL);
    assert( aux[strlen(aux) - 1] == '\n');

    line[0] = '\0';
    i = 0;
    count = 0;
    while (aux[i] != '\n'){
        if (aux[i] != 'l') {
            line[count] = aux[i];
        }
        else count += ReadNewLine(line);
        i++;
        count++;
        line[count] = '\0';
    }

    parser(line, s);

    return 0;
}
