/**
 *  @file Eval - Receber a linha e a stack inicial, se não existe stack inicial => cria, enquanto houver linha, pega no token, tratar números, trata arrays, tratar strings, tratar operações, linha passa a ser o resto, devolve stack atual.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "stack.h"
#include "eval.h"
#include "parser.h"

/**
 * \brief Função Get_Delimited
 *
 * Função Get_Delimited
 *
 * @param rest --> Serve para devolver o resto da linha
 * @param line --> A linha que recebe
 *
 * @return newline
 */
char* get_delimited(char* line, char** rest)
{
    char* newline;

    if ((newline = (char*)malloc(strlen(line) * sizeof(char))) == NULL) return NULL;
    if ((*rest = (char*)malloc(strlen(line) * sizeof(char))) == NULL) return NULL;

    if (*line == '[') {
        memcpy(newline, line + 2, strlen(line) - 4);
        *(newline + strlen(line) - 4) = '\0';
    }
    if (*line == '\"') {
        memcpy(newline, line + 1, strlen(line) - 2);
        *(newline + strlen(line) - 2) = '\0';
    }

    return newline;
}

/**
 * \brief Função Eval
 *
 * Função Eval
 *
 * @param init_st --> Stack Inicial.
 * @param line --> A linha que recebe.
 *
 * @return init_st
 */
STACK* eval(char* line, STACK* init_st)
{


    DATA elem, elem1;
    char* sobra_l, * sobra_d;
    elem.type = LONG;
    char *rest=NULL, *token=NULL;
    STACK* st;
    int* AZ =  CreateAZ();

    //   if (init_st == NULL) init_st = create_stack();
    st = create_stack();

    if (*line == '\"') elem1.type = STRING;
    if (*line == '[') elem1.type = ARRAY;
    line = get_delimited(line, &rest);
    if (elem1.type == STRING) {
        elem1.STRING = line;
        push(init_st, elem1);
        return init_st;
    }

    while ((token = get_token(line, &rest)) != NULL) {
        elem.LONG = strtol(token, &sobra_l, 10);
        elem.DOUBLE = strtod(token, &sobra_d);
        if (strlen(sobra_l) == 0) {
            elem.type = LONG;
            push(st, elem);
        }
        else {
            if (strlen(sobra_d) == 0) {
                elem.type = DOUBLE;
                push(st, elem);
            }
            else {
                if ((*token == '[') || (*token == '\"')) st = eval(token, st);
                else Oprations(st, token, AZ);
            }
        }
        free(line);
        line = rest;
    }

    if (elem1.type == ARRAY) {
        elem1.ARRAY = st;
        push(init_st, elem1);
    }
    
    return init_st;
}

