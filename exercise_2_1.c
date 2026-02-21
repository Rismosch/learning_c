#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("limits.h\n");
    printf("  CHAR_BIT     %20i\n", CHAR_BIT);
    printf("  CHAR_MAX     %20i\n", CHAR_MAX);
    printf("  CHAR_MIN     %20i\n", CHAR_MIN);
    printf("  INT_MAX      %20i\n", INT_MAX);
    printf("  INT_MIN      %20i\n", INT_MIN);
    printf("  LONG_MAX     %20li\n", LONG_MAX);
    printf("  LONG_MIN     %20li\n", LONG_MIN);
    printf("  SCHAR_MAX    %20i\n", SCHAR_MAX);
    printf("  SCHAR_MIN    %20i\n", SCHAR_MIN);
    printf("  SHRT_MAX     %20i\n", SHRT_MAX);
    printf("  SHRT_MIN     %20i\n", SHRT_MIN);
    printf("  UCHAR_MAX    %20u\n", UCHAR_MAX);
    printf("  UINT_MAX     %20u\n", UINT_MAX);
    printf("  ULONG_MAX    %20lu\n", ULONG_MAX);
    printf("  USHRT_MAX    %20u\n", USHRT_MAX);
    printf("\n");
    printf("float.h\n");
    printf("  FLT_RADIX    %20i\n", FLT_RADIX);
    printf("  FLT_ROUNDS   %20i\n", FLT_ROUNDS);
    printf("  FLT_DIG      %20i\n", FLT_DIG);
    printf("  FLT_EPSILON  %20e\n", FLT_EPSILON);
    printf("  FLT_MANT_DIG %20i\n", FLT_MANT_DIG);
    printf("  FLT_MAX      %20e\n", FLT_MAX);
    printf("  FLT_MAX_EXP  %20i\n", FLT_MAX_EXP);
    printf("  FLT_MIN      %20e\n", FLT_MIN);
    printf("  FLT_MIN_EXP  %20i\n", FLT_MIN_EXP);
    printf("  DBL_DIG      %20e\n", DBL_DIG);
    printf("  DBL_EPSILON  %20e\n", DBL_EPSILON);
    printf("  DBL_MANT_DIG %20i\n", DBL_MANT_DIG);
    printf("  DBL_MAX      %20e\n", DBL_MAX);
    printf("  DBL_MAX_EXP  %20i\n", DBL_MAX_EXP);
    printf("  DBL_MIN      %20e\n", DBL_MIN);
    printf("  DBL_MIN_EXP  %20i\n", DBL_MIN_EXP);
    return 0;
}
