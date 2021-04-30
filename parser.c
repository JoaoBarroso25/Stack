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
void Oprations(STACK *s, char *token, int *AZ) {
    DATA Y, X, Z, XY, *P;
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
        if (X.type == LONG && Y.type == LONG) XY.type = LONG;
        else XY.type = DOUBLE;
        XY.LONG = (int) (X.LONG / Y.LONG);
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
        XY.LONG = (long) pow(X.LONG, Y.LONG);
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
        X.CHAR = (char) X.LONG;
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
    if (strcmp(token, "=") == 0) {
        Y = pop(s);
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE == Y.DOUBLE) X.DOUBLE = 1;
        else X.DOUBLE = 0;
        push(s, X);
    }
    if (strcmp(token, ">") == 0) {
        Y = pop(s);
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE > Y.DOUBLE) X.DOUBLE = 1;
        else X.DOUBLE = 0;
        push(s, X);
    }
    if (strcmp(token, "<") == 0) {
        Y = pop(s);
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE < Y.DOUBLE) X.DOUBLE = 1;
        else X.DOUBLE = 0;
        push(s, X);
    }
    if (strcmp(token, "e>") == 0) {
        Y = pop(s);
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE > Y.DOUBLE) push(s, X);
        else push(s, Y);
    }
    if (strcmp(token, "e<") == 0) {
        Y = pop(s);
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE < Y.DOUBLE) push(s, X);
        else push(s, Y);
    }
    if (strcmp(token, "!") == 0) {
        X = pop(s);
        X.type = DOUBLE;
        if (X.DOUBLE != 0) {
            X.DOUBLE = 0;
            X.LONG = 0;
        } else {
            X.DOUBLE = 1;
            X.LONG = 1;
        }
        push(s, X);
    }
    if (strcmp(token, "e&") == 0) {   // verficar ainda
        Y = pop(s);
        X = pop(s);
        if (X.type == DOUBLE && Y.type == DOUBLE) {
            if (X.DOUBLE == 0 || Y.DOUBLE == 0) {
                X.DOUBLE = 0;
                push(s, X);
            } else {
                if (X.DOUBLE >= Y.DOUBLE) {
                    push(s, X);
                } else push(s, Y);
            }
        } else {
            if (X.LONG == 0 || Y.LONG == 0) { // esta linha
                X.LONG = 0;
                push(s, X);
            } else {
                if (X.LONG >= Y.LONG) {
                    push(s, X);
                } else push(s, Y);
            }
        }
    }
    if (strcmp(token, "e|") == 0) {   // verficar - acho que ja esta bem
        X = pop(s);
        Y = pop(s);
        if (X.type == DOUBLE || Y.type == DOUBLE) {
            if (X.DOUBLE == 0 || Y.DOUBLE == 0) {
                X.DOUBLE = 0;
                push (s,X);
            }
            else {
                if (X.DOUBLE >= Y.DOUBLE) push (s, X);
                else push(s, Y);
            }
        }
        else {
            if (X.DOUBLE == 0 || Y.DOUBLE == 0) {
                X.DOUBLE = 0;
                push (s,X);
            }
            else if (X.LONG >= Y.LONG) push (s, X);
            else push(s, Y);
        }
    }
    if (strcmp(token, "?") == 0) { // verficar - x y z com ordem trocada
        X = pop(s);
        Y = pop(s);
        Z = pop(s);
        if (Z.LONG == 0 || Z.DOUBLE == 0) {
            push(s, X);
        }
        else push(s,Y);
        }
    if (strcmp(token, "A") == 0) {
        X.LONG = AZ[0];
        X.DOUBLE = AZ[0];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "B") == 0) {
        X.LONG = AZ[1];
        X.DOUBLE = AZ[1];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "C") == 0) {
        X.LONG = AZ[2];
        X.DOUBLE = AZ[2];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "D") == 0) {
        X.LONG = AZ[3];
        X.DOUBLE = AZ[3];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "E") == 0) {
        X.LONG = AZ[4];
        X.DOUBLE = AZ[4];
        X.type = LONG;
        push(s, X);

    }
    if (strcmp(token, "F") == 0) {
        X.LONG = AZ[5];
        X.DOUBLE = AZ[5];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "G") == 0) {
        X.LONG = AZ[6];
        X.DOUBLE = AZ[6];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "H") == 0) {
        X.LONG = AZ[7];
        X.DOUBLE = AZ[7];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "I") == 0) {
        X.LONG = AZ[8];
        X.DOUBLE = AZ[8];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "J") == 0) {
        X.LONG = AZ[9];
        X.DOUBLE = AZ[9];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "K") == 0) {
        X.LONG = AZ[10];
        X.DOUBLE = AZ[10];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "L") == 0) {
        X.LONG = AZ[11];
        X.DOUBLE = AZ[11];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "M") == 0) {
        X.LONG = AZ[12];
        X.DOUBLE = AZ[12];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "O") == 0) {
        X.LONG = AZ[14];
        X.DOUBLE = AZ[14];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "P") == 0) {
        X.LONG = AZ[15];
        X.DOUBLE = AZ[15];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "Q") == 0) {
        X.LONG = AZ[16];
        X.DOUBLE = AZ[16];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "R") == 0) {
        X.LONG = AZ[17];
        X.DOUBLE = AZ[17];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "T") == 0) {
        X.LONG = AZ[19];
        X.DOUBLE = AZ[19];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "U") == 0) {
        X.LONG = AZ[20];
        X.DOUBLE = AZ[20];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "V") == 0) {
        X.LONG = AZ[21];
        X.DOUBLE = AZ[21];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "W") == 0) {
        X.LONG = AZ[22];
        X.DOUBLE = AZ[22];
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "N") == 0) { // VERIFICAR
        X.CHAR = '\n';
        X.type = CHAR;
        push(s, X);
    }
    if (strcmp(token, "S") == 0) { // VERIFICAR
        X.CHAR = ' ';
        X.type = CHAR;
        push(s, X);
    }
    if (strcmp(token, "X") == 0) {
        X.LONG = 0;
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "Y") == 0) {
        X.LONG = 1;
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, "Z") == 0) {
        X.LONG = 2;
        X.type = LONG;
        push(s, X);
    }
    if (strcmp(token, ":A") == 0) {
        X = top(s);
        AZ[0] = X.LONG;
    }
    if (strcmp(token, ":B") == 0) {
        X = top(s);
        AZ[1] = X.LONG;
    }
    if (strcmp(token, ":C") == 0) {
        X = top(s);
        AZ[2] = X.LONG;
    }
    if (strcmp(token, ":D") == 0) {
        X = top(s);
        AZ[3] = X.LONG;
    }
    if (strcmp(token, ":E") == 0) {
        X = top(s);
        AZ[4] = X.LONG;
    }
    if (strcmp(token, ":F") == 0) {
        X = top(s);
        AZ[5] = X.LONG;
    }
    if (strcmp(token, ":G") == 0) {
        X = top(s);
        AZ[6] = X.LONG;
    }
    if (strcmp(token, ":H") == 0) {
        X = top(s);
        AZ[7] = X.LONG;
    }
    if (strcmp(token, ":I") == 0) {
        X = top(s);
        AZ[8] = X.LONG;
    }
    if (strcmp(token, ":J") == 0) {
        X = top(s);
        AZ[9] = X.LONG;
    }
    if (strcmp(token, ":K") == 0) {
        X = top(s);
        AZ[10] = X.LONG;
    }
    if (strcmp(token, ":L") == 0) {
        X = top(s);
        AZ[11] = X.LONG;
    }
    if (strcmp(token, ":M") == 0) {
        X = top(s);
        AZ[12] = X.LONG;
    }
    if (strcmp(token, ":O") == 0) {
        X = top(s);
        AZ[14] = X.LONG;
    }
    if (strcmp(token, ":P") == 0) {
        X = top(s);
        AZ[15] = X.LONG;
    }
    if (strcmp(token, ":Q") == 0) {
        X = top(s);
        AZ[16] = X.LONG;
    }
    if (strcmp(token, ":R") == 0) {
        X = top(s);
        AZ[17] = X.LONG;
    }
    if (strcmp(token, ":T") == 0) {
        X = top(s);
        AZ[19] = X.LONG;
    }
    if (strcmp(token, ":U") == 0) {
        X = top(s);
        AZ[20] = X.LONG;
    }
    if (strcmp(token, ":V") == 0) {
        X = top(s);
        AZ[21] = X.LONG;
    }
    if (strcmp(token, ":W") == 0) {
        X = top(s);
        AZ[22] = X.LONG;
    }
    if (strcmp(token, ":X") == 0) {
        X = top(s);
        AZ[23] = X.LONG;
    }
    if (strcmp(token, ":Y") == 0) {
        X = top(s);
        AZ[24] = X.LONG;
    }
    if (strcmp(token, ":Z") == 0) {
        X = top(s);
        AZ[25] = X.LONG;
    }
}
