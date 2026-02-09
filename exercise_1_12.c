#include <stdint.h>
#include <stdio.h>

#define OUT 1
#define IN 0

int main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') {
            ++nl;
        } if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++nw;
            putchar('\n');
        }
        if (state == IN) {
            putchar(c);
        }
    }

    putchar('\n');
}
