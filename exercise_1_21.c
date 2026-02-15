#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 1<<10
#define SPACES_IN_TAB 4

int my_getline(char s[], int lim);
void entab(char buf[], int len, int spaces);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        entab(line, len, SPACES_IN_TAB);
        printf("%s", line);
    }

    return 0;
}

int my_getline(char s[], int lim) {
    int c, i;

    s[0] = 0;

    i = 0;
    while ((c = getchar()) != EOF) {
        if (i < (lim - 1)) {
            s[i] = c;
            s[i + 1] = 0;
        }

        i += 1;

        if (c == '\n') {
            break;
        }
    }

    return i;
}

void entab(char buf[], int len, int spaces) {
    int i, j, k;

    for (i = 0, j = 0; i < len; ++j) {
        if (buf[i] == 0) {
            break;
        }

        if (buf[i] != ' ') {
            buf[j] = buf[i];
            i += 1;
            continue;
        }

        bool has_enough_spaces = true;
        for (k = 0; k < spaces; ++k) {
            if (buf[i + k] != ' ') {
                has_enough_spaces = false;
                break;
            }
        }

        if (has_enough_spaces) {
            buf[j] = '\t';
            i += spaces;
        } else {
            buf[j] = buf[i];
            i += 1;
        }
    }

    if (j < i) {
        buf[j] = 0;
    }
}
