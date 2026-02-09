#include <stdint.h>
#include <stdio.h>

int main() {
    int32_t blanks = 0;
    int32_t tabs = 0;
    int32_t newlines = 0;

    int32_t c;
    while ((c = getchar()) != EOF) {
        switch(c) {
            case ' ':
                blanks += 1;
                break;
            case '\t':
                tabs += 1;
                break;
            case '\n':
                newlines += 1;
                break;
        }
    }

    int32_t sum = blanks + tabs + newlines;
    printf("%d %d %d %d", sum, blanks, tabs, newlines);
}
