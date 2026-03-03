#include <limits.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 1<<10

/* itoa: convert n to characters in s*/
void itoa(int n, char s[], int min_width);

int main() {
    char buf[BUF_LEN];
    itoa(12345, buf, 2);
    printf("%s\n", buf);
    itoa(67890, buf, 10);
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

void itoa(int n, char s[], int min_width) {
    int i;
    long sign;

    long l = n; 
    if ((sign = l) < 0) {
        l = -l;
    }

    i = 0;
    do {
        s[i++] = l % 10 + '0';
    } while ((l /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    while (i < min_width) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}
