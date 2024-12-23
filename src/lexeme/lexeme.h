#ifndef LEXEME_H
#define LEXEME_H

#include <stdbool.h>

// Declare all the ants as extern
extern char *LEFT_PAREN;
extern char *RIGHT_PAREN;
extern char *LEFT_BRACE;
extern char *RIGHT_BRACE;
extern char *STAR;
extern char *DOT;
extern char *COMMA;
extern char *SEMICOLON;

// Assignment
extern char *EQUAL;
extern char *EQUAL_EQUAL;

// Comparison
extern char *BANG;
extern char *BANG_EQUAL;
extern char *GREATER;
extern char *GREATER_EQUAL;
extern char *LESS;
extern char *LESS_EQUAL;

// Arithmetic
extern char *PLUS;
extern char *MINUS;
extern char *SLASH;

// String
extern char *STRING;
extern char *STRING_ERROR;

// Number
extern char *NUMBER;
extern char *NUMBER_ERROR;

// Identifier
extern char *IDENTIFIER;

// Whitespace
extern char *NEWLINE;
extern char *COMMENT;
extern char *WHITESPACE;

// Reserved words
// and, class, else, false, for, fun, if, nil, or, print, return, super, this, true, var, while.
extern char *AND;
extern char *CLASS;
extern char *ELSE;
extern char *FALSE;
extern char *FOR;
extern char *FUN;
extern char *IF;
extern char *NIL;
extern char *OR;
extern char *PRINT;
extern char *RETURN;
extern char *SUPER;
extern char *THIS;
extern char *TRUE;
extern char *VAR;
extern char *WHILE;

// Declare the function prototype
void print_unexpected_character(char character, int line_number);

char *lexeme_from_char(char **character);

bool is_reserved_word(char *lexeme);

#endif  // LEXEME_H
