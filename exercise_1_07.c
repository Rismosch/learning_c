#include <stdint.h>
#include <stdio.h>

int main() {
    while (true) {
        int32_t c = getchar();

        bool is_eof = c == EOF;
        printf("%c is EOF: %b\n", c, is_eof);
        if (is_eof) {
            break;
        }
    }
}

