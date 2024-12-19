#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexeme/lexeme.h"

const char *EOF_TOKEN = "EOF";
const char *NULL_LITERAL = "null";

char *read_file_contents(const char *filename);

void print_token(const char *lexeme, char character, const char *literal) {
    if (strcmp(lexeme, BANG_EQUAL) == 0)  {
        fprintf(stdout, "%s %s %s\n", lexeme, "!=", literal);
        return;
    } else if (strcmp(lexeme, EQUAL_EQUAL) == 0) {
        fprintf(stdout, "%s %s %s\n", lexeme, "==", literal);
        return;
    } else if (strcmp(lexeme, GREATER_EQUAL) == 0) {
        fprintf(stdout, "%s %s %s\n", lexeme, ">=", literal);
        return;
    } else if (strcmp(lexeme, LESS_EQUAL) == 0) {
        fprintf(stdout, "%s %s %s\n", lexeme, "<=", literal);
        return;
    }    

    fprintf(stdout, "%s %c %s\n", lexeme, character, literal);
}

void print_string(char **character, int line_number) {
    (*character)++;
    char *start = *character;
    char *end = start;
    
    while (*end != '"' && *end != '\0') {
        end++;
    }

    int length = end - start;
    char *string_content = malloc(length + 1);
    strncpy(string_content, start, length);
    string_content[length] = '\0';
    
    fprintf(stdout, "%s \"%s\" %s\n", STRING, string_content, string_content);
    
    *character = end;
    
    free(string_content);
}

void print_number(char **character) {
    char *start = *character;
    int count_dot = 0;
    // if no count dot then number would be number.0 (42.0)
    // if count dot then number would be number.number (42.42)

    while (**character >= '0' && **character <= '9' || **character == '.') {
        if (**character == '.') {
            count_dot++;
        }

        (*character)++;
    }

    int length = *character - start;
    char *number_content = malloc(length + 3);
    char *number_content_original = malloc(length + 3);
    if (count_dot == 0) {
        // number would be number.0 (42.0)
        strncpy(number_content, start, length);
        number_content[length] = '.';
        number_content[length + 1] = '0';
        number_content[length + 2] = '\0';
    } else {
        // number would be number.number (42.42)
        strncpy(number_content, start, length);
        number_content[length] = '\0';

        // transform trailing zeros to one zero
        int i; 
        for (i = length - 1; i >= 0; i--) {
            if (number_content[i] == '0') {
                number_content[i] = '\0';
            } else {
                break;
            }
        }

        if (number_content[i] == '.') {
            number_content[i+1]= '0';
        }
    }
    strncpy(number_content_original, start, length);
    number_content_original[length] = '\0';

    fprintf(stdout, "%s %s %s\n", NUMBER, number_content_original, number_content);

    (*character)--;
    free(number_content);
    free(number_content_original);
}
 
void print_identifier(char **character) {
    char *start = *character;
    while (
        (**character >= 'a' && **character <= 'z') 
        || (**character >= 'A' && **character <= 'Z') 
        || (**character >= '0' && **character <= '9')
        || **character == '_') {
        (*character)++;
    }

    int length = *character - start;
    char *identifier_content = malloc(length + 1);
    strncpy(identifier_content, start, length);
    identifier_content[length] = '\0';

    fprintf(stdout, "%s %s %s\n", IDENTIFIER, identifier_content, NULL_LITERAL);

    if (**character != '\0') {
        (*character)--;
    }

    free(identifier_content);
}

void print_unexpected_character(char character, int line_number) {
    fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", line_number, character);
}

void print_string_error(int line_number) {
    fprintf(stderr, "[line %d] Error: Unterminated string.\n", line_number);
}

void print_eof_token() {
    fprintf(stdout, "%s %s %s\n", EOF_TOKEN, "", NULL_LITERAL);
}

int main(int argc, char *argv[]) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3) {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    const char *command = argv[1];
    int error_code = 0;
    int line_number = 1;

    if (strcmp(command, "tokenize") == 0) {
        char *file_contents = read_file_contents(argv[2]);

        char *c;
        for (c = file_contents; *c != '\0'; c++) {
            const char *lexeme = lexeme_from_char(&c);

            // error code first
            if (lexeme == NULL) {
                print_unexpected_character(*c, line_number);
                error_code = 65;
                continue;
            } else if (strcmp(lexeme, STRING_ERROR) == 0) {
                print_string_error(line_number);
                error_code = 65;
                continue;
            }  

            // skip whitespace
            else if (strcmp(lexeme, WHITESPACE) == 0) {
                continue;
            } else if (strcmp(lexeme, COMMENT) == 0) {
                while (*c != '\n' && *c != '\0') {
                    c++;
                }
                line_number++;
                continue;
            } else if (strcmp(lexeme, NEWLINE) == 0) {
                line_number++;
                continue;
            } 

            // special cases
            else if (strcmp(lexeme, STRING) == 0) {
                print_string(&c, line_number);
                continue;
            } else if (strcmp(lexeme, NUMBER) == 0) {
                print_number(&c);
                continue;
            }

            // identifier
            else if (strcmp(lexeme, IDENTIFIER) == 0) {
                print_identifier(&c);
                continue;
            }

            print_token(lexeme, *c, NULL_LITERAL);
        }

        print_eof_token();

        free(file_contents);
        return error_code;
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}

char *read_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_contents = malloc(file_size + 1);
    if (file_contents == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Error reading file contents\n");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}
