#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float float_bitshift(float f, int bitshift) {
    uint32_t i;
    float result;

    memcpy(&i, &f, sizeof(f)); // Copy float to unsigned integer
    uint32_t exponent = (i >> 23) & 0xFF; // Extract exponent bits

    exponent += bitshift;

    i = (i & ~(0xFF << 23)) | (exponent << 23); // Merge modified exponent into integer
    memcpy(&result, &i, sizeof(result)); // Copy modified bits into float

    return result;
}

double double_bitshift(double f, int bitshift) {
    uint64_t i;
    double result;

    memcpy(&i, &f, sizeof(f));
    uint64_t exponent = (i >> 52) & 0x7FF;

    exponent += bitshift;

    i = (i & ~(0x7FFULL << 52)) | (exponent << 52);
    memcpy(&result, &i, sizeof(result));

    return result;
}


int main() {
    srand(time(0)); // Seed the RNG
    int numIterations = 10000000;

    double randomDouble = (double) rand() / 1073741824;
    float randomFloat = (float) randomDouble;

    float fastFloatX2Result = 0.0f;
    float fastFloatHalfResult = 0.0f;
    double fastDoubleX2Result = 0.0f;
    double fastDoubleHalfResult = 0.0f;
    float floatDouble = 0.0f;
    float floatHalve = 0.0f;
    double doubleDouble = 0.0f;
    double doubleHalve = 0.0f;

    printf("Original random float: %.24f\n", randomFloat);
    printf("Original random double: %.32lf\n", randomDouble);


    // Time float_bitshift (x2) function
    clock_t start = clock();
    for (int i = 0; i < numIterations; i++) {
        fastFloatX2Result = float_bitshift(randomFloat, 1);
    }
    clock_t end = clock();
    double doubleFloatTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("float_bitshift (x2) function time: %.8fs\t(result: %.24f)\n", doubleFloatTime, fastFloatX2Result);

    // Time float_bitshift (/2) function
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        fastFloatHalfResult = float_bitshift(randomFloat, -1);
    }
    end = clock();
    double halfFloatTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("float_bitshift (/2) function time: %.8fs\t(result: %.24f)\n", halfFloatTime, fastFloatHalfResult);

    // Time double_bitshift (x2) function
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        fastDoubleX2Result = float_bitshift(randomFloat, 1);
    }
    end = clock();
    double doubleDoubleTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("double_bitshift (x2) function time: %.8fs\t(result: %.32lf)\n", doubleDoubleTime, fastDoubleX2Result);

    // Time double_bitshift (/2) function
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        fastDoubleHalfResult = float_bitshift(randomFloat, -1);
    }
    end = clock();
    double halfDoubleTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("double_bitshift (/2) function time: %.8fs\t(result: %.32lf)\n", halfDoubleTime, fastDoubleHalfResult);

    // Time regular float (x2)
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        floatDouble = randomFloat * 2.0f;
    }
    end = clock();
    double multiplyTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Regular float (x2) time: %.8fs\t\t\t\t\t\t(result: %.24f)\n", multiplyTime, floatDouble);

    // Time regular float (/2)
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        floatHalve = randomFloat / 2.0f;
    }
    end = clock();
    double divideTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Regular float (/2) time: %.8fs\t\t\t\t\t\t(result: %.24f)\n", divideTime, floatHalve);

    // Time regular double (x2)
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        doubleDouble = randomDouble * 2.0f;
    }
    end = clock();
    double doubleX2Time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Regular double (x2) time: %.8fs\t\t\t\t\t\t(result: %.32lf)\n", doubleX2Time, doubleDouble);

    // Time regular double (/2)
    start = clock();
    for (int i = 0; i < numIterations; i++) {
        doubleHalve = randomDouble / 2.0f;
    }
    end = clock();
    double doubleHalveTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Regular double (/2) time: %.8fs\t\t\t\t\t\t(result: %.32lf)\n", doubleHalveTime, doubleHalve);

    return 0;
}