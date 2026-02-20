#include <stdio.h>

#define NOT_INSIDE_STRING 0
#define INSIDE_STRING 1
#define INSIDE_CHAR 2

#define STACK_CAPACITY 1<<10

int main() {
    char c = 0;
    char current = 0;
    char previous = 0;
    int is_inside_string = NOT_INSIDE_STRING;
    bool is_inside_single_comment = false;
    bool is_inside_multi_comment = false;
    bool previous_ignore_syntax = false;

    int line = 1;
    int column = 0;
    char bracket_stack[STACK_CAPACITY];
    int bracket_stack_len = 0;

    while((c = getchar()) != EOF) {
        previous = current;
        current = c;
        column += 1;

        // detect if we are in a string, comment or neither
        if (current == '\\' && previous == '\\') {
            // clear current `\\`, such that it doesn't escape
            // the next character
            current = 0; 
        } else if (is_inside_string == INSIDE_STRING) {
            if (current == '\"' && previous != '\\') {
                is_inside_string = NOT_INSIDE_STRING;
            }
        } else if (is_inside_string == INSIDE_CHAR) {
            if (current == '\'' && previous != '\\') {
                is_inside_string = NOT_INSIDE_STRING;
            }
        } else if (is_inside_single_comment) {
            if (current == '\n') {
                is_inside_single_comment = false;
            }
        } else if (is_inside_multi_comment) {
            if (previous == '*' && current == '/') {
                is_inside_multi_comment = false;
                previous = 0;
            }
        } else {
            if (current == '\"') {
                is_inside_string = INSIDE_STRING;
            } else if (current == '\'') {
                is_inside_string = INSIDE_CHAR;
            } else if (current == '/') {
                if (previous == '/') {
                    is_inside_single_comment = true;
                }
            } else if (current == '*') {
                if (previous == '/') {
                    is_inside_multi_comment = true;
                }
            }
        }

        bool current_ignore_syntax = is_inside_string ||
            is_inside_single_comment ||
            is_inside_multi_comment;
        bool should_ignore_syntax = current_ignore_syntax && previous_ignore_syntax;
        previous_ignore_syntax = current_ignore_syntax;

        // print visualization
        //if (current == '\n') {
        //    putchar('\n');
        //} else if (should_ignore_syntax){
        //    putchar('X');
        //} else {
        //    putchar('.');
        //}
        //
        //continue;

        if (c == '\n') {
            line += 1;
            column = 0;
        }

        if (should_ignore_syntax) {
            continue;
        }

        // we are neither in a string or comment, check if brackets match
        if (current == '(' || current == '{' || current == '[') {
            // push
            if (bracket_stack_len >= STACK_CAPACITY) {
                printf("ERROR: overflow! too many brackets at %i:%i\n", line, column);
                return -1;
            }

            bracket_stack[bracket_stack_len] = current;
            bracket_stack_len += 1;
        } else if (current == ')' || current == '}' || current == ']') {
            // pop
            if (bracket_stack_len <= 0) {
                printf("ERROR: failed to find matching bracket for %c at %i:%i\n", current, line, column);
                return -1;
            }

            bracket_stack_len -= 1;
            char bracket = bracket_stack[bracket_stack_len];

            bool is_paranthesis = bracket == '(' && current == ')';
            bool is_bracket = bracket == '{' && current == '}';
            bool is_brace = bracket == '[' && current == ']';
            bool brackets_match = is_paranthesis ||
                is_bracket ||
                is_brace;

            if (!brackets_match) {
                printf("ERROR: brackets '%c' and '%c' do not match at %i:%i\n", bracket, current, line, column);
                return -1;
            }
        }
    } // end while-loop

    // sanity checks for the end
    if (is_inside_multi_comment) {
        printf("ERROR: multicomment was not closed\n");
        return -1;
    }

    if (bracket_stack_len > 0) {
        char bracket = bracket_stack[bracket_stack_len - 1];
        printf("ERROR: bracket '%c' was not closed\n", bracket);
        return -1;
    }
    
    // success!
    return 0;
}
