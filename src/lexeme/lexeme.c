#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexeme.h"

const char *LEFT_PAREN = "LEFT_PAREN";
const char *RIGHT_PAREN = "RIGHT_PAREN";
const char *LEFT_BRACE = "LEFT_BRACE";
const char *RIGHT_BRACE = "RIGHT_BRACE";
const char *STAR = "STAR";
const char *DOT = "DOT";
const char *COMMA = "COMMA";
const char *SEMICOLON = "SEMICOLON";

// Assignment
const char *EQUAL = "EQUAL";
const char *EQUAL_EQUAL = "EQUAL_EQUAL";

// Comparison
const char *BANG = "BANG";
const char *BANG_EQUAL = "BANG_EQUAL";
const char *GREATER = "GREATER";
const char *GREATER_EQUAL = "GREATER_EQUAL";
const char *LESS = "LESS";
const char *LESS_EQUAL = "LESS_EQUAL";

// Arithmetic
const char *PLUS = "PLUS";
const char *MINUS = "MINUS";
const char *SLASH = "SLASH";

// String
const char *STRING = "STRING";
const char *STRING_ERROR = "STRING_ERROR";

// Number
const char *NUMBER = "NUMBER";
const char *NUMBER_ERROR = "NUMBER_ERROR";

// Whitespace
const char *NEWLINE = "NEWLINE";
const char *COMMENT = "COMMENT";
const char *WHITESPACE = "WHITESPACE";

const char* lexeme_from_char(char **character) {
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

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      int count_dot = 0;
      char *start = *character;
      while ((**character >= '0' && **character <= '9') || **character == '.') {
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

    case ' ':
    case '\t':
     return WHITESPACE;

    case '\n':
      return NEWLINE;
    default:
      return NULL;
  }
}
