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
} Operator;

Operator getop(char*, double*);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(int argc, char *argv[]) {
    Operator op;
    double lhs;
    double rhs;


    for(int i = 1; i < argc; ++i) {
        op = getop(argv[i], &rhs);

        switch(op) {
        case OPERATOR_NUMBER:
            push(rhs);
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

        case OPERATOR_UNKNOWN:
        default:
            printf("error: unknown command %s\n", argv[0]);
            break;
        }
    }

    printf("\t%.8g\n", pop());

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

/* getop: get next operator or numeric operand */
Operator getop(char *s, double *out_number) {
    int i = 0;

    while (s[i] == ' ' || s[i] == '\t') {
        i += 1;
    }

    if (!isdigit(s[i]) && s[i] != '.') {
        switch(s[i]) {
        case '+':   return OPERATOR_ADDITION;
        case '*':   return OPERATOR_MULTIPLICATION;
        case '-':   return OPERATOR_SUBTRACTION;
        case '/':   return OPERATOR_DIVISION;
        default:    return OPERATOR_UNKNOWN;
        }
    }

    *out_number = atof(&s[i]);
    return OPERATOR_NUMBER;
}

