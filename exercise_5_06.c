#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define BUFLEN 1<<10
#define NUMBER '0'

//getline (Chapter 1 and 4);
int my_getline(char* s, int lim);

//atoi, itoa, and their variants (chapter 2, 3, 4);
int atoi(char* s);
void itoa(int n, char* s);

//reverse (chapter 3);
void reverse(char* s);

//strindex and getop (chapter 4)
int strindex(char* s, char* t);
int getop(char* s);

int main() {
    //// test getline
    //char s[BUFLEN];
    //while (my_getline(s, BUFLEN)) {
    //    printf("%s", s);
    //}
    
    //// test atoi
    //printf("%i\n", atoi("42"));
    //printf("%i\n", atoi("0"));
    //printf("%i\n", atoi("-13"));
    
    //// test itoa
    //char s[BUFLEN];
    //itoa(42, s);
    //printf("%s\n", s);
    //itoa(0, s);
    //printf("%s\n", s);
    //itoa(-13, s);
    //printf("%s\n", s);
    //itoa(INT_MIN, s);
    //printf("%s\n", s);
    //itoa(INT_MAX, s);
    //printf("%s\n", s);

    //// test reverse
    //char s[BUFLEN] = "hello world";
    //reverse(s);
    //printf("%s\n", s);

    //// test strindex
    //printf("%i\n", strindex("elfelfelf", "elf"));
    //printf("%i\n", strindex("elfelfelf", "fel"));
    //printf("%i\n", strindex("elfelfelf", "what"));

    //// test getop
    int type;
    char s[BUFLEN];
    while ((type = getop(s)) != EOF) {
        if (type == NUMBER) {
            printf("number: %s\n", s);
        } else {
            printf("type:   '%c' (%i)\n", type, type);
        }
    }

    return 0;
}

int my_getline(char* s, int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i, ++s) {
        *s = c;
    }

    if (c == '\n') {
        *s = c;
        s += 1;
        i += 1;
    }

    *s = 0;
    return i;
}

int atoi(char* s) {
    int n, sign;

    // skip white space
    while (isspace(*s)) {
        s += 1;
    }

    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-') {
        s += 1;
    }

    for (n = 0; isdigit(*s); ++s) {
        n = 10 * n + (*s - '0');
    }

    return sign * n;
}

void itoa(int n, char* s) {
    char* start = s;

    long sign;

    long l = n;
    if ((sign = l) < 0) {
        l = -l;
    }

    do {
        *s++ = l % 10 + '0';
    } while ((l /= 10) > 0);

    if (sign < 0) {
        *s++ = '-';
    }

    *s = '\0';
    reverse(start);
}

void reverse(char* s) {
    char c;

    char* left = s;
    char* right = s + strlen(s) - 1;

    for (; left < right; ++left, --right) {
        c = *left;
        *left = *right;
        *right = c;
    }
}

int strindex(char* s, char* t) {
    char* start_s = s;
    char* start_t = t;
    char* current_s;

    for (; *s != '\0'; s = current_s + 1) {
        current_s = s;

        for (t = start_t; *t != '0' && *s == *t; ++s, ++t) {}

        if (t > start_t && *t == '\0') {
            return current_s - start_s;
        }
    }

    return -1;
}

int getch(void);
void ungetch(int);

int getop(char* s) {
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t') {}

    *(s + 1) = 0;
    if (!isdigit(c) && c != '.') {
        return c; // not a number
    }

    // collect ingeter part
    if (isdigit(c)) {
        while (isdigit(*(++s) = c = getch())) {}
    }

    // collect fraction part
    if (c == '.') {
        while (isdigit(*(++s) = c = getch())) {}
    }

    *s = 0;
    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
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
