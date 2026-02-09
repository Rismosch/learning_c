#include "stdio.h"

float fahrenheit_to_celsius(float value);

int main() {
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = fahrenheit_to_celsius(fahr);
        printf("%5.1f %5.1f\n", fahr, celsius);
        fahr += step;
    }

    return 0;
}

float fahrenheit_to_celsius(float value) {
    float celsius = 5.0f * (value - 32.0f) / 9.0f;
    return celsius;
}
