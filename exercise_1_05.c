#include <stdint.h>
#include <stdio.h>

#define LOWER   0
#define UPPER 300
#define STEP   20

int main() {
    printf("fahrenheit celsius\n");
    for (float f = UPPER; f >= LOWER; f -= STEP) {
        float c = (5.0f / 9.0f) * (f - 32.0f);
        printf("%10.0f %7.1f\n", f, c);
    }
}

