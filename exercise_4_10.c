// pass `-lm` to gcc when compiling this

// +------+
// | main |
// +------+

#include <math.h>
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
    OPERATOR_LOG,               // l
    OPERATOR_DUPLICATE,         // d
    OPERATOR_SWAP,              // w
    OPERATOR_CLEAR,             // c
    OPERATOR_SIN,               // s
    OPERATOR_EXP,               // e
    OPERATOR_POW,               // ^
    OPERATOR_VARIABLE_DEFINE,   // v<A-Z>
    OPERATOR_VARIABLE_DEREF,    // <A-Z>
    OPERATOR_NEWLINE,
    OPERATOR_EOF,
} Operator;

Operator getop(char []);
void push(double);
double pop(void);
double peek(int);

/* reverse Polish calculator */
int main() {
    Operator op;
    double lhs;
    double rhs;
    char s[MAXOP];
    double variables[26] = {0};
    char v;

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

        case OPERATOR_LOG:
            rhs = peek(0);
            if (!isnan(rhs)) {
                printf("\t%.8g\n", rhs);
            } else {
                printf("error: stack is empty\n");
            }
            break;

        case OPERATOR_DUPLICATE:
            rhs = peek(0);
            if (!isnan(rhs)) {
                push(rhs);
            } else {
                printf("error: stack is empty\n");
            }
            break;

        case OPERATOR_SWAP:
            rhs = peek(0);
            lhs = peek(1);
            if (isnan(lhs) || isnan(rhs)) {
                printf("error: not enough elements on the stack\n");
                break;
            }

            pop();
            pop();
            push(rhs);
            push(lhs);
            break;

        case OPERATOR_CLEAR:
            while (!isnan(peek(0))) {
                pop();
            }
            break;

        case OPERATOR_SIN:
            rhs = pop();
            push(sin(rhs));
            break;

        case OPERATOR_EXP:
            rhs = pop();
            push(exp(rhs));
            break;

        case OPERATOR_POW:
            rhs = pop();
            lhs = pop();
            push(pow(lhs, rhs));
            break;

        case OPERATOR_VARIABLE_DEFINE:
            rhs = pop();
            v = s[0] - 'A';
            variables[v] = rhs;
            break;

        case OPERATOR_VARIABLE_DEREF:
            v = s[0] - 'A';
            rhs = variables[v];
            push(rhs);
            break;

        case OPERATOR_NEWLINE:
            printf("\t%.8g\n", pop());
            break;

        case OPERATOR_UNKNOWN:
        default:
            printf("error: unknown command '%s' (%i)\n", s, s[0]);
            return -1;
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
        return NAN;
    }
}

/* peek: return the top value from the stack without popping */
double peek(int offset) {
    int i = sp - 1 - offset;
    if (i < 0 || i >= sp) {
        return NAN;
    } else {
        return val[i];
    }
}

// +-------+
// | input |
// +-------+

#include <ctype.h>

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        i += 1;
    }

    s[i] = 0;
    return i;
}

#define MAXLINE 1<<10

char line[MAXLINE] = {0};
int line_len = 0;
int line_index = 0;

int peakch() {
    char c = line[line_index];
    return c;
}

void takech() {
    line_index += 1;

    if (line_index >= line_len) {
        line_index = 0;
        line_len = my_getline(line, MAXLINE);
    }
}

double variables[26] = {0};

/* getop: get next operator or numeric operand */
Operator getop(char s[]) {
    int i, c;
    takech();

    // clear whitespace
    while ((s[0] = c = peakch()) == ' ' || c == '\t') {
        takech();
    }

    s[1] = '\0';

    // handle variable
    if (c >= 'A' && c <= 'Z') {
        return OPERATOR_VARIABLE_DEREF;
    }

    if (c == 'v') {
        takech();
        c = peakch();
        if (c >= 'A' && c <= 'Z') {
            s[0] = c;
            return OPERATOR_VARIABLE_DEFINE;
        } else {
            s[0] = 'v';
            s[1] = c;
            s[2] = 0;
            return OPERATOR_UNKNOWN;
        }
    }

    // handle operators
    if (!isdigit(c) && c != '.') {
        switch(c) {
        case '+': return    OPERATOR_ADDITION;
        case '*': return    OPERATOR_MULTIPLICATION;
        case '-': return    OPERATOR_SUBTRACTION;
        case '/': return    OPERATOR_DIVISION;
        case '%': return    OPERATOR_MODULUS;
        case 'l': return    OPERATOR_LOG;
        case 'd': return    OPERATOR_DUPLICATE;
        case 'w': return    OPERATOR_SWAP;
        case 'c': return    OPERATOR_CLEAR;
        case 's': return    OPERATOR_SIN;
        case 'e': return    OPERATOR_EXP;
        case '^': return    OPERATOR_POW;
        case '\n': return   OPERATOR_NEWLINE;
        case 0: return      OPERATOR_EOF;
        default: return     OPERATOR_UNKNOWN;
        }
    }

    i = 0;

    // collect integer part
    if (isdigit(c)) {
        takech();
        while (isdigit(s[++i] = c = peakch())) {
            takech();
        }
    }

    // collect fraction part
    if (c == '.') {
        takech();
        while(isdigit(s[++i] = c = peakch())) {
            takech();
        }
    }

    s[i] = '\0';
    return OPERATOR_NUMBER;
}

