#include <stdlib.h>
#include <stdio.h>

#define BUF_LEN 1<<12
#define MAX_LINE 20

int main() {
    char c = 0;
    char buf[BUF_LEN];
    buf[0] = 0;
    int buf_len = 0;
    int i = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            i = 0;
        } else if (i < MAX_LINE) {
            i += 1;
        } else {
            putchar('\n');
            i = buf_len;
        }

        if (c == ' ' || c == '\t' || c == '\n') {
            if (buf_len > 0) {
                printf("%s", buf);
                buf[0] = 0;
                buf_len = 0;
            }

            putchar(c);
            continue;
        }

        buf[buf_len] = c;
        buf[buf_len + 1] = 0;
        buf_len += 1;

        if (buf_len >= MAX_LINE) {
            printf("%s", buf);
            buf[0]= 0;
            buf_len = 0;
        }
    }

    return 0;
}

