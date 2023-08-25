#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 0x1
#define FALSE 0x0

typedef unsigned char b8;
typedef unsigned char u8;
typedef unsigned long long int u64;
typedef int i32;
typedef long double f64;

#define NLEN 20

u64 cube(u64 n) { return n * n * n; }
b8 is_cube(u64 n) {
    int v = round(pow((f64)n, 1.0/3.0));
    return n==cube(v);
}

u64 as_array(u64 n, u8 *dst) {
    u64 i = 0;
    while (n>0) {
        u64 digit = n % 10;
        n /= 10;
        if (dst != NULL) 
        dst[i++] = digit;
    }
    return i;
}

void swap(u8 *arr, u64 i, u64 j) {
    u8 tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

b8 includes(u8 *arr, u64 len, u64 n) {
    for (u64 i=0; i<len; i++) 
        if (arr[i] == n) return TRUE;
    return FALSE;
}

b8 is_perm(u64 a, u64 b) {
    u8 aa[NLEN] = {0};          u8 bb[NLEN] = {0};
    u8 bit_a[10] = {0};         u8 bit_b[10] = {0};
    u64 alen = as_array(a, aa); u64 blen = as_array(b, bb);

    if (alen != blen) return FALSE;
    for (u64 i=0; i<alen; i++) bit_a[aa[i]]++;
    for (u64 i=0; i<blen; i++) bit_b[bb[i]]++;
    for (u64 i=0; i<10; i++) if (bit_a[i]!=bit_b[i]) return FALSE;

    return TRUE;
}

i32 main( void ) {
    u64 c=0; u64 i=0;
    for (; i<10000; i++) {
        c = cube(i);
        u64 nperms = 0;
        for (u64 j = 0; j<10000; j++) {
            u64 cc = cube(j);
            nperms += is_perm(c, cc);
        }
        if (nperms==5) break;
    }

    printf("result = %lld (at: %lld)\n", c, i);
    return 0;
}

