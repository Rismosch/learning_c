#include <ctype.h>
#include <stdio.h>

// returns int, because thats the input character
int getfloat(float *pn);

int main() {
    int c;
    float f;
    while(true) {
        c = getfloat(&f);
        if (c == EOF) {
            break;
        }

        if (c) {
            printf("%f\n", f);
        }

    }

    return 0;
}

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
    float power;
    int c, sign, sign_exponent, exponent;

    while (isspace(c = getch())) {} // skip shitespace

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    // read sign
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

    // read numbers before decimal
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    // decimal
    if (c == '.') {
        c = getch();
    }

    // read numbers after decimal
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }

    // detect exponent
    if (c == 'e' || c == 'E') {
        c = getch();
    }

    // read exponent sign
    sign_exponent = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }

    // read exponent
    for (exponent = 0; isdigit(c); c = getch()) {
        exponent = 10.0 * exponent + (c - '0');
    }

    // apply exponent
    for (int i = 0; i < exponent; ++i) {
        if (sign_exponent > 0) {
            power /= 10.0;
        } else {
            power *= 10.0;
        }
    }
    // cleanup, compute and return
    if (c != EOF) {
        ungetch(c);
    }

    *pn = sign * *pn / power;

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
