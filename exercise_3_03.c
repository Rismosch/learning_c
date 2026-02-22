#include <stdio.h>
#define BUF_LEN 1<<10

void expand(char s1[], char s2[]);

int main() {
    char buf[BUF_LEN];

    expand("a-z", buf);
    printf("1: \"%s\"\n", buf);
    expand("a-b-c", buf);
    printf("2: \"%s\"\n", buf);
    expand("a-z0-9", buf);
    printf("3: \"%s\"\n", buf);
    expand("-a-z", buf);
    printf("4: \"%s\"\n", buf);

    return 0;
}

bool is_lower(char c) {
    return c >= 'a' && c <= 'z';
}

bool is_upper(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_valid(char c) {
    return is_lower(c) || is_upper(c) || is_digit(c);
}

bool can_apply_range(char lhs, char rhs) {
    if (!is_valid(lhs) || !is_valid(rhs)) {
        return false;
    }

    bool both_are_lower = is_lower(lhs) && is_lower(rhs);
    bool both_are_upper = is_upper(lhs) && is_upper(rhs);
    bool both_are_digit = is_digit(lhs) && is_digit(rhs);
    bool cases_match = both_are_lower || both_are_upper || both_are_digit;
    if (!cases_match) {
        return false;
    }

    bool is_increasing = lhs < rhs;
    if (!is_increasing) {
        return false;
    }

    return true;
}

void expand(char s1[], char s2[]) {
    int i, j, k;

    for (i = 0, j = 0; s1[i] != 0; ++i) {
        if (i == 0 || (s1[i] != '-')) {
            s2[j] = s1[i];
            j += 1;
            continue;
        }

        char min = s1[i - 1];
        char max = s1[i + 1];

        if (!can_apply_range(min, max)) {
            s2[j] = s1[i];
            j += 1;
            continue;
        }

        for (k = min + 1; k < max; ++k) {
            s2[j] = k;
            j += 1;
        }
    }

    s2[j] = 0;
}
