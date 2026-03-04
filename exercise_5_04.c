#include <stdio.h>

#define BUFLEN 1<<10

/* strend: returns 1 if the string t occurs at the end of the string s, and zero otherwise */
int strend(char* s, char* t) {
    int len_s = 0;
    int len_t = 0;

    // find end of s
    while(*s) {
        s += 1;
        len_s += 1;
    }

    s -= 1;

    // find end of t
    while(*t) {
        t += 1;
        len_t += 1;
    }

    t -= 1;

    // compare
    if (len_s < len_t) {
        return 0;
    }

    for (int i = 0; i < len_t; ++i) {
        if (*(s - i) != *(t - i)) {
            return 0;
        }
    }

    return 1;
}

int main() {
    printf("%i\n", strend("h", "world"));
    printf("%i\n", strend("hello", "world"));
    printf("%i\n", strend("hello world", "world"));
    return 0;
}
