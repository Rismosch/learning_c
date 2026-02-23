#include <limits.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 1<<10

/* itoa: convert n to characters in s using base b */
void itob(int n, char s[], int b);

int main() {
    char buf[BUF_LEN];
    itob(0xBEEF, buf, 2);
    printf("%s\n", buf);
    itob(0xBEEF, buf, 8);
    printf("%s\n", buf);
    itob(0xBEEF, buf, 16);
    printf("%s\n", buf);
}

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b) {
    int i;
    long sign;

    long l = n; 
    if ((sign = l) < 0) {
        l = -l;
    }

    i = 0;
    do {
        int digit = l % b;
        if (digit < 10) {
            s[i++] = digit + '0';
        } else {
            s[i++] = digit - 10 + 'a';
        }
    } while ((l /= b) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}
