#include <stdio.h>

// returns x with the n bits that begins at position p inverted
// example:
// x = 101101
// p = 2
// n = 3
// 
// result:
//
//       nnn
// x    101101
// x'   110001
int invert(int x, int p, int n);

int main() {
    int r = invert(055, 2, 3);
    printf("%o\n", r);
    return 0;
}

int invert(int x, int p, int n) {
    int mask = (1 << n) - 1;
    return x ^ (mask << p);
}

