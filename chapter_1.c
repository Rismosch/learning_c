#include <stdint.h>
#include <stdio.h>

#define LOWER   0
#define UPPER 300
#define STEP   20

#define IN  1
#define OUT 0

#define MAX_WORD_LENGTH

void exercise_1_1() {
    printf("hello, world\n");
}

void exercise_1_2() {
    // compiler error!
    //printf("\c is an invalid character\n")
}

void exercise_1_3() {
    float fahr, celsius;

    printf("fahrenheit celsius\n");

    fahr = LOWER;
    while (fahr <= UPPER) {
        celsius = (5.0f / 9.0f) * (fahr - 32.0f);
        printf("%10.0f %7.1f\n", fahr, celsius);
        fahr += STEP;
    }
}

void exercise_1_4() {
    float fahr, celsius;

    printf("celsius fahrenheit\n");

    celsius = LOWER;
    while (celsius <= UPPER) {
        fahr = celsius * (9.0f / 5.0f) + 32.0f;
        printf("%7.0f %10.1f\n", celsius, fahr);
        celsius += STEP;
    }
}

void exercise_1_5() {
    printf("fahrenheit celsius\n");
    for (float f = UPPER; f >= LOWER; f -= STEP) {
        float c = (5.0f / 9.0f) * (f - 32.0f);
        printf("%10.0f %7.1f\n", f, c);
    }
}

void exercise_1_6() {
    int32_t c = getchar();
    while (true) {
        bool is_eof = c == EOF;
        printf(" is EOF: %b\n", is_eof);
        if (is_eof) {
            break;
        }

        putchar(c);
        c = getchar();
    }
}

void exercise_1_7() {
    while (true) {
        int32_t c = getchar();

        bool is_eof = c == EOF;
        printf("%c is EOF: %b\n", c, is_eof);
        if (is_eof) {
            break;
        }
    }
}

void exercise_1_8() {
    int32_t blanks = 0;
    int32_t tabs = 0;
    int32_t newlines = 0;

    int32_t c;
    while ((c = getchar()) != EOF) {
        switch(c) {
            case ' ':
                blanks += 1;
                break;
            case '\t':
                tabs += 1;
                break;
            case '\n':
                newlines += 1;
                break;
        }
    }

    int32_t sum = blanks + tabs + newlines;
    printf("%d %d %d %d", sum, blanks, tabs, newlines);
}

void exercise_1_9() {
    int32_t c = getchar();
    while (c != EOF) {
        putchar(c);

        if (c != ' ') {
            c = getchar();
        } else {
            while (c == ' ') {
                c = getchar();
            }
        }
    }
}

void exercise_1_10() {
    int32_t c;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '\t':
                putchar('\\');
                putchar('t');
                break;
            case '\b':
                putchar('\\');
                putchar('b');
                break;
            case '\\':
                putchar('\\');
                putchar('\\');
                break;
            default:
                putchar(c);
                break;
        }
    }
}

void exercise_1_11() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }

    printf("%d %d %d\n", nl, nw, nc);
}

void exercise_1_12() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') {
            ++nl;
        } if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++nw;
            putchar('\n');
        }
        if (state == IN) {
            putchar(c);
        }
    }

    putchar('\n');
}

void exercise_1_13() {
    int c, state, current_length;
    int lengths[MAX_WORD_LENGTH];

    for (int i = 0; i < MAX_WORD_LENGTH; ++i) {
        lengths[i] = 0;
    }

    state = OUT;
    current_length = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') {
            ++nl;
        } if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if (current_length > 0) {
                todo
            }

            current_length = 0;
        } else if (state == OUT) {
            state = IN;
            ++nw;
            putchar('\n');
        }
        if (state == IN) {
            putchar(c);
        }
    }

    putchar('\n');


}

int main()
{
    exercise_1_13();
}
