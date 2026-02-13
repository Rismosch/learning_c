#include "stdlib.h"
#include "stdio.h"

#define BUF_LEN 1<<10

void reverse(char in[], char out[]);

int main() {
    int c;
    char buf[BUF_LEN + 1];
    char bufr[BUF_LEN + 1];
    int len = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            buf[len] = 0;
            reverse(buf, bufr);
            printf("%s\n", bufr);
            len = 0;
        } else {
            buf[len] = c;
            len += 1;
        }
    }

    if (len > 0) {
        buf[len] = 0;
        reverse(buf, bufr);
        printf("%s\n", bufr);
    }

    return 0;
}

void reverse(char in[], char out[]) {
    int i;

    for (i = 0;; ++i) {
        if (in[i] == 0) {
            out[i] = 0;
            i -= 1;
            break;
        }
    }

    for (int j = 0; i >= 0; --i, ++j) {
        out[j] = in[i];
    }
}
