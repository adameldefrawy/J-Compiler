/*
 * stack.h
 */

#include <stdbool.h>


typedef struct stack_elt_tag {
  int num;
  bool if_else;
  struct stack_elt_tag *prev;
} stack_elt;

typedef struct {
  stack_elt *first, *last;
} stack;

void init_stack (stack *s);
void push (stack *s, int num, bool if_else);
int pop (stack *s);
void delete_all_entries (stack *s);