#include <stdint.h>
#include <stdio.h>

#define LOWER   0
#define UPPER 300
#define STEP   20

int main() {
    float fahr, celsius;

    printf("celsius fahrenheit\n");

    celsius = LOWER;
    while (celsius <= UPPER) {
        fahr = celsius * (9.0f / 5.0f) + 32.0f;
        printf("%7.0f %10.1f\n", celsius, fahr);
        celsius += STEP;
    }
}

