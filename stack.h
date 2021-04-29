** @file Ficheiro Stack.h
 */
#ifndef UNTITLED13_STACK_H
#define UNTITLED13_STACK_H

#endif //UNTITLED13_STACK_H

#ifndef ___STACK_H___

/*! \def STACK H
 *  \brief Definido o ficheiro STACK.H
 */
#define ___STACK_H___

#include <assert.h>

/*! \enum ENUM
 *  \brief Atribui um valor a cada tipo: LONG,DOUBLE,CHAR,STRING.
 *
 */
typedef enum {LONG = 1, DOUBLE = 2, CHAR = 4, STRING = 8} TYPE;

/*! \def INTEGER
 *  \brief Onde é definido um Inteiro, como LONG ou CHAR.
 *
 */
#define INTEGER  (LONG | CHAR)

/*! \def NUMERO
 *  \brief Onde é definido um Número, como INTERGER ou DOUBLE.
 *
 */
#define NUMBER   (INTEGER | DOUBLE)

/*! \struct Struct com os Tipos.
 *  \brief Struct onde estão definidas todas os tipos possíveis para o Projeto.
 *
 */
typedef struct data {
    TYPE type; /*!< Definido o Type. */
    // Esta parte devia ser transformada numa union mais tarde
    long LONG; /*!< Definido o Long. */
    double DOUBLE; /*!< Definido o Double. */
    char CHAR; /*!< Definido o Char. */
    char *STRING; /*!< Definido o apontador para Char. */
} DATA; /*!< Nome atribuído à Struct. */

/*! \struct Struct com a Stack.
 *  \brief Struct onde estão definidas a stack, o seu tamanho e o número de elementos que tem.
 *
 */
typedef struct stack {
    DATA *stack; /*!< Definido através do DATA o tipo do apontador para os elementos da Stack. */
    int size; /*!< Definido o inteiro Size. */
    int n_elems; /*!< Definido o inteiro com o número de elementos. */
} STACK; /*!< Nome atribuído à stack. */

int has_type(DATA elem, int mask);
STACK *create_stack();
void push(STACK *s, DATA elem);
DATA pop(STACK *s);
DATA top(STACK *s);
int is_empty(STACK *s);
void print_stack(STACK *s);
DATA * Find_Elem(STACK* s, long i);

/*! \def STACK_OPERATIONS
 *  \brief POP e PUSH name.
 *
 */
#define STACK_OPERATION_PROTO(_type, _name)   \
  void push_##_name(STACK *s, _type val);     \
  _type pop_##_name(STACK *s);

STACK_OPERATION_PROTO(long, LONG)
STACK_OPERATION_PROTO(double, DOUBLE)
STACK_OPERATION_PROTO(char, CHAR)
STACK_OPERATION_PROTO(char *, STRING)

#endif
