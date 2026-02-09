#include <stdint.h>
#include <stdio.h>

#define OUT 0
#define IN 1
#define MAX_WORD_LENGTH 11
#define HISTOGRAD_WIDTH 50

int main() {
    int c, state, current_length;
    int lengths[MAX_WORD_LENGTH];

    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        lengths[i] = 0;
    }

    state = OUT;
    current_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if (current_length > 0) {
                int index;
                if (current_length >= MAX_WORD_LENGTH) {
                    index = MAX_WORD_LENGTH - 1;
                } else {
                    index = current_length;
                }

                lengths[index] += 1;
                current_length = 0;
            }

        } else if (state == OUT) {
            state = IN;
        }
        if (state = IN) {
            current_length += 1;
        }
    }

    int max = 0;
    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        int length = lengths[i];
        if (length > max) {
            max = length;
        }
    }

    for (int i = 1; i < MAX_WORD_LENGTH; ++i) {
        int length = lengths[i];
        int bar = (int)(HISTOGRAD_WIDTH * (float)length/(float)max);

        if (i == MAX_WORD_LENGTH - 1) {
            printf("%3d+ ", i);
        } else if (i == 1 || i % 5 == 0) {
            printf("%3d  ", i);
        } else {
            printf("     ");
        }

        for (int j = 0; j < bar; ++j) {
            putchar('=');
        }

        putchar('\n');
    }

    putchar('\n');
}

