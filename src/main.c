#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *LEFT_PAREN = "LEFT_PAREN";
const char *RIGHT_PAREN = "RIGHT_PAREN";
const char *LEFT_BRACE = "LEFT_BRACE";
const char *RIGHT_BRACE = "RIGHT_BRACE";
const char *STAR = "STAR";
const char *DOT = "DOT";
const char *COMMA = "COMMA";
const char *PLUS = "PLUS";
const char *MINUS = "MINUS";
const char *SEMICOLON = "SEMICOLON";
const char *EOF_TOKEN = "EOF";
const char *NULL_LITERAL = "null";

char *read_file_contents(const char *filename);

void print_token(const char *token_type, const char *lexeme, const char *literal) {
    fprintf(stdout, "%s %s %s\n", token_type, lexeme, literal);
}

void print_unexpected_character(char character, int line_number) {
    fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", line_number, character);
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

    if (strcmp(command, "tokenize") == 0) {
        char *file_contents = read_file_contents(argv[2]);


        bool unexpected_character = false;
        for (int i = 0; i < strlen(file_contents); i++) {
            if (file_contents[i] == '(') {
                print_token(LEFT_PAREN, "(", NULL_LITERAL);
            } else if (file_contents[i] == ')') {
                print_token(RIGHT_PAREN, ")", NULL_LITERAL);
            } else if (file_contents[i] == '{') {
                print_token(LEFT_BRACE, "{", NULL_LITERAL);
            } else if (file_contents[i] == '}') {
                print_token(RIGHT_BRACE, "}", NULL_LITERAL);
            } else if (file_contents[i] == '*') {
                print_token(STAR, "*", NULL_LITERAL);
            } else if (file_contents[i] == '.') {
                print_token(DOT, ".", NULL_LITERAL);
            } else if (file_contents[i] == ',') {
                print_token(COMMA, ",", NULL_LITERAL);
            } else if (file_contents[i] == '+') {
                print_token(PLUS, "+", NULL_LITERAL);
            } else if (file_contents[i] == '-') {
                print_token(MINUS, "-", NULL_LITERAL);
            } else if (file_contents[i] == ';') {
                print_token(SEMICOLON, ";", NULL_LITERAL);
            } else {
                print_unexpected_character(file_contents[i], 1);
                unexpected_character = true;
            }
        }

        print_eof_token();

        // Failed to tokenize
        if (unexpected_character) {
            return 65;
        }

        free(file_contents);
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
