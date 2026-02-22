#include <stdio.h>

void lower(char s[]);

int main() {
    char s[] = "Hello, World!";
    lower(s);
    printf("%s\n", s);
    return 0;
}

void lower(char s[]) {
    for (int i = 0; s[i] != 0; ++i) {
        bool is_upper = s[i] >= 'A' && s[i] <= 'Z';
        s[i] = is_upper ? s[i] - 'A' + 'a' : s[i];
    }
}
