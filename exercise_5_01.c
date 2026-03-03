#include <ctype.h>
#include <stdio.h>

int getint(int *pn);

int main() {
    int n;
    while(true) {
        int status = getint(&n);
        if (status == EOF) {
            break;
        }

        if (status) {
            printf("%i\n", n);
        }

    }

    return 0;
}

int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch())) {} // skip shitespace

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        char prev = c;
        c = getch();

        if (c == EOF) {
            return EOF;
        }

        if (!isdigit(c)) {
            ungetch(prev);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }

    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch
int bufp;           // next free position in buf

/* get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
