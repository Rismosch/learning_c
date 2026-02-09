#include <stdint.h>
#include <stdio.h>

int main() {
    int32_t c = getchar();
    while (c != EOF) {
        putchar(c);

        if (c != ' ') {
            c = getchar();
        } else {
            while (c == ' ') {
                c = getchar();
            }
        }
    }
}
