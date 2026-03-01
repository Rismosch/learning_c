#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int character;
bool has_character;

/* get a (possibly pushed back) character */
int getch(void) {
    if (!has_character) {
        return getchar();
    }

    has_character = false;
    return character;
}

/* push character back on input */
void ungetch(int c) {
    if (c == EOF) {
        printf("ungetch: character was EOF\n");
        return;
    }

    if (has_character) {
        printf("ungetch: character was already pushed back\n");
        return;
    }

    character = c;
    has_character = true;
}

int main() {
    ungetch(EOF);

    int c;
    while ((c = getch()) != EOF) {
        printf("%3i: '%c'\n", c, c);
    }
}

