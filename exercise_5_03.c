#include <stdio.h>

#define BUFLEN 1<<10

/* strcat: concatenate t to the end of s; s must be big enough */
void strcat(char* s, char* t);

int main() {
    char buf[BUFLEN] = "hello";
    strcat(buf, "world");
    printf("%s\n", buf);
    return 0;
}

void strcat(char* s, char* t) {
    while(*s){
        s++;
    }

    while(*s++ = *t++){}
}
