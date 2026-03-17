#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    /* ... */
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 },
};

#define MAXWORD 100

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count c keywords */
int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) != 0) {
                keytab[n].count++;
            }
        }
    }

    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf(
                "%4d %s\n",
                keytab[n].count,
                keytab[n].word
            );
        }
    }

    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

/* getword */
int getword(char *word, int lim) {
    int c, prev_c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {}

    if (c != EOF) {
        *w++ = c;
    }

    if (c == '"') {
        // string literal
        *w++ = c;
        while (true) {
            prev_c = c;
            c = getch();

            if (c == EOF) {
                *w = 0;
                return c;
            }

            *w++ = c;

            if (c == '"' && prev_c != '\\') {
                *w = 0;
                return c;
            }
        }
    } else if (c == '\'') {
        // char literal
        *w++ = c;

        while (true) {
            prev_c = c;
            c = getch();

            if (c == EOF) {
                *w = 0;
                return c;
            }

            *w++ = c;

            if (c == '\'' && prev_c != '\\') {
                *w = 0;
                return c;
            }
        }
    } else if (c == '/') {
        // comment
        *w++ = c;

        prev_c = c;
        c = getch();

        switch (c) {
        case '/':
            *w++ = c;
            while ((c = getch()) != EOF) {
                *w++ = c;
                if (c == '\n') {
                    break;
                }
            }

            break;

        case '*':
            *w++ = c;
            while (true) {
                prev_c = c;
                c = getch();

                if (c == EOF) {
                    break;
                }

                *w++ = c;

                if (prev_c == '*' && c == '/') {
                    break;
                }
            }

            break;

        default:
            *w = 0;
            break;
        }

        return c;

    } else if (c == '#') {
        // preprocessor directive
        *w++ = c;
        while (true) {
            prev_c = c;
            c = getch();

            if (c == EOF) {
                *w = 0;
                return c;
            }

            *w++ = c;

            if (c == '\n' && prev_c != '\\') {
                *w = 0;
                return c;
            }
        }
    } else if (!isalpha(c) && c != '_') {
        *w = 0;
        return c;
    } else {
        for (; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && c != '_') {
                ungetch(*w);
                break;
            }
        }

        *w = 0;
        return word[0];
    }
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void) {       /* get a (possible pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {   /* push character back on input */
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
