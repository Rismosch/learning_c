#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(
    void *lineptr[],
    int left,
    int right,
    int (*comp)(void *, void *),
    bool reverse
);

int numcmp(const char *, const char *);
int my_strcmp(char const *, char const *);

bool ignore_case = false;
bool only_compare_directory_order = false;
bool is_directory(char);

/* sort imput lines */
int main(int argc, char *argv[]) {
    int nlines;
    bool arg_numeric = false;
    bool arg_reverse = false;
    bool arg_fold = false;
    bool arg_directory = false;

    // parse cli
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        if (arg[0] != '-') {
            printf("unknown arg: %s\n", arg);
            return -1;
        }

        for (int j = 1; arg[j] != 0; ++j) {
            char c = arg[j];
            switch(c) {
            case 'n':
                arg_numeric = true;
                break;
            case 'r':
                arg_reverse = true;
                break;
            case 'f':
                arg_fold = true;
                break;
            case 'd':
                arg_directory = true;
                break;
            default:
                printf("unknown flag -%c", c);
                return -1;
            }
        }
    }

    ignore_case = arg_fold;
    only_compare_directory_order = arg_directory;

    // sort
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        int (*comp)(void *, void *);
        if (arg_numeric) {
            comp = (int (*)(void *, void *))numcmp;
        } else {
            comp = (int (*)(void *, void *))my_strcmp;
        }

        my_qsort(
            (void **) lineptr,
            0,
            nlines - 1,
            comp,
            arg_reverse
        );
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big for sort\n");
        return 1;
    }
}

#define MAXLEN 1<<10
int my_getline(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len * sizeof(char))) == NULL) {
            return -1;
        } else {
            line[len - 1] = 0; // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; ++i) {
        printf("%s\n", lineptr[i]);
    }
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

/* my_qsort: sort v[left]..v[right] into increasing order*/
void my_qsort(
    void *v[],
    int left,
    int right,
    int (*comp)(void *, void *),
    bool reverse
) {
    int i, last;
    void swap(void *v[], int, int);

    // do nothing if array contains fewer than two elements
    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i) {
        void *lhs;
        void *rhs;
        if (reverse) {
            lhs = v[i];
            rhs = v[left];
        } else {
            lhs = v[left];
            rhs = v[i];
        }

        if ((*comp)(lhs, rhs) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    my_qsort(v, left, last - 1, comp, reverse);
    my_qsort(v, last + 1, right, comp, reverse);
}

/* swap v[i] and v[j] */
void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s2 and s2 numerically */
int numcmp(const char *s1, const char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v2 > v2) {
        return 1;
    } else {
        return 0;
    }
}

/* my_strcmp: case sensitive compare s1 and s2*/
int my_strcmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int lhs = ignore_case ? tolower((unsigned char)*a) : (unsigned char)*a;
        int rhs = ignore_case ? tolower((unsigned char)*b) : (unsigned char)*b;
        int d = lhs - rhs;

        if (!*a)
        {
            return d;
        }

        if (d == 0)
        {
            continue;
        }

        if (!only_compare_directory_order) {
            return d;
        }

        if (!is_directory(*a) && !is_directory(*b)) {
            return d;
        }

        // one of the characters is directory, thus comparison is ignored!
    }


    return 0;
}

/* is_directory: returns true if c is a letter, number or blank */
bool is_directory(char c) {
    bool is_upper = isupper(c);
    bool is_lower = islower(c);

    bool is_digit = isdigit(c);

    bool is_letter = is_upper || is_lower;
    bool is_blank = c == ' ' || c == '\t' || c == '\n';

    return is_letter || is_digit || is_blank;
}
