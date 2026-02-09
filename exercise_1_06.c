#include <stdint.h>
#include <stdio.h>

int main() {
    int32_t c = getchar();
    while (true) {
        bool is_eof = c == EOF;
        printf(" is EOF: %b\n", is_eof);
        if (is_eof) {
            break;
        }

        putchar(c);
        c = getchar();
    }
}

