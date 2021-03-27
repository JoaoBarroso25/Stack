/**
 *  @file Main - Ficheiro que contém a Função Principal do Programa e a Função Parse.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

/**
 * \brief Função Parse
 *
 * Função Parse --> Onde estão localizadas todas as Expressões Matemáticas.
 *
 * x
 *
 * @param line  --> A linha que foi lida e da qual se vai fazer o parse.
 * @param s     --> Corresponde à stack.
 */

void parse(char* line, STACK* s) {
    char delims[] = " \t\n";
    DATA elem, Y, X, XY;
    char* sobra;
    XY.type = LONG;
    for (char* token = strtok(line, delims); token != NULL; token = strtok(NULL, delims)) {
        //   long val_i = strtol(token, &sobra, 10);
        elem.LONG = strtol(token, &sobra, 10);
        if (strlen(sobra) == 0) {
            push(s, elem);
        }
        else{
            if (strcmp(token, "+") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG + Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "*") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG * Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "-") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG - Y.LONG;
                push(s, XY);
            }

            if (strcmp(token, "/") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG / Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "%") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG % Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "&") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG & Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "^") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG ^ Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "|") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = X.LONG | Y.LONG;
                push(s, XY);
            }
            if (strcmp(token, "#") == 0) {
                Y = pop(s);
                X = pop(s);
                XY.LONG = pow (X.LONG , Y.LONG);
                push(s, XY);
            }
            if (strcmp(token, ")") == 0) {
                X = pop(s);
                XY.LONG = X.LONG + 1;
                push(s, XY);
            }
            if (strcmp(token, "(") == 0) {
                X = pop(s);
                XY.LONG = X.LONG - 1;
                push(s, XY);
            }
            if (strcmp(token, "~") == 0) {
                X = pop(s);
                XY.LONG = ~(X.LONG);
                push(s, XY);
            }
        }
        if (isdigit(line[strlen(line) - 1])) {
            X = pop(s);
            XY.LONG = X.LONG;
            push(s, XY);
        }
    }
    print_stack(s);
}

/**
 * \brief Função Main
 *
 * Função Principal do Programa
 *      . Devolve NULL senão conseguir ler a linha.
 *      . Verifica se o último caractere da linha é o '\n'.
 *      . Invocamos a função Parse que recebe uma linha uma stack s.
 *
 * @return --> Retorna 0.
 */

int main() {
    char line[10240];
    STACK* s;

    s = create_stack();

    assert(fgets(line, 10240, stdin) != NULL);
    assert( line[strlen(line) - 1] == '\n');

    parse(line, s);
    return 0;

}

























