#include <limits.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 1<<10

/* itoa: convert n to characters in s */
int itoa(int n, char s[]);

int main() {
    char buf[BUF_LEN];

    itoa(42, buf);
    printf("%s\n", buf);
    itoa(10, buf);
    printf("%s\n", buf);
    itoa(123456789, buf);
    printf("%s\n", buf);
    itoa(0, buf);
    printf("%s\n", buf);
    itoa(-13, buf);
    printf("%s\n", buf);
    itoa(INT_MIN, buf);
    printf("%s\n", buf);
    itoa(INT_MAX, buf);
    printf("%s\n", buf);
}

int itoa(int n, char s[]) {
    long sign = 1;
    long l = n; 
    if (l < 0) {
        sign = -1;
        l = -l;
    }

    long modulus = l / 10 * sign;
    long reminder = l % 10;

    if (modulus == 0) {
        if (sign < 0) {
            s[0] = '-';
            s[1] = reminder + '0';
            s[2] = 0;
            return 2;
        } else {
            s[0] = reminder + '0';
            s[1] = 0;
            return 1;
        }
    }

    int i = itoa(modulus, s);
    s[i] = reminder + '0';
    s[i + 1] = 0;
    return i + 1;
}
