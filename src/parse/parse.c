#include "parse.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexeme/lexeme.h"

void print_reserved_word_lowercase(char *lexeme) {
    if (strcmp(lexeme, AND) == 0) {
        fprintf(stdout, "%s", "and");
    } else if (strcmp(lexeme, CLASS) == 0) {
        fprintf(stdout, "%s", "class");
    } else if (strcmp(lexeme, ELSE) == 0) {
        fprintf(stdout, "%s", "else");
    } else if (strcmp(lexeme, FALSE) == 0) {
        fprintf(stdout, "%s", "false");
    } else if (strcmp(lexeme, FOR) == 0) {
        fprintf(stdout, "%s", "for");
    } else if (strcmp(lexeme, FUN) == 0) {
        fprintf(stdout, "%s", "fun");
    } else if (strcmp(lexeme, IF) == 0) {
        fprintf(stdout, "%s", "if");
    } else if (strcmp(lexeme, NIL) == 0) {
        fprintf(stdout, "%s", "nil");
    } else if (strcmp(lexeme, OR) == 0) {
        fprintf(stdout, "%s", "or");
    } else if (strcmp(lexeme, PRINT) == 0) {
        fprintf(stdout, "%s", "print");
    } else if (strcmp(lexeme, RETURN) == 0) {
        fprintf(stdout, "%s", "return");
    } else if (strcmp(lexeme, SUPER) == 0) {
        fprintf(stdout, "%s", "super");
    } else if (strcmp(lexeme, THIS) == 0) {
        fprintf(stdout, "%s", "this");
    } else if (strcmp(lexeme, TRUE) == 0) {
        fprintf(stdout, "%s", "true");
    }
}

int parse(char *file_contents) {
    int error_code = 0;
    int line_number = 1;

    char *c;
    for (c = file_contents; *c != '\0'; c++) {
        char *lexeme = lexeme_from_char(&c);

        if (is_reserved_word(lexeme)) {
            print_reserved_word_lowercase(lexeme);

            // skip until the end of the reserved word
            while (*c != ' ' && *c != '\n' && *c != '\0') {
                c++;
            }
        }
    }

    return error_code;
}