#include <stdio.h>

#define BUFLEN 1<<10

void strncpy(char* s, char* t, int n);
void strcat(char* s, char* t, int n);
int strcmp(char* s, char* t, int n);

int main() {
    char buf[BUFLEN];
    strncpy(buf, "hello world", 5);
    printf("%s\n", buf);
    strcat(buf, " world", 3);
    printf("%s\n", buf);
    printf("%i\n", strcmp(buf, "hello woman", 8));
    printf("%i\n", strcmp(buf, "hello man", 8));
}

void strncpy(char* s, char* t, int n) {
    for (int i = 0; i < n; ++i) {
        if (*s++ = *t++) {
            continue;
        } else {
            return;
        }
    }

    *s = 0;
}

void strcat(char* s, char* t, int n) {
    while (*s) {
        s += 1;
    }

    for (int i = 0; i < n; ++i) {
        if (*s++ = *t++) {
            continue;
        } else {
            return;
        }
    }

    *s = 0;
}

int strcmp(char* s, char* t, int n) {
    for (int i = 0; i < n; ++i, ++s, ++t) {
        if (*s == *t) {
            continue;
        }

        if (*s == 0) {
            return 0;
        }

        return *s - *t;
    }

    return 0;
}
