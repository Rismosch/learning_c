#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */
#define MAXFIELDS 100       /* max #fields to be sorted */
char *fieldptr[MAXFIELDS];

int readlines(char *lineptr[], int nlines);
int readfields(char *s, char *fieldptr[], int nfields);
void writestrings(char *sptr[], int nlines, char linefeed);

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
    int nfields;
    bool arg_numeric = false;
    bool arg_reverse = false;
    bool arg_fold = false;
    bool arg_directory = false;
    bool arg_handle_fields = false;

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
            case 'h':
                arg_handle_fields = true;
                break;
            default:
                printf("unknown flag -%c", c);
                return -1;
            }
        }
    }

    ignore_case = arg_fold;
    only_compare_directory_order = arg_directory;

    // read lines
    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("input too big for sort\n");
        return -1;
    }

    // determine sort func
    int (*comp)(void *, void *);
    if (arg_numeric) {
        comp = (int (*)(void *, void *))numcmp;
    } else {
        comp = (int (*)(void *, void *))my_strcmp;
    }

    // sort lines
    if (!arg_handle_fields) {
        my_qsort(
            (void **) lineptr,
            0,
            nlines - 1,
            comp,
            arg_reverse
        );
        writestrings(lineptr, nlines, '\n');
        return 0;
    }

    // fields
    for (int i = 0; i < nlines; ++i) {
        char *line = lineptr[i];
        char line_len = strlen(line);

        // find fields
        int j;
        char prev = 0;
        for (j = 0; j < line_len; ++j) {
            char c = line[j];

            if (c == ' ' && prev == ' ') {
                //line[j] = 0;
                break;
            }

            prev = c;
        }

        if (j >= line_len || j == 0) {
            // nothing to sort
            printf("%s\n", lineptr[i]);
            continue;
        }

        // print everything up to the fields
        for (int k = 0; k < j; ++k) {
            putchar(line[k]);
        }

        // read fields
        if ((nfields = readfields(&line[j], fieldptr, MAXFIELDS)) < 0) {
            printf("input too big for sort\n");
            return -1;
        }

        // sort fields
        my_qsort(
            (void **) fieldptr,
            0,
            nfields - 1,
            comp,
            arg_reverse
        );
        writestrings(fieldptr, nfields, ',');
        printf("\n");
    }

    return 0;
}

#define MAXLEN 1<<10
int my_getline(char *, int);
int my_getfield(char *, char *, int);

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

/* readfields: read fields separated by ',' */
int readfields(char *s, char *fieldptr[], int maxfields) {
    int len, nfields;
    char *p, field[MAXLEN];

    nfields = 0;
    while ((len = my_getfield(s, field, MAXLEN)) > 0) {
        if (nfields >= maxfields || (p = malloc(len * sizeof(char))) == NULL) {
            return -1;
        } else {
            // delete separator
            if (field[len - 1] == ',') {
                field[len - 1] = 0; 
            }

            strcpy(p, field);
            fieldptr[nfields++] = p;
            s += len;
        }
    }

    return nfields;
}

/* writestrings: write output lines */
void writestrings(char *lineptr[], int nlines, char linefeed) {
    int i;

    for (i = 0; i < nlines; ++i) {
        printf("%s%c", lineptr[i], linefeed);
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


int my_getfield(char *input, char output[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = *input++) != 0 && c != ','; ++i) {
        output[i] = c;
    }

    if (c == ',') {
        output[i] = c;
        ++i;
    }

    output[i] = 0;
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
        if (only_compare_directory_order) {
            while (!is_directory(*a)) {
                a++;
            }

            while (!is_directory(*b)) {
                b++;
            }
        }

        int lhs = ignore_case ? tolower((unsigned char)*a) : (unsigned char)*a;
        int rhs = ignore_case ? tolower((unsigned char)*b) : (unsigned char)*b;
        int d = lhs - rhs;

        if (d != 0 || !*a)
        {
            return d;
        }
    }

    return 0;
}

/* is_directory: returns true if c is a letter, number or blank */
bool is_directory(char c) {
    bool is_upper = isupper(c);
    bool is_lower = islower(c);
    bool is_letter = is_upper || is_lower;

    bool is_digit = isdigit(c);
    bool is_blank = c == ' ' || c == '\t' || c == '\n';
    bool is_null = c == 0;

    return is_letter || is_digit || is_blank || is_null;
}
