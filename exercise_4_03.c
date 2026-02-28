// includes solutions for 4.3 to 4.10

// +------+
// | main |
// +------+

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100

typedef enum {
    OPERATOR_UNKNOWN,
    OPERATOR_NUMBER,
    OPERATOR_ADDITION,          // +
    OPERATOR_MULTIPLICATION,    // *
    OPERATOR_SUBTRACTION,       // -
    OPERATOR_DIVISION,          // /
    OPERATOR_MODULUS,           // %
    OPERATOR_NEWLINE,
    OPERATOR_EOF,
} Operator;

Operator getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main() {
    Operator op;
    double lhs;
    double rhs;
    char s[MAXOP];

    while((op = getop(s)) != OPERATOR_EOF) {
        switch(op) {
        case OPERATOR_NUMBER:
            push(atof(s));
            break;

        case OPERATOR_ADDITION:
            rhs = pop();
            lhs = pop();
            push(lhs + rhs);
            break;

        case OPERATOR_MULTIPLICATION:
            rhs = pop();
            lhs = pop();
            push(lhs * rhs);
            break;

        case OPERATOR_SUBTRACTION:
            rhs = pop();
            lhs = pop();
            push(lhs - rhs);
            break;

        case OPERATOR_DIVISION:
            rhs = pop();
            if (rhs != 0.0) {
                lhs = pop();
                push(lhs / rhs);
            } else {
                printf("error: zero divisor\n");
            }
            break;

        case OPERATOR_MODULUS:
            rhs = pop();
            if (rhs != 0.0) {
                lhs = pop();
                push((int)lhs % (int)rhs);
            } else {
                printf("error: non positive divisor\n");
            }
            break;

        case OPERATOR_NEWLINE:
            printf("\t%.8g\n", pop());
            break;

        case OPERATOR_UNKNOWN:
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}

// +-------+
// | stack |
// +-------+

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return the top value from stack */
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// +-------+
// | input |
// +-------+

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
Operator getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {}

    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        switch(c) {
        case '+': return    OPERATOR_ADDITION;
        case '*': return    OPERATOR_MULTIPLICATION;
        case '-': return    OPERATOR_SUBTRACTION;
        case '/': return    OPERATOR_DIVISION;
        case '%': return    OPERATOR_MODULUS;
        case '\n': return   OPERATOR_NEWLINE;
        case EOF:return     OPERATOR_EOF;
        default: return     OPERATOR_UNKNOWN;
        }
        return c; // not a number
    }

    i = 0;

    // collect integer part
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {}
    }

    // collect fraction part
    if (c == '.') {
        while(isdigit(s[++i] = c = getch())) {}
    }

    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return OPERATOR_NUMBER;
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
