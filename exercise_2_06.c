#include <stdio.h>

// returns x with the n bits that begin at position p set to the rightomst n bits of y
//
// example:
// x = 101101
// p = 2
// n = 3
// y = 001001
// 
// result:
//
//       nnn
// x    101101
// y  001001    p=2
// x'   100101
int setbits(int x, int p, int n, int y);

int main() {
    int r = setbits(055, 2, 3, 011);
    printf("%o\n", r);
    return 0;
}

int setbits(int x, int p, int n, int y) {
    int mask = (1 << n) - 1;
    int mask2 = mask << p;
    int x_ = x & (~(mask << p));
    int y_ = (y & mask) << p;
    return x_ | y_;
}

