#include <float.h>
#include <stdio.h>

#define SWAP(t,x,y) t temp##t = x; x = y; y = temp##t;

int main() {
    int a = 42;
    int b = -13;
    float af = NAN;
    float bf = FLT_MAX;

    SWAP(int, a, b);
    SWAP(float, af, bf);

    printf("a=%i b=%i\n", a, b);
    printf("af=%f bf=%f\n", af, bf);

    return 0;
}


