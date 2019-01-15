/*
 * token.c
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

int read_token (token *theToken, FILE *theFile)
{
  // LITERAL (HEX)
  if (theToken->str[0] == '0' && tolower(theToken->str[1]) == 'x') {
    for (int i = 2; i < strlen(theToken->str); i++) {
      if (!isxdigit(theToken->str[i])) {
        theToken->type = BROKEN_TOKEN;
        return BROKEN_TOKEN;
      }
    }
    theToken->type = LITERAL;
    theToken->literal_value = (int) strtol(theToken->str, NULL, 16);
  }
  // LITERAL (DECIMAL)
  else if ((theToken->str[0] == '-' && strlen(theToken->str) > 1) || isdigit(theToken->str[0])) {
    for (int i = 1; i < strlen(theToken->str); i++) {
      if (!isdigit(theToken->str[i])) {
        theToken->type = BROKEN_TOKEN;
      }
    }
    theToken->type = LITERAL;
    theToken->literal_value = (int) strtol(theToken->str, NULL, 10);
  }
  // ADD
  else if (strcmp(theToken->str, "+") == 0) {
    theToken->type = PLUS;
  }
  // SUBTRACT
  else if (strcmp(theToken->str, "-") == 0) {
    theToken->type = MINUS;
  }
  // MULTIPLY
  else if (strcmp(theToken->str, "*") == 0) {
    theToken->type = MUL;
  }
  // DIVIDE
  else if (strcmp(theToken->str, "/") == 0) {
    theToken->type = DIV;
  }
  // MODULUS
  else if (strcmp(theToken->str, "%") == 0) {
    theToken->type = MOD;
  }
  // LESS THAN
  else if (strcmp(theToken->str, "lt") == 0) {
    theToken->type = LT;
  }
  // Less THAN OR EQUAL TO
  else if (strcmp(theToken->str, "le") == 0) {
    theToken->type = LE;
  }
  // EQUAL TO
  else if (strcmp(theToken->str, "eq") == 0) {
    theToken->type = EQ;
  }
  // GREATER THAN OR EQUAL TO
  else if (strcmp(theToken->str, "ge") == 0) {
    theToken->type = GE;
  }
  // GREATER THAN
  else if (strcmp(theToken->str, "gt") == 0) {
    theToken->type = GT;
  }
  // AND
  else if (strcmp(theToken->str, "and") == 0) {
    theToken->type = AND;
  }
  // OR
  else if (strcmp(theToken->str, "or") == 0) {
    theToken->type = OR;
  }
  // NOT
  else if (strcmp(theToken->str, "not") == 0) {
    theToken->type = NOT;
  }
  // DROP
  else if (strcmp(theToken->str, "drop") == 0) {
    theToken->type = DROP;
  }
  // DUPLICATE
  else if (strcmp(theToken->str, "dup") == 0) {
    theToken->type = DUP;
  }
  // SWAP
  else if (strcmp(theToken->str, "swap") == 0) {
    theToken->type = SWAP;
  }
  // ROTATE
  else if (strcmp(theToken->str, "rot") == 0) {
    theToken->type = ROT;
  }
  // ARGN
  else if (theToken->str[0] == 'a' && theToken->str[1] == 'r' && theToken->str[2] == 'g') {
    if (strlen(theToken->str) == 4) {
      if (!isdigit(theToken->str[3])) {
        theToken->type = BROKEN_TOKEN;
      }
      else {
        theToken->type = ARG;
        theToken->arg_no = (int) (theToken->str[3] - '0');
      }
    }
    else if (strlen(theToken->str) == 5) {
      if (!isdigit(theToken->str[3]) || !isdigit(theToken->str[4])) {
        theToken->type = BROKEN_TOKEN;
      }
      else {
        char sub[3];
        sub[0] = theToken->str[3];
        sub[1] = theToken->str[4];
        theToken->arg_no = (int) strtol(sub, NULL, 10);
        if (theToken->arg_no < 1 || theToken->arg_no > 20) {
          theToken->type = BROKEN_TOKEN;
        }
        theToken->type = ARG;
      }
    }
    else {
      theToken->type = BROKEN_TOKEN;
    }
  }
  // IF
  else if (strcmp(theToken->str, "if") == 0) {
    theToken->type = IF;
  }
  // ELSE
  else if (strcmp(theToken->str, "else") == 0) {
    theToken->type = ELSE;
  }
  // ENDIF
  else if (strcmp(theToken->str, "endif") == 0) {
    theToken->type = ENDIF;
  }
  // FUNCTION
  else if (strcmp(theToken->str, "defun") == 0) {
    theToken->type = DEFUN;
    theToken->str[1] = '\0';
    char check;
    while (isspace(check = fgetc(theFile))) {
      continue;
    }
    theToken->str[0] = check;
    int i = 1;
    while (!isspace(check = fgetc(theFile))) {
      theToken->str[i] = check;
      i++;
    }
    theToken->str[i] = '\0';
  }
  // RETURN
  else if (strcmp(theToken->str, "return") == 0) {
    theToken->type = RETURN;
  }
  // IDENTIFIER
  else {
    theToken->type = IDENT;
  }

  return theToken->type;
}

// Extra functions which you may wish to define and use , or not
const char *token_type_to_string (int type) {
  switch(type) {
    case DEFUN:
      return "DEFUN";
    case IDENT:
      return "IDENT";
    case RETURN:
      return "RETURN";
    case PLUS:
      return "PLUS";
    case MINUS:
      return "MINUS";
    case MUL:
      return "MUL";
    case DIV:
      return "DIV";
    case MOD:
      return "MOD";
    case AND:
      return "AND";
    case OR:
      return "OR";
    case NOT:
      return "NOT";
    case LT:
      return "LT";
    case LE:
      return "LE";
    case EQ:
      return "EQ";
    case GE:
      return "GE";
    case GT:
      return "GT";
    case IF:
      return "IF";
    case ELSE:
      return "ELSE";
    case ENDIF:
      return "ENDIF";
    case DROP:
      return "DROP";
    case DUP:
      return "DUP";
    case SWAP:
      return "SWAP";
    case ROT:
      return "ROT";
    case ARG:
      return "ARG";
    case LITERAL:
      return "LITERAL";
    case BROKEN_TOKEN:
      return "BROKEN_TOKEN";
    default:
      return "INVALID TOKEN";
  }
}

void print_token (token *theToken) {
  if (theToken->type == LITERAL) {
    printf("LITERAL %d\n", theToken->literal_value);
  }
  else if (theToken->type == ARG) {
    printf("ARG %d\n", theToken->arg_no);
  }
  else if (theToken->type == DEFUN) {
    printf("DEFUN %s\n", theToken->str);
  }
  else if (theToken->type == IDENT) {
    printf("IDENT %s\n", theToken->str);
  }
  else {
    printf("%s\n", token_type_to_string(theToken->type));
  }
}