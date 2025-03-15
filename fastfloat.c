#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


float double_float(float f) {
    uint32_t i;
    float result;

    memcpy(&i, &f, sizeof(f)); // Copy float to unsigned integer
    uint32_t exponent = (i >> 23) & 0xFF; // Extract exponent bits

    exponent++;

    i = (i & ~(0xFF << 23)) | (exponent << 23); // Merge modified exponent into integer
    memcpy(&result, &i, sizeof(result)); // Copy modified bits into float

    return result;
}
float half_float(float f) {
    uint32_t i;
    float result;

    memcpy(&i, &f, sizeof(f));
    uint32_t exponent = (i >> 23) & 0xFF;

    exponent--;

    i = (i & ~0x7f800000) | (exponent << 23);

    memcpy(&result, &i, sizeof(result));

    return result;
}


int main() {
    float f = 97.381f;
    int numIterations = 10000000;

    float fastDoubleResult = 0.0f;
    float fastHalfResult = 0.0f;
    float dubb = 0.0f;
    float halve = 0.0f;


    clock_t start = clock(); // Time double_float function
    for (int i = 0; i < numIterations; i++) {
        fastDoubleResult = double_float(f);
    }
    clock_t end = clock();
    double doubleFloatTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("double_float function time: %f seconds (result: %f)\n", doubleFloatTime, fastDoubleResult);

    start = clock(); // Time half_float function
    for (int i = 0; i < numIterations; i++) {
        fastHalfResult = half_float(f);
    }
    end = clock();
    double halfFloatTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("half_float function time: %f seconds (result: %f)\n", halfFloatTime, fastHalfResult);

    start = clock(); // Time regular doubling w/ multiplication
    for (int i = 0; i < numIterations; i++) {
        dubb = f * 2.0f;
    }
    end = clock();
    double multiplyTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Regular doubling time: %f seconds (result: %f)\n", multiplyTime, dubb);
    
    start = clock(); // Time regular halving w/ division
    for (int i = 0; i < numIterations; i++) {
        halve = f / 2.0f;
    }
    end = clock();
    double divideTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Regular halving time: %f seconds (result: %f)\n", divideTime, halve);

    return 0;
}
