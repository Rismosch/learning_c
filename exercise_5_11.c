#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1<<10
#define DEFAULT_SPACES_IN_TAB 4

typedef enum {
    OPERATION_UNKNOWN,
    OPERATION_ENTAB,
    OPERATION_DETAB,
} Operation;

int my_getline(char s[], int lim);
void entab(char buf[], int len, int spaces);
void detab(char buf[], int len, int spaces);

void print_help() {
    printf("usage:\n");
    printf("    ./a.out <entab/detab> [number of spaces in tab (default 4)]\n");
}

Operation get_operation(char* s) {
    if (strcmp(s, "entab") == 0) {
        return OPERATION_ENTAB;
    } else if (strcmp(s, "detab") == 0) {
        return OPERATION_DETAB;
    } else {
        return OPERATION_UNKNOWN;
    }
}


int main(int argc, char *argv[]) {
    // parse cli
    Operation operation;
    int spaces_in_tab;

    if (argc == 2) {
        operation = get_operation(argv[1]);
        spaces_in_tab = DEFAULT_SPACES_IN_TAB;
    } else if (argc == 3) {
        operation = get_operation(argv[1]);
        spaces_in_tab = atoi(argv[2]);
    } else {
        print_help();
        return -1;
    }

    // run commans
    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        switch(operation) {
        case OPERATION_ENTAB:
            entab(line, len, spaces_in_tab);
            break;
        case OPERATION_DETAB:
            detab(line, len, spaces_in_tab);
            break;
        default:
            printf("error: invalid operation %i\n", operation);
            return -1;
        }
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

void detab(char buf[], int len, int spaces) {
    int i, j, k;

    // ensure enough space
    int required_len = 0;
    for (i = 0; i < len && buf[i] != 0; ++i) {
        bool is_tab = buf[i] == '\t';
        if (is_tab) {
            required_len += spaces;
        } else {
            required_len += 1;
        }
    }

    if (required_len > MAXLINE) {
        printf("ERROR: buf is not large enough");
        abort();
    }

    buf[required_len] = 0;

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
