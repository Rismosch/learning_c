#include <ctype.h>
#include <stdio.h>

/* atof: convert string s to double */
double atof(char s[]);

int main(void) {
    printf("%f\n", atof("123.45"));
    printf("%f\n", atof("123.45e6"));
    printf("%f\n", atof("123.45e-6"));
    return 0;
}

double atof(char s[]) {
    double val, power;
    int i, sign, sign_exponent, exponent;

    // skip whitespace
    for (i = 0; isspace(s[i]); ++i) {}

    // read sign
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i += 1;
    }

    // read numbers before decimal
    for (val = 0.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }

    // decimal
    if (s[i] == '.') {
        i += 1;
    }

    // read numbers after decimal
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    // detect exponent
    if (s[i] == 'e' || s[i] == 'E') {
        i += 1;
    }

    // read exponent sign
    sign_exponent = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i += 1;
    }

    // read exponent
    for (exponent = 0; isdigit(s[i]); ++i) {
        exponent = 10.0 * exponent + (s[i] - '0');
    }

    // apply exponent
    for (i = 0; i < exponent; ++i) {
        if (sign_exponent > 0) {
            power /= 10.0;
        } else {
            power *= 10.0;
        }
    }

    return sign * val / power;
}

