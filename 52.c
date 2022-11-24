#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 100000000
#define SCAN_START 10000

static
void to_digits(int value, unsigned int* buf, int len)
{
    unsigned int i = len - 1, v=value;
    do {
        buf[i] = v % 10;
        i--;
        v /= 10;
    } while (v != 0);
#ifdef DEBUG
    printf("to_digits(value: %u): [", value);
    for (size_t i=0; i<len; ++i)
        printf("%d", buf[i]);
    printf("] (buf[0]: %d)\n", buf[0]);
#endif
}

int digits[10] = {0};
int digits_test[10] = {0};
int digits_pos[10] = {0};

static
bool same_digits(int value, int test)
{
    int vlen=0, tlen=0;
    int v=value, t=test;
    while (v!=0) {
        v=v/10;
        vlen++;
    }
    while (t!=0) {
        t=t/10;
        tlen++;
    }

    if (tlen != vlen) return false;

    int i, j;
    to_digits(value, digits, 10);
    to_digits(test, digits_test, 10);
    for (i=10-vlen; i<10; ++i) {
        digits_pos[digits[i]]++;
        digits_pos[digits_test[i]]--;
    }
    for (i=0; i<10 && !digits_pos[i]; ++i);
    for (j=0; j<10; ++j) {digits[j]=0;digits_test[j]=0;digits_pos[j]=0;}
    return i==10;
}

int main(void)
{
    int test=0;
    for (int i=SCAN_START; i<POOL_SIZE; i++) {
        if (same_digits(i, i*2))
        if (same_digits(i, i*3))
        if (same_digits(i, i*4))
        if (same_digits(i, i*5))
        if (same_digits(i, i*6)) {
            printf("6 >>> %d\n", i);
            break;
        }
    }
    return 0;
}
