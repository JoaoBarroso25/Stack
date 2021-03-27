/**
 *  @file Stack - Ficheiro que contém todas as funções auxiliares para o Ficheiro Main.
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * \brief Função Has_Type
 *
 * Função responsável por verificar se um inteiro é de um certo tipo.
 *
 * @param elem --> Tipo de Dados que vai ser comparado
 * @param mask --> Intiero ao qual vai ser feita a verificação
 *
 * @return --> Retorna 1 se os dois tipos são iguais e retorna 0, caso contrário.
 */
int has_type(DATA elem, int mask) {
    return (elem.type & mask) != 0;
}

/**
 * \brief Função Create_Stack
 *
 * Função responsável por criar a Stack.
 *
 * @return --> Retorna a Stack.
 */
STACK *create_stack() {
    STACK *s = (STACK *) calloc(1, sizeof(STACK));
    //s->n_elems = 0;
    s->size = 100;
    s->stack = (DATA *) calloc(s->size, sizeof(DATA));
    return s;
}

/**
 * \brief Função Push
 *
 * Função responsável por colocar um elemento no top de uma Stack.
 *
 * @param s     --> Corresponde à Stack.
 * @param elem  --> Corresponde ao elemento que irá ser colocado no topo da Stack.
 */
void push(STACK *s, DATA elem) {
    if(s->size == s->n_elems) {
        s->size += 100;
        s->stack = (DATA *) realloc(s->stack, s->size * sizeof(DATA));
    }
    s->stack[s->n_elems] = elem;
    s->n_elems++;
}

/**
 * \brief Função Pop
 *
 * Função responsável por eliminar um elemento do topo da Stack.
 *
 * @param s --> Corresponde à Stack.
 * @return  --> A eliminação do item da stack.
 */
DATA pop(STACK *s) {
    s->n_elems--;
    return s->stack[s->n_elems];
}
/**
 * \brief Função Top
 *
 * Função responsável por retornar o elemento no topo da Stack.
 *
 * @param s --> Corresponde à Stack.
 * @return  --> Retorna o elemento no topo da Stack.
 */
DATA top(STACK *s) {
    return s->stack[s->n_elems - 1];
}

/**
 * \brief Função Is_Empty
 *
 * Função que verifica se uma stack está ou não vazia.
 *
 * @param s --> Corresponde à Stack.
 * @return  --> Retorna 0.
 */
int is_empty(STACK *s) {
    return s->n_elems == 0;
}

/**
 * \brief Função Print_Stack
 *
 * Função responsável por dar display na tela da stack.
 *
 * @param s --> Recebe a stack à iqual vai imprimir.
 */
void print_stack(STACK *s) {
    for(int K = 0; K < s->n_elems; K++) {
        DATA elem = s->stack[K];
        TYPE type = elem.type;
        switch(type) {
            case LONG:
                printf("""%ld", elem.LONG); break;
            case DOUBLE:
                printf(" ""%g", elem.DOUBLE); break;
            case CHAR:
                printf(" ""%c", elem.CHAR); break;
            case STRING:
                printf(" ""%s", elem.STRING); break;
        }
    }
    printf("\n");
}

#define STACK_OPERATION(_type, _name)         \
  void push_##_name(STACK *s, _type val) {    \
    DATA elem;                                \
    elem.type = _name;                        \
    elem._name = val;                         \
    push(s, elem);                            \
  }                                           \
  _type pop_##_name(STACK *s) {               \
    DATA elem = pop(s);                       \
    assert(elem.type == _name);               \
    return elem._name;                        \
  }

/**
 *  \brief Onde definimos todos os casos posíveis de operações com Stacks.
 *
 *  Operações com Stacks
 *
 * @param s     --> corresponde ao tipo do conteúdo da Stack.
 * @param val   --> corresponde ao valor do contéudo da Stack.
 */
STACK_OPERATION(long, LONG)
STACK_OPERATION(double, DOUBLE)
STACK_OPERATION(char, CHAR)
STACK_OPERATION(char *, STRING)