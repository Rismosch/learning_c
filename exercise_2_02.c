#include <stdio.h>

#define BUF_LEN 1 << 10

int my_getline(char line[], int maxline);

int main() {
    char buf[BUF_LEN];
    while (my_getline(buf, BUF_LEN) > 0) {
        printf("%s", buf);
    }

    return 0;
}

int my_getline(char s[], int lim) {
    int c, i;

    //for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
    //    s[i] = c;
    //}

    i = 0;
    while (true) {
        if (i >= lim -1) {
            break;
        }

        if ((c = getchar()) == EOF) {
            break;
        }

        if (c == '\n') {
            break;
        }

        s[i] = c;
        i += 1;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
