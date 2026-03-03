#include <limits.h>
#include <stdio.h>
#include <string.h>

/* reverse: reverses a string */
void reverse(char[]);

int main() {
    char buf[] = "hello world";
    reverse(buf);
    printf("%s\n", buf);

    return 0;
}

void reverse_internal(char s[], int left, int right) {
    if (left >= right) {
        return;
    }

    char c = s[left];
    s[left] = s[right];
    s[right] = c;

    reverse_internal(s, left + 1, right - 1);
}

void reverse(char s[]) {
    int i = 0;
    int j = strlen(s) - 1;
    reverse_internal(s, i, j);
}

