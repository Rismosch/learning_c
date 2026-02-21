#include <stdio.h>

// deletes all characters present in s2 from s1
void squeeze(char s1[], char s2[]);

int main() {
    char buf[] = "hello world";
    squeeze(buf, "eo");
    printf("%s\n", buf);

    return 0;
}

void squeeze(char s1[], char s2[]) {
    int i, j, k;

    for (i = 0, j = 0; s1[i] != 0; ++i) {
        bool characters_match = false;

        for(k = 0; s2[k] != 0; ++k) {
            if (s1[i] == s2[k]) {
                characters_match = true;
                break;
            }
        }

        if (!characters_match) {
            s1[j++] = s1[i];
        }
    }

    s1[j] = 0;
}
