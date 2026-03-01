#include <stdio.h>
#include <string.h>

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

/* push entire string back on input */
void ungets(char s[]) {
    for (int i = strlen(s) - 1; i >= 0; --i) {
        ungetch(s[i]);
    }
}

int main() {
    ungets("hello world\n");

    int c;
    while((c = getch()) != EOF) {
        printf("%3i: '%c'\n", c, c);
    }
}

