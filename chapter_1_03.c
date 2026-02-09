#include <stdint.h>
#include <stdio.h>

#define LOWER   0
#define UPPER 300
#define STEP   20

int main() {
    float fahr, celsius;

    printf("fahrenheit celsius\n");

    fahr = LOWER;
    while (fahr <= UPPER) {
        celsius = (5.0f / 9.0f) * (fahr - 32.0f);
        printf("%10.0f %7.1f\n", fahr, celsius);
        fahr += STEP;
    }
}
