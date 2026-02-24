#include <stdio.h>

int strindex(char source[], char searchfor[]);

int main() {
    printf("%i\n", strindex("elfelfelf", "fel"));
    printf("%i\n", strindex("elfelfelf", "what"));
    return 0;
}

int strindex(char s[], char t[]) {
    int i, j, k;

    int result = -1;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {}

        if (k > 0 && t[k] == '\0') {
            result = i;
        }
    }

    return result;
}
