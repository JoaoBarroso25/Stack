/**
 *  @file Parser - Ficheiro que contém a Função Parser e a Função Operations.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "stack.h"
#include "parser.h"

/**
 * \brief Função Parse
 *
 * Função Parse --> Onde se verifica o que é implementado no terminal, por exemplo, se é caractere, número ou token, neste último, vai ser necessária a execução de outra função, Operations.
 *
 * @param line  --> A linha que foi lida e da qual se vai fazer o parse.
 * @param s     --> Corresponde à stack.
 */
void parser(char* line, STACK* s) {
        char delims[] = " \t\n";
        DATA elem;
        char* sobra_l, *sobra_d;
        elem.type = LONG;

        for (char* token = strtok(line, delims); token != NULL; token = strtok(NULL, delims)) {
            //   long val_i = strtol(token, &sobra, 10);
            elem.LONG = strtol(token, &sobra_l, 10);
            elem.DOUBLE = strtod(token, &sobra_d);
            if (strlen(sobra_l) == 0) {
                elem.type = LONG;
                push(s, elem);
            }
            else {
                if (strlen(sobra_d) == 0) {
                    elem.type = DOUBLE;
                    push(s, elem);
                }
                else {
                    Oprations(s, token);
                }
            }
        }
        print_stack(s);
    }

    /**
     * \brief Função Operations
     *
     * Função Operations --> Onde estão localizadas todas as implementações, desde Expressões Matemáticas, à manipulação da Stack, entre outros.
     *
     * @param s     --> Corresponde à stack.
     * @param token --> Recebe um caractere ao qual se vai fazer a comparação de modo a ser executada a operação desejada.
     */

    void Oprations(STACK *s, char *token)
    {
        DATA Y, X, Z, XY, * P;
        XY.type = LONG;
        XY.LONG = 0;
        XY.DOUBLE = 0;

        if (strcmp(token, "+") == 0) {
            Y = pop(s);
            X = pop(s);
            if (X.type == LONG && Y.type == LONG) XY.type = LONG;
            else XY.type = DOUBLE;
            XY.LONG = X.LONG + Y.LONG;
            XY.DOUBLE = X.DOUBLE + Y.DOUBLE;
            push(s, XY);
        }
        if (strcmp(token, "*") == 0) {
            Y = pop(s);
            X = pop(s);
            if (X.type == LONG && Y.type == LONG) XY.type = LONG;
            else XY.type = DOUBLE;
            XY.LONG = X.LONG * Y.LONG;
            XY.DOUBLE = X.DOUBLE * Y.DOUBLE;
            push(s, XY);
        }
        if (strcmp(token, "-") == 0) {
            Y = pop(s);
            X = pop(s);
            if (X.type == LONG && Y.type == LONG) XY.type = LONG;
            else XY.type = DOUBLE;
            XY.LONG = X.LONG - Y.LONG;
            XY.DOUBLE = X.DOUBLE - Y.DOUBLE;
            push(s, XY);
        }
        if (strcmp(token, "/") == 0) {
            Y = pop(s);
            X = pop(s);
            if(X.type==LONG && Y.type==LONG) XY.type = LONG;
            else XY.type = DOUBLE;
            XY.LONG = (int)(X.LONG / Y.LONG);
            XY.DOUBLE = X.DOUBLE / Y.DOUBLE;
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
            XY.LONG = (long)pow(X.LONG, Y.LONG);
            XY.DOUBLE = pow(X.DOUBLE, Y.DOUBLE);
            XY.type = DOUBLE;
            push(s, XY);
        }
        if (strcmp(token, ")") == 0) {
            X = pop(s);
            X.LONG = X.LONG + 1;
            X.DOUBLE = X.DOUBLE + 1;
            X.CHAR = X.CHAR + 1;
            push(s, X);
        }
        if (strcmp(token, "(") == 0) {
            X = pop(s);
            X.LONG = X.LONG - 1;
            X.DOUBLE = X.DOUBLE - 1;
            X.CHAR = X.CHAR - 1;
            push(s, X);
        }
        if (strcmp(token, "~") == 0) {
            X = pop(s);
            XY.LONG = ~(X.LONG);
            push(s, XY);
        }
        if (strcmp(token, "_") == 0) {
            X = top(s);
            push(s, X);
    //        push(s, X);
        }
        if (strcmp(token, ";") == 0) {
            X = pop(s);
        }
        if (strcmp(token, "\\") == 0) {
            X = pop(s);
            Y = pop(s);
            push(s, X);
            push(s, Y);
        }
        if (strcmp(token, "@") == 0) {
            X = pop(s);
            Y = pop(s);
            Z = pop(s);
            push(s, Y);
            push(s, X);
            push(s, Z);
        }
        if (strcmp(token, "$") == 0) {
            X = pop(s);
            assert((P = Find_Elem(s, X.LONG)) != NULL);
            push(s, *P);
        }
        if (strcmp(token, "c") == 0) {
            X = pop(s);
            X.CHAR = (char)X.LONG;
            X.type = CHAR;
            push(s, X);
        }
        if (strcmp(token, "i") == 0) {
            X = pop(s);
            X.type = LONG;
            push(s, X);
        }
        if (strcmp(token, "f") == 0) {
            X = pop(s);
            X.type = DOUBLE;
            push(s, X);
        }
    }