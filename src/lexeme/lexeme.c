#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexeme.h"

char *LEFT_PAREN = "LEFT_PAREN";
char *RIGHT_PAREN = "RIGHT_PAREN";
char *LEFT_BRACE = "LEFT_BRACE";
char *RIGHT_BRACE = "RIGHT_BRACE";
char *STAR = "STAR";
char *DOT = "DOT";
char *COMMA = "COMMA";
char *SEMICOLON = "SEMICOLON";

// Assignment
char *EQUAL = "EQUAL";
char *EQUAL_EQUAL = "EQUAL_EQUAL";

// Comparison
char *BANG = "BANG";
char *BANG_EQUAL = "BANG_EQUAL";
char *GREATER = "GREATER";
char *GREATER_EQUAL = "GREATER_EQUAL";
char *LESS = "LESS";
char *LESS_EQUAL = "LESS_EQUAL";

// Arithmetic
char *PLUS = "PLUS";
char *MINUS = "MINUS";
char *SLASH = "SLASH";

// String
char *STRING = "STRING";
char *STRING_ERROR = "STRING_ERROR";

// Number
char *NUMBER = "NUMBER";
char *NUMBER_ERROR = "NUMBER_ERROR";

// Identifier
char *IDENTIFIER = "IDENTIFIER";

// Whitespace
char *NEWLINE = "NEWLINE";
char *COMMENT = "COMMENT";
char *WHITESPACE = "WHITESPACE";

// Reserved words
char *AND = "AND";
char *CLASS = "CLASS";
char *ELSE = "ELSE";
char *FALSE = "FALSE";
char *FOR = "FOR";
char *FUN = "FUN";
char *IF = "IF";
char *NIL = "NIL";
char *OR = "OR";
char *PRINT = "PRINT";
char *RETURN = "RETURN";
char *SUPER = "SUPER";
char *THIS = "THIS";
char *TRUE = "TRUE";
char *VAR = "VAR";
char *WHILE = "WHILE";

bool is_reserved_word(char *lexeme) {
    return strcmp(lexeme, AND) == 0 || strcmp(lexeme, CLASS) == 0 ||
           strcmp(lexeme, ELSE) == 0 || strcmp(lexeme, FALSE) == 0 ||
           strcmp(lexeme, FOR) == 0 || strcmp(lexeme, FUN) == 0 ||
           strcmp(lexeme, IF) == 0 || strcmp(lexeme, NIL) == 0 ||
           strcmp(lexeme, OR) == 0 || strcmp(lexeme, PRINT) == 0 ||
           strcmp(lexeme, RETURN) == 0 || strcmp(lexeme, SUPER) == 0 ||
           strcmp(lexeme, THIS) == 0 || strcmp(lexeme, TRUE) == 0 ||
           strcmp(lexeme, VAR) == 0 || strcmp(lexeme, WHILE) == 0;
}

char *lexeme_from_char(char **character) {
    switch (**character) {
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
        case '{':
            return LEFT_BRACE;
        case '}':
            return RIGHT_BRACE;
        case '*':
            return STAR;
        case '.':
            return DOT;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;

        case '=':
            (*character)++;
            if (**character == '=') {
                return EQUAL_EQUAL;
            }
            (*character)--;
            return EQUAL;
        case '!':
            (*character)++;
            if (**character == '=') {
                return BANG_EQUAL;
            }
            (*character)--;
            return BANG;
        case '>':
            (*character)++;
            if (**character == '=') {
                return GREATER_EQUAL;
            }
            (*character)--;
            return GREATER;
        case '<':
            (*character)++;
            if (**character == '=') {
                return LESS_EQUAL;
            }
            (*character)--;
            return LESS;

        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            (*character)++;
            if (**character == '/') {
                return COMMENT;
            }
            (*character)--;
            return SLASH;
        case '"':
            (*character)++;
            while (**character != '"' && **character != '\0') {
                (*character)++;
            }

            if (**character != '"') {
                return STRING_ERROR;
            }

            // if yes then return STRING until beginning again
            (*character)--;
            while (**character != '"') {
                (*character)--;
            }

            return STRING;

        case '0' ... '9':
            int count_dot = 0;
            char *start = *character;
            while ((**character >= '0' && **character <= '9') ||
                   **character == '.') {
                if (**character == '.') {
                    count_dot++;
                }

                if (count_dot > 1) {
                    return NUMBER_ERROR;
                }

                (*character)++;
            }

            if (count_dot > 1) {
                return NUMBER_ERROR;
            }

            // if valid then return pointer to first character of number
            *character = start;
            return NUMBER;

        case '_':
        case 'a' ... 'z':
        case 'A' ... 'Z':
            // have to check if it is a reserved word
            char *identifier_start = *character;
            while ((**character >= 'a' && **character <= 'z') ||
                   (**character >= 'A' && **character <= 'Z') ||
                   (**character >= '0' && **character <= '9') ||
                   **character == '_') {
                (*character)++;
            }

            int length = *character - identifier_start;
            char *identifier_content = malloc(length + 1);
            strncpy(identifier_content, identifier_start, length);
            identifier_content[length] = '\0';

            *character = identifier_start;
            if (strcmp(identifier_content, "and") == 0) {
                free(identifier_content);   
                return AND;
            } else if (strcmp(identifier_content, "class") == 0) {
                free(identifier_content);
                return CLASS;
            } else if (strcmp(identifier_content, "else") == 0) {
                free(identifier_content);
                    return ELSE;
            } else if (strcmp(identifier_content, "false") == 0) {
                free(identifier_content);
                return FALSE;
            } else if (strcmp(identifier_content, "for") == 0) {
                free(identifier_content);
                return FOR;
            } else if (strcmp(identifier_content, "fun") == 0) {
                free(identifier_content);
                return FUN;
            } else if (strcmp(identifier_content, "if") == 0) {
                free(identifier_content);
                return IF;
            } else if (strcmp(identifier_content, "nil") == 0) {
                free(identifier_content);
                return NIL;
            } else if (strcmp(identifier_content, "or") == 0) {
                free(identifier_content);
                return OR;
            } else if (strcmp(identifier_content, "print") == 0) {
                free(identifier_content);
                return PRINT;
            } else if (strcmp(identifier_content, "return") == 0) {
                return RETURN;
            } else if (strcmp(identifier_content, "super") == 0) {
                free(identifier_content);
                return SUPER;
            } else if (strcmp(identifier_content, "this") == 0) {
                free(identifier_content);
                return THIS;
            } else if (strcmp(identifier_content, "true") == 0) {
                free(identifier_content);
                return TRUE;
            } else if (strcmp(identifier_content, "var") == 0) {
                return VAR;
            } else if (strcmp(identifier_content, "while") == 0) {
                free(identifier_content);
                return WHILE;
            }

            free(identifier_content);
            return IDENTIFIER;
        case ' ':
        case '\t':
            return WHITESPACE;

        case '\n':
            return NEWLINE;
        default:
            return NULL;
    }
}
