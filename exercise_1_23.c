#include <stdio.h>

int main() {
    char current = 0;
    char previous = 0;
    bool is_inside_string = false;
    bool is_inside_single_comment = false;
    bool is_inside_multi_comment = false;

    while((current = getchar()) != EOF) {
        if (is_inside_string) {
            putchar(current);
            if (current == '\"') {
                is_inside_string = false;
            }
        } else if (is_inside_single_comment) {
            if (current == '\n') {
                is_inside_single_comment = false;
            }
        } else if (is_inside_multi_comment) {
            if (previous == '*' && current == '/') {
                is_inside_multi_comment = false;
                previous = 0;
                continue;
            }
        } else {
            if (current == '\"') {
                if (previous == '/') {
                    putchar('/');
                }

                putchar(current);
                is_inside_string = true;
            } else if (current == '/') {
                if (previous == '/') {
                    is_inside_single_comment = true;
                }
            } else if (current == '*') {
                if (previous == '/') {
                    is_inside_multi_comment = true;
                } else {
                    putchar(current);
                }
            } else {
                if (previous == '/') {
                    putchar('/');
                }

                putchar(current);
            }
        }

        previous = current;
    }

    return 0;
}
