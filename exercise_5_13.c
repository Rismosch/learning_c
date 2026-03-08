#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1<<10
#define DEFAULT_TAIL 10

int my_getline(char s[], int lim);

void print_help() {
    printf("usage:\n");
    printf("    ./a.out [-n <number of lines>]\n");
}

int main(int argc, char *argv[]) {
    // parse cli
    int tail;

    if (argc == 1) {
        tail = DEFAULT_TAIL;
    } else if (argc == 3) {
        if (strcmp(argv[1], "-n") != 0) {
            print_help();
            return -1;
        }
        tail = atoi(argv[2]);
    } else {
        print_help();
        return -1;
    }

    // run tail
    int len;
    char line[MAXLINE];
    char **lines = (char**)malloc(tail * sizeof(char*));
    int lines_len = 0;

    while ((len = my_getline(line, MAXLINE)) > 0) {
        if (lines_len == tail) {
            char *s = lines[0];
            free(s);
            for (int i = 1; i < tail; ++i) {
                lines[i - 1] = lines[i];
            }

            s = (char*)malloc((len + 1) * sizeof(char));
            strcpy(s, line);
            lines[tail - 1] = s;
        } else {
            char *s = (char*)malloc((len + 1) * sizeof(char));
            strcpy(s, line);
            lines[lines_len] = s;
            lines_len += 1;
        }
    }

    for (int i = 0; i < lines_len; ++i) {
        printf("%s", lines[i]);
    }

    return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = 0;
    return i;
}
