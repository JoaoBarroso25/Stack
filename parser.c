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
 * \brief Função CreateAZ
 *
 * Função CreateAZ--> Função que cria um array onde ficam armazenados valores que podem ser alterados ao longo do código. 
 *
*/
int* CreateAZ()
{
    int* aux,i;
    if ((aux = (int*)calloc(26,sizeof(int))) == NULL)
        return NULL;

    for (i = 0; i < 6; i++)
        aux[i] = 10 + i;
    // A -> F
    aux[6] = 0; // G
    aux[7] = 0; // H
    aux[8] = 0; // I
    aux[9] = 0; // J
    aux[10] = 0; // K
    aux[11] = 0; // L
    aux[12] = 0; // M
    // N
    aux[14] = 0; // O
    aux[15] = 0; // P
    aux[16] = 0; // Q
    aux[17] = 0; // R
    // S
    aux[19] = 0; // T
    aux[20] = 0; // U
    aux[21] = 0; // V
    aux[22] = 0; // W
    aux[23] = 0; // X
    aux[24] = 1; // Y
    aux[25] = 2; // Z

    return aux;
}

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
    int *AZ;

    AZ = CreateAZ();

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
                Oprations(s, token, AZ);
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
void Oprations(STACK* s, char* token, int* AZ)
{
    DATA Y, X, Z, XY, * P;
    XY.LONG = 0;
    XY.DOUBLE = 0;

    if (strcmp(token, "+") == 0) op_plus(s);

    if (strcmp(token, "*") == 0) op_star(s);
    
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
        if (X.type == LONG && Y.type == LONG) XY.type = LONG;
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
    if (strcmp(token, "#") == 0) op_sharp(s);

    if (strcmp(token, ")") == 0) op_remove_last(s);

    if (strcmp(token, "(") == 0) op_remove_first(s);

    if (strcmp(token, "~") == 0) op_explosion(s);

    if (strcmp(token, "_") == 0) {
        X = top(s);
        push(s, X);
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
    if (strcmp(token, "=") == 0) op_equal(s);

    if (strcmp(token, ">") == 0) op_higher(s);

    if (strcmp(token, "<") == 0) op_lower(s);

    if (strcmp(token, "e>") == 0) {
        Y = pop(s);
        X = pop(s);
        if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        if (X.DOUBLE > Y.DOUBLE) {
        X.type = DOUBLE;
        push(s, X);
        }
        else push(s, Y);
            }
        if  ((X.type == STRING) && (Y.type == STRING)) {
            if ( strlen (X.STRING) >= strlen (Y.STRING)) {
                X.type = STRING;
                push (s, X);
            }
            else {
                Y.type = STRING;
                push (s, Y);
            }
        }
    }
    if (strcmp(token, "e<") == 0) {
        Y = pop(s);
        X = pop(s);
        if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        if (X.DOUBLE < Y.DOUBLE) {
            push(s, X);
            X.type = DOUBLE;
        }
        else push(s, Y);
            }
        if  ((X.type == STRING) && (Y.type == STRING)) {
                if ( strlen (X.STRING) < strlen (Y.STRING)) {
                    X.type = STRING;
                    push (s, X);
                }
                else {
                    Y.type = STRING;
                    push (s, Y);
                    }
                }
    }
    if (strcmp(token, "!") == 0) {
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE != 0) {
            X.DOUBLE = 0;
            X.LONG = 0;
        }
        else {
            X.DOUBLE = 1;
            X.LONG = 1;
        }
        push(s, X);
    }
    if (strcmp(token, "e&") == 0) {   
        Y = pop(s);
        X = pop(s);
        if (X.type == DOUBLE && Y.type == DOUBLE) {
            if (X.DOUBLE == 0 || Y.DOUBLE == 0) {
                X.DOUBLE = 0;
                push(s, X);
            }
            else {
                if (X.DOUBLE >= Y.DOUBLE) {
                    push(s, X);
                }
                else push(s, Y);
            }
        }
        else {
            if (X.LONG == 0 || Y.LONG == 0) { 
                X.LONG = 0;
                push(s, X);
            }
            else {
                if (X.LONG >= Y.LONG) {
                    push(s, X);
                }
                else push(s, Y);
            }
        }
    }
    if (strcmp(token, "e|") == 0) {   
        X = pop(s);
        Y = pop(s);
        if (X.type == DOUBLE || Y.type == DOUBLE) {
            if (X.DOUBLE == 0 || Y.DOUBLE == 0) {
                X.DOUBLE = 0;
                push(s, X);
            }
            else {
                if (X.DOUBLE >= Y.DOUBLE) push(s, X);
                else push(s, Y);
            }
        }
        else {
            if (X.DOUBLE == 0 || Y.DOUBLE == 0) {
                X.DOUBLE = 0;
                push(s, X);
            }
            else if (X.LONG >= Y.LONG) push(s, X);
            else push(s, Y);
        }
    }
    if (strcmp(token, "?") == 0) { 
        X = pop(s);
        Y = pop(s);
        Z = pop(s);
        if (Z.LONG == 0 || Z.DOUBLE == 0) {
            push(s, X);
        }
        else push(s, Y);
    }


    if ((strcmp(token, "A") >= 0) && (strcmp(token, "Z") <= 0) && (strcmp(token, "N") != 0) && (strcmp(token, "S") != 0)){
        X.LONG = AZ[(int)(*token)-65];
//        X.DOUBLE = AZ[(int)(*token) - 65];
        X.type = LONG;
        push(s, X);
    }


    if (strcmp(token, "N") == 0) { // VERIFICAR
        X.CHAR = '\n';
        X.type = CHAR;
        push(s, X);
    }
    if (strcmp(token, "S") == 0) { 
        X.CHAR = ' ';
        X.type = CHAR;
        push(s, X);
    }

    if ((strcmp(token, ":A") >= 0) && (strcmp(token, ":Z") <= 0)) {
        X = top(s);
        AZ[(int)(*(token+1)) - 65] = X.LONG;
    }

    if (strcmp(token, ",") == 0) op_comma(s);


}

