#include <stdio.h>

// returns the index of the first character in s1, that matches any character in s2. it returns -1 if no characters match
int any(char s1[], char s2[]) {
    int i, j;
    for(i = 0; s1[i] != 0; ++i) {
        for (j = 0; s2[j] != 0; ++j) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }

    return -1;
}

int main() {
    printf("%i\n", any("hello world", "eo"));
    printf("%i\n", any("hello world", "xampp"));
    printf("%i\n", any("hello world", "damsdam"));
    return 0;
}
