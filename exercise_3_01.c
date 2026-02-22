#include <stdio.h>

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, /*7,*/ 8, 9, 10, 11, 12, 13, 14 ,15, 16, 17, 18, 19, 20};
    printf("%i\n", binsearch2(7, array, 19));
    printf("%i\n", binsearch2(13, array, 19));

    return 0;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int binsearch2(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while ((high - low) > 1) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid;
        }
    }

    if (x == v[low]) {
        return low;
    } else if (x == v[high]) {
        return high;
    } else {
        return -1;
    }
}
