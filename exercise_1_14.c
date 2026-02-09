#include <stdint.h>
#include <stdio.h>

#define OUT 0
#define IN 1
#define HISTOGRAD_WIDTH 50
#define MIN_CHAR ' '
#define MAX_CHAR '~'

int main() {
    int c, state;
    int l = MAX_CHAR - MIN_CHAR + 1;
    int frequencies[l];

    for (int i = 0; i < l; ++i) {
        frequencies[i] = 0;
    }

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c >= MIN_CHAR && c <= MAX_CHAR) {
            frequencies[c - MIN_CHAR] += 1;
        } else {
            frequencies[l - 1] += 1;
        }
    }

    int max = 0;
    for (int i = 0; i < l; ++i) {
        int frequency = frequencies[i];
        if (frequency > max) {
            max = frequency;
        }
    }

    for (int i = 0; i < l; ++i) {
        int frequency = frequencies[i];
        int bar = (int)(HISTOGRAD_WIDTH * (float)frequency/(float)max);

        if (i != l - 1) {
            printf("'%c' ", i + MIN_CHAR);
        } else {
            printf("??? ");
        }

        for (int j = 0; j < bar; ++j) {
            putchar('=');
        }

        putchar('\n');
    }

    putchar('\n');
}

