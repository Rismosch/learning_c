#include <stdio.h>

int htoi(char s[]);

int main() {
    printf("%x\n", htoi("0000"));
    printf("%x\n", htoi("1234"));
    printf("%x\n", htoi("abcdef"));
    printf("%X\n", htoi("BEEF"));

    return 0;
}

int htoi(char s[]) {
    int i, n;

    i = 0;
    n = 0;
    while(true) {
        char offset;
        if (s[i] >= '0' && s[i] <= '9') {
            offset = '0';
        } else if(s[i] >= 'a' && s[i] <= 'f') {
            offset = 'a' - 10;
        } else if(s[i] >= 'A' && s[i] <= 'F') {
            offset = 'A' - 10;
        } else {
            break;
        }

        n = 16 * n + (s[i] - offset);
        i += 1;
    }

    return n;
}
