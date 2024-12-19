#ifndef LEXEME_H
#define LEXEME_H

// Declare all the constants as extern
extern const char *LEFT_PAREN;
extern const char *RIGHT_PAREN;
extern const char *LEFT_BRACE;
extern const char *RIGHT_BRACE;
extern const char *STAR;
extern const char *DOT;
extern const char *COMMA;
extern const char *SEMICOLON;

// Assignment
extern const char *EQUAL;
extern const char *EQUAL_EQUAL;

// Comparison
extern const char *BANG;
extern const char *BANG_EQUAL;
extern const char *GREATER;
extern const char *GREATER_EQUAL;
extern const char *LESS;
extern const char *LESS_EQUAL;

// Arithmetic
extern const char *PLUS;
extern const char *MINUS;
extern const char *SLASH;

// String
extern const char *STRING;
extern const char *STRING_ERROR;

// Number
extern const char *NUMBER;
extern const char *NUMBER_ERROR;

// Identifier
extern const char *IDENTIFIER;

// Whitespace
extern const char *NEWLINE;
extern const char *COMMENT;
extern const char *WHITESPACE;

// Declare the function prototype
const char* lexeme_from_char(char **character);

#endif // LEXEME_H 