#include "stdio.h"

#define THRESHOLD 80

int main() {
    int buf[THRESHOLD];
    bool print = false;

    int c = 0;
    int buf_len = 0;
    while ((c = getchar()) != EOF) {
        if (print) {
            //putchar(c);
        }

        if (c == '\n') {
            buf_len = 0;
            if (print) {
                putchar('\n');
                print = false;
            }
        } else {
            //printf("print! \"%c\"\n", c);

            if (buf_len < THRESHOLD) {
                buf[buf_len] = c;
                buf_len += 1;
            } else if (!print) {
                for(int i = 0; i < THRESHOLD; ++i) {
                    //printf("%2d \"%c\"\n", i, buf[i]);
                    putchar(buf[i]);
                }

                //printf("------\n");
                putchar(c);
                print = true;
            } else {
                //printf("print! \"%c\"\n", c);
                putchar(c);
            }
        }
    }

}
