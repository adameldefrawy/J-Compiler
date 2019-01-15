/*
 * jc.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "output.h"

int main (int argc, char **argv)
{

	// Open input j file and create output file
	FILE *input = fopen(argv[1], "r");
	char outputName[strlen(argv[1]) + 3];
	strcpy(outputName, argv[1]);
	outputName[strlen(outputName) - 1] = 'a';
	strcat(outputName, "sm\0");
	FILE* output = fopen(outputName, "w");

	// Handle labels
	char label[strlen(argv[1]) + 1];
	strcpy(label, argv[1]);
	label[strlen(label) - 2] = '\0';
	int label_num = 1;
	int if_num = 1;
	stack *s = malloc(sizeof(stack));
	init_stack(s);

	// Write the ".CODE" label at the top of the output
	fprintf(output, "%s\n", ".CODE");

	// Loop through the file, read tokens, and write into output
	char check;
	while ((check = fgetc(input)) != EOF) {
		// Skip spaces and comments
		if (check == ';') {
			while (check != '\n') {
				check = fgetc(input);
			}
		}
		if (isspace(check) || check == EOF) {
			continue;
		}
		char token_str[MAX_TOKEN_LENGTH] = "";
    	memset(token_str, 0, strlen(token_str));
		while (!isspace(check) && check != EOF) {
			char buffer[2];
			sprintf(buffer, "%c", check);
			strcat(token_str, buffer);
			check = fgetc(input);
		}
		token *newToken = malloc(sizeof(token));
		newToken->type = DEFUN;
		newToken->literal_value = 0;
		newToken->arg_no = 0;
		strcpy(newToken->str, token_str);
		int token_type = read_token(newToken, input);
		//print_token(newToken);
		print_assembly(output, newToken, label, &label_num, &if_num, s);
		free(newToken);
	}

	if (s->first != NULL) {
		printf("NO IF TO MATCH THE ENDIF\n");
		delete_all_entries(s);
		free(s);
		exit(1);
	}
	free(s);
	fclose(output);
	fclose(input);

	return 0;
}