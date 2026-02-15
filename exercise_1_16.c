#include <stdio.h>
#define MAXLINE 20

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
    int len, max, max_line_num;
    char line[MAXLINE];
    char longest[MAXLINE];

    longest[0] = 0;

    max = 0;
    max_line_num = 0;
    for (int i = 1;(len = my_getline(line, MAXLINE)) > 0; ++i) {
        if (len > max) {
            max = len;
            max_line_num = i;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("length: %d, line: %d, content: \"%s\"\n", max, max_line_num, longest);
    }

    return 0;
}

/* my_getline: read a line into s, return length */
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

/* copy: copy `from` into `to`; assume to is beg enough */
void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != 0) {
        ++i;
    }
}