void op_comma(STACK* s)
{
    DATA Y, X, XY;
    XY.LONG = 0;
    XY.DOUBLE = 0;

    X = pop(s);
    Y.type = LONG;
    if (X.type == LONG){
        XY.ARRAY = create_stack();
        XY.type = ARRAY;
        for (Y.LONG = 0; Y.LONG < X.LONG; Y.LONG++)  push(XY.ARRAY, Y);
        push(s, XY);
    }
    if (X.type == ARRAY) {
        X.LONG = X.ARRAY->n_elems;
        X.type = LONG;
        push(s, X);
    }
    if (X.type == STRING) {
        X.LONG = strlen(X.STRING);
        X.type = LONG;
        push(s, X);
    }
}

void op_plus(STACK* s)
{
    DATA Y, X, XY;
    XY.LONG = 0;
    XY.DOUBLE = 0;

    Y = pop(s);
    X = pop(s);

    if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        if (X.type == LONG && Y.type == LONG) XY.type = LONG;
        else XY.type = DOUBLE;
        XY.LONG = X.LONG + Y.LONG;
        XY.DOUBLE = X.DOUBLE + Y.DOUBLE;
        push(s, XY);
    }

    if ((X.type == ARRAY) && (Y.type == ARRAY)) {
        for (int i = 0; i < Y.ARRAY->n_elems; i++) {
            XY = Y.ARRAY->stack[i];
            push(X.ARRAY, XY);
        }
        free(Y.ARRAY);
        push(s, X);
    }

    if ((X.type == ARRAY) && (Y.type != ARRAY)) {
        push(X.ARRAY, Y);
        push(s, X);
    }

    if ((X.type != ARRAY) && (Y.type == ARRAY)) {
        XY.ARRAY = create_stack();
        XY.type = ARRAY;
        push(XY.ARRAY, X);
        for (int i = 1; i < Y.ARRAY->n_elems; i++)
            push(XY.ARRAY, Y);
        push(s, XY);
        //       free(Y.ARRAY);
    }

    if ((X.type == STRING) && (Y.type == STRING)) {
        strcat(X.STRING, Y.STRING);
        push(s, X);
    }


}

void op_star(STACK *s)
{
    DATA Y, X, XY;
    XY.LONG = 0;
    XY.DOUBLE = 0;
    XY.STRING = NULL;
    int xsize;

    Y = pop(s);
    X = pop(s);
    if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        if (X.type == LONG && Y.type == LONG) XY.type = LONG;
        else XY.type = DOUBLE;
        XY.LONG = X.LONG * Y.LONG;
        XY.DOUBLE = X.DOUBLE * Y.DOUBLE;
        push(s, XY);
    }
    if ( X.type == ARRAY && Y.type == LONG) {
        xsize = X.ARRAY->n_elems;
        for (int j = 1; j < Y.LONG; j++) {
            for (int i = 0; i < xsize; i++) {
                XY = X.ARRAY->stack[i];
                push(X.ARRAY, XY);
            }
        }
        push(s, X);
    }
    if (X.type == STRING && Y.type == LONG) {
        XY.STRING = (char *)malloc(strlen(X.STRING) * sizeof(char));
        strcpy(XY.STRING, X.STRING);
        for (int j = 1; j < Y.LONG; j++) {
            strcat(X.STRING, XY.STRING);
        }
        push(s, X);
    }

}

void op_equal(STACK* s)
{
    DATA Y, X, XY;

    XY.type = LONG;
    Y = pop(s);
    X = pop(s);

    if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        X.type = DOUBLE;
        if (X.DOUBLE == Y.DOUBLE) X.DOUBLE = 1;
        else X.DOUBLE = 0;
        push(s, X);
    }
    if ((X.type == ARRAY) && (Y.type == LONG)) push(s, X.ARRAY->stack[Y.LONG]);
    if ((X.type == STRING) && (Y.type == STRING)) {
        if ( strcmp (X.STRING, Y.STRING) == 0 ) XY.LONG = 1;
        else XY.LONG = 0;
        push (s, XY);
    }

}



