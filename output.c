/*
 * output.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "output.h"

void print_prologue (FILE *output)
{
	fprintf(output, "\t;; prologue\n");
	fprintf(output, "\tADD R6, R6, #-3\n");
	fprintf(output, "\tSTR R7, R6, #1\n");
	fprintf(output, "\tSTR R5, R6, #0\n");
	fprintf(output, "\tADD R5, R6, #0\n\n");

}

void print_epilogue (FILE *output)
{
	fprintf(output, "\t;; epilogue\n");
	fprintf(output, "\tLDR R0, R6, #0\n");
	fprintf(output, "\tSTR R0, R5, #2\n");
	fprintf(output, "\tADD R6, R5, #0\n");
	fprintf(output, "\tADD R6, R6, #2\n");
	fprintf(output, "\tLDR R7, R5, #1\n");
	fprintf(output, "\tLDR R5, R5, #0\n");
	fprintf(output, "\tRET\n\n");
}

void print_assembly (FILE *output, token *theToken, char *filename, int *label_num, int *if_num, stack *s)
{
	short int low;
	short int high;
	short int offset;
	switch(theToken->type) {
		case DEFUN:
			fprintf(output, "\t.FALIGN\n%s\n", theToken->str);
			print_prologue(output);
			break;
		case IDENT:
			fprintf(output, "\tLEA R7 %s\n", theToken->str);
			fprintf(output, "\tJSRR R7\n");
			break;
		case RETURN:
			print_epilogue(output);
			break;
		case PLUS:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tADD R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case MINUS:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tSUB R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case MUL:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tMUL R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case DIV:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tDIV R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case MOD:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tMOD R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case AND:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tAND R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case OR:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tOR R0, R0, R1\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case NOT:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tNOT R0, R0\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case LT:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tCMP R0, R1\n");
			fprintf(output, "\tBRn L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #0\n");
			fprintf(output, "\tJMP L%d_%s\n", *label_num, filename);
			(*label_num)--;
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #1\n");
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
			break;
		case LE:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tCMP R0, R1\n");
			fprintf(output, "\tBRnz L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #0\n");
			fprintf(output, "\tJMP L%d_%s\n", *label_num, filename);
			(*label_num)--;
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #1\n");
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case EQ:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tCMP R0, R1\n");
			fprintf(output, "\tBRz L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #0\n");
			fprintf(output, "\tJMP L%d_%s\n", *label_num, filename);
			(*label_num)--;
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #1\n");
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case GE:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tCMP R0, R1\n");
			fprintf(output, "\tBRzp L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #0\n");
			fprintf(output, "\tJMP L%d_%s\n", *label_num, filename);
			(*label_num)--;
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #1\n");
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case GT:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tCMP R0, R1\n");
			fprintf(output, "\tBRp L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #0\n");
			fprintf(output, "\tJMP L%d_%s\n", *label_num, filename);
			(*label_num)--;
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tCONST R0, #1\n");
			fprintf(output, "L%d_%s\n", *label_num, filename);
			(*label_num)++;
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case IF:
			push(s, *if_num, 0);
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tADD R6, R6, #1\n");
			fprintf(output, "\tCMPI R0, #0\n");
			fprintf(output, "\tBRz ELSE%d_%s\n", *if_num, filename);
			(*if_num)++;
			break;
		case ELSE:
			s->last->if_else = 1;
			fprintf(output, "\tJMP ENDIF%d_%s\n", s->last->num, filename);
			fprintf(output, "ELSE%d_%s\n", s->last->num, filename);
			break;
		case ENDIF:
			if (s->first == NULL) {
				printf("CALLED ENDIF BEFORE IF\n");
				delete_all_entries(s);
				free(s);
				free(theToken);
				exit(1);				
			}
			if (!s->last->if_else) {
				fprintf(output, "ELSE%d_%s\n", s->last->num, filename);
			}
			fprintf(output, "ENDIF%d_%s\n", s->last->num, filename);
			pop(s);
			break;
		case DROP:
			fprintf(output, "\tADD R6, R6, #1\n");
			break;
		case DUP:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tADD R6, R6, #-1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case SWAP:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tSTR R0, R6, #1\n");
			fprintf(output, "\tSTR R1, R6, #0\n");
			break;
		case ROT:
			fprintf(output, "\tLDR R0, R6, #0\n");
			fprintf(output, "\tLDR R1, R6, #1\n");
			fprintf(output, "\tLDR R2, R6, #2\n");
			fprintf(output, "\tSTR R0, R6, #1\n");
			fprintf(output, "\tSTR R1, R6, #2\n");
			fprintf(output, "\tSTR R2, R6, #0\n");
			break;
		case ARG:
			offset = theToken->arg_no + 2;
			fprintf(output, "\tLDR R0, R5, #%d\n", offset);
			fprintf(output, "\tADD R6, R6, #-1\n");
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		case LITERAL:
			fprintf(output, "\tADD R6, R6, #-1\n");
			if (theToken->literal_value > 255 || theToken->literal_value < -256) {
				low = (unsigned short int) theToken->literal_value % 256;
				high = (unsigned short int) theToken->literal_value / 256;
				fprintf(output, "\tCONST R0, #%d\n", low);
				fprintf(output, "\tHICONST R0, #%d\n", high);
			}
			else {
				fprintf(output, "\tCONST R0, #%d\n", theToken->literal_value);
			}
			fprintf(output, "\tSTR R0, R6, #0\n");
			break;
		default:
			printf("%s IS AN INVALID TOKEN\n", theToken->str);
			delete_all_entries(s);
			free(s);
			free(theToken);
			exit(1);
	}
}
