#include <stdio.h>

int rightrot(int x, int n);

int main() {
    int r = rightrot(0xA0000000, 2);
    printf("%x\n", r);
    return 0;
}

int rightrot(int x, int n) {
    unsigned int mask = 1;
    while (true) {
        unsigned int new_mask = mask << 1;
        if (new_mask != 0) {
            mask = new_mask;
        } else {
            break;
        }
    }

    for (int i = 0; i < n; ++i) {
        int bit = (x & mask) != 0;
        x = (x << 1) | bit;
    }

    return x;
}

