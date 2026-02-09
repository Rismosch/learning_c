#include <stdio.h>

int main() {
    // compiler warning, gcc does not escape it and only prints "c"
    printf("\"\c\" is an invalid character\n");
}

