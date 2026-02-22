#include <stdio.h>

#define BUF_LEN 1<<10

void escape(char s[], char t[]);

int main() {
    char s[] = "this is a newline: `\n`, this is a tab: `\t`";
    char t[BUF_LEN];
    escape(s, t);
    printf("s: \"%s\"\nt: \"%s\"\n", s, t);
    return 0;
}

void escape(char s[], char t[]) {
    int i, j;
    for (i = 0, j = 0; s[i] != 0; ++i) {
        switch(s[i]) {
            case '\n':
                t[j] = '\\';
                t[j + 1] = 'n';
                j += 2;
                break;
            case '\t':
                t[j] = '\\';
                t[j + 1] = 't';
                j += 2;
                break;
            default:
                t[j] = s[i];
                j += 1;
                break;
        }
    }
}
