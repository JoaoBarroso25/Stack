** @file Ficheiro Stack.h
 */
#ifndef UNTITLED13_STACK_H
#define UNTITLED13_STACK_H

#endif //UNTITLED13_STACK_H

#ifndef ___STACK_H___

/** STACK H Definido o ficheiro STACK.H */
#define ___STACK_H___

#include <assert.h>

/** ENUM Atribui um valor a cada tipo: LONG,DOUBLE,CHAR,STRING. */
typedef enum {LONG = 1, DOUBLE = 2, CHAR = 4, STRING = 8} TYPE;

/** INTEGER Onde é definido um Inteiro, como LONG ou CHAR. */
#define INTEGER  (LONG | CHAR)

/** NUMERO Onde é definido um Número, como INTERGER ou DOUBLE. */
#define NUMBER   (INTEGER | DOUBLE)

/** Struct onde estão definidas todas os tipos possíveis para o Projeto. */
typedef struct data {
    /** Definido o Type. */
    TYPE type; 
    /** Definido o Long. */
    long LONG; 
    /** Definido o Double. */
    double DOUBLE; 
    /** Definido o Char. */
    char CHAR;
    /** Definido o apontador para Char. */
    char *STRING; 
} DATA; /** Nome atribuído à Struct. */

/** Struct onde estão definidas a stack, o seu tamanho e o número de elementos que tem. */
typedef struct stack {
    /** Definido através do DATA o tipo do apontador para os elementos da Stack. */
    DATA *stack; 
     /** Definido o inteiro Size. */
    int size; 
    /** Definido o inteiro com o número de elementos. */
    int n_elems; 
} STACK; /** Nome atribuído à stack. */

int has_type(DATA elem, int mask);
STACK *create_stack();
void push(STACK *s, DATA elem);
DATA pop(STACK *s);
DATA top(STACK *s);
int is_empty(STACK *s);
void print_stack(STACK *s);
DATA * Find_Elem(STACK* s, long i);

/** STACK_OPERATIONS POP e PUSH name. */
#define STACK_OPERATION_PROTO(_type, _name)   \
  void push_##_name(STACK *s, _type val);     \
  _type pop_##_name(STACK *s);

STACK_OPERATION_PROTO(long, LONG)
STACK_OPERATION_PROTO(double, DOUBLE)
STACK_OPERATION_PROTO(char, CHAR)
STACK_OPERATION_PROTO(char *, STRING)

#endif
