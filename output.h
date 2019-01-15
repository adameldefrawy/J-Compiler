/*
 * output.h
 */

#include <stdio.h>
#include "token.h"
#include "stack.h"

void print_prologue (FILE *output);
void print_epilogue (FILE *output);
void print_assembly (FILE *output, token *theToken, char *filename, int *label_num, int *if_num, stack *s);