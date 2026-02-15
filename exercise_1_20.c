#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 1<<10
#define SPACES_IN_TAB 4

int my_getline(char s[], int lim);
void detab(char buf[], int len, int spaces);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        detab(line, len, SPACES_IN_TAB);
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

void detab(char buf[], int len, int spaces) {
    int i, j, k;

    // ensure enough space
    int required_len = 0;
    for (i = 0; i < len && buf[i] != 0; ++i) {
        if (buf[i] == '\t') {
            required_len += spaces;
        } else {
            required_len += 1;
        }
    }

    if (required_len > MAXLINE) {
        printf("ERROR: buf is not large enough");
        abort();
    }

    // detab
    for (i -= 1, j = required_len - 1; i >= 0; --i) {
        if (buf[i] == '\t') {
            for (k = 0; k < spaces; ++k) {
                buf[j - k] = ' ';
            }
            j -= spaces;
        } else {
            buf[j] = buf[i];
            j -= 1;
        }
    }
}
