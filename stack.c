/*
 * stack.c
 */

#include "stack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void init_stack (stack *s)
{
  s->first = NULL;
  s->last = NULL;
}

void push (stack *s, int num, bool if_else)
{
  stack_elt *elt = malloc (sizeof(elt) * 2);
  elt->num = num;
  elt->if_else = if_else;
  elt->prev = s->last;

  if (!(s->last)) {
    s->first = elt;
  }
  s->last = elt;
}

int pop (stack *s)
{
  stack_elt *elt;
  
  elt = s->last;

  if (s->first == s->last) {
    s->first = NULL;
    s->last = NULL;
  } else {
    s->last = elt->prev;
  }

  int popped = elt->num;
  free(elt);

  return popped;
}

void delete_all_entries (stack *s)
{
  while (s->first) {
    pop (s);
  }
}