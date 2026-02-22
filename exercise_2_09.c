#include <stdio.h>

int bitcount(unsigned x);

int main() {
    int r = bitcount(0b101101);
    printf("%i\n", r);
    return 0;
}

// `(x - 1)` turns the rightmost 1 into a 0, and all 0s right to it
// into a 1. using that as a mask for `&` leaves all left bits
// unchanged, since they are the same as the mask. the 0s change
// nothing, because they are already 0. this leaves only the single
// flipped bit, which results in it flipped of, because `1&0==0`.
//
// thus, `x &= (x - 1)` changes the rightmost 1 into a 0;
int bitcount(unsigned x) {
    int b = 0;
    while (x != 0) {
        x &= (x - 1);
        b += 1;
    }
    return b;
}