void op_higher(STACK* s)
{

    DATA Y, X, Z, XY;
    unsigned int j, i;

    Y = pop(s);
    X = pop(s);

    if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        X.type = DOUBLE;
        if (X.DOUBLE > Y.DOUBLE) X.DOUBLE = 1;
        else X.DOUBLE = 0;
        push(s, X);
    }
    if((X.type == ARRAY) && (Y.type == LONG)) {
        XY.ARRAY = create_stack();
        XY.type = ARRAY;
        for (int i = X.ARRAY->n_elems-Y.LONG; i < X.ARRAY->n_elems; i++) {
            Z = X.ARRAY->stack[i];
            push(XY.ARRAY, Z);
        }
        push(s, XY);
    }
    if ((X.type == STRING) && (Y.type == LONG)) {
        for (j=0, i = strlen(X.STRING) - Y.LONG; i < strlen(X.STRING); i++, j++)
            X.STRING[j] = X.STRING[i];

        X.STRING[j] = '\0';
        push(s, X);
    }
    if ((X.type = STRING)&&(Y.type = STRING)) {
        if ( strlen (X.STRING) > strlen (Y.STRING)) {
            X.type = LONG;
            X.LONG = 0;
            push (s, X);
        }
        else {
            X.type = LONG;
            X.LONG = 1;
            push (s, X);
        }
    }
}

void op_lower(STACK* s)
{
    DATA Y, X, Z, XY;

    Y = pop(s);
    X = pop(s);
    if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        X.type = DOUBLE;
        if (X.DOUBLE < Y.DOUBLE) X.DOUBLE = 1;
        else X.DOUBLE = 0;
        push(s, X);
    }
    if ((X.type == ARRAY) && (Y.type == LONG)) {
        XY.ARRAY = create_stack();
        XY.type = ARRAY;
        for (int i = 0; i < Y.LONG; i++) {
            Z = X.ARRAY->stack[i];
            push(XY.ARRAY, Z);
        }
        push(s, XY);
    }
    if ((X.type == STRING) && (Y.type == LONG)) {
        X.STRING[Y.LONG] = '\0';
        push(s, X);
    }
    if ((X.type == STRING) && (Y.type == STRING)) {
       if ( strlen (X.STRING) < strlen (Y.STRING)) {
           X.type = LONG;
           X.LONG = 1;
           push (s, X);
           }
           else {
           X.type = LONG;
           X.LONG = 0;
           push (s, X);
       }
    }

}
void op_remove_first(STACK* s)
{
    DATA Y, X, XY, Z;

    X = pop(s);

    if ((X.type != ARRAY) && (X.type != STRING)) {
        X = pop(s);
        X.LONG = X.LONG - 1;
        X.DOUBLE = X.DOUBLE - 1;
        X.CHAR = X.CHAR - 1;
        push(s, X);
    }
    if (X.type == ARRAY) {
        XY.ARRAY = create_stack();
        XY.type = ARRAY;
        Z = X.ARRAY->stack[0];
        for (int i = 1; i < X.ARRAY->n_elems; i++){
            Y = X.ARRAY->stack[i];
            push(XY.ARRAY, Y);
        }
        push(s, XY);
        push(s, Z);
    }
}

void op_remove_last (STACK* s)
{
    DATA Y, X;

    X = pop(s);


    if ((X.type != ARRAY) && (X.type != STRING)) {
        X.LONG = X.LONG + 1;
        X.DOUBLE = X.DOUBLE + 1;
        X.CHAR = X.CHAR + 1;
        push(s, X);
    }
    if (X.type == ARRAY) {
        Y = pop(X.ARRAY);
        push(s, X);
        push(s, Y);
    }
}

void op_sharp(STACK* s)
{
    DATA X, Y, XY;

    Y = pop(s);
    X = pop(s);

    if ((X.type != ARRAY) && (Y.type != ARRAY) && (X.type != STRING) && (Y.type != STRING)) {
        XY.LONG = (long)pow(X.LONG, Y.LONG);
        XY.DOUBLE = pow(X.DOUBLE, Y.DOUBLE);
        XY.type = DOUBLE;
        push(s, XY);
    }

    if (X.type == STRING && Y.type == STRING){
        XY.STRING = strstr(X.STRING, Y.STRING);
        if (XY.STRING != NULL) XY.LONG = XY.STRING - X.STRING;
        else XY.LONG = -1;
        XY.type = LONG;
        push(s, XY);
    }
}

void op_explosion(STACK *s)
{
    DATA X,XY;

    XY.type = LONG;
    X = pop(s);

    if (X.type != ARRAY) {
        X = pop(s);
        XY.LONG = ~(X.LONG);
        push(s, XY);
    }

    if (X.type == ARRAY) {
        for (int i = 0; i < X.ARRAY->n_elems; i++) {
            XY = X.ARRAY->stack[i];
            push(s, XY);
        }
    }
}

