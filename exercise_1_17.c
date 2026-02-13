#include "stdlib.h"
#include "stdio.h"

#define MAX_LINE_LENGTH 1<<10

int main() {
    int c;
    char line[MAX_LINE_LENGTH + 1];
    int line_len = 0;

    bool can_print = false;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (can_print) {
                line[line_len] = 0;
                printf("%s\n", line);
                can_print = false;
                line_len = 0;
            }

            continue;
        }

        if (line_len < MAX_LINE_LENGTH) {
            line[line_len] = c;
            line_len += 1;
        } else {
            printf("ERROR: exceeded MAX_LINE_LENGTH %d", MAX_LINE_LENGTH);
            abort();
        }

        if (c != ' ' && c != '\t') {
            can_print = true;
        }
    }

    if (line_len > 0 && can_print) {
        line[line_len] = 0;
        printf("%s\n", line);
    }
}
