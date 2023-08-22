#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 0x1
#define FALSE 0x0

typedef unsigned char b8;
typedef unsigned char u8;
typedef unsigned long long int u64;
typedef int i32;

u8 *p = NULL;

u8* sieve(const u64 N) {
    u8* p = (u8*)malloc(N*sizeof(u8)); p[0] = 0; p[1] = 0;
    for (u64 i=0; i<N; p[i++]=1);
    u64 upto = (u64) (ceil(sqrt(N)));
    for (u64 i=2; i<upto; i++) if (p[i]) for (u64 k = i*i; k<N; k+=i) p[k] = 0;
    return p;
}
#define N 100000000

u64 numcat(u64 x, u64 y) {
    u64 pow = 10;
    while(y >= pow) pow *= 10;
    return x * pow + y;
}

b8 includes(u64 *arr, u64 len, u64 v) {
    for (u64 i=0; i<len; i++)
        if (arr[i] == v)
            return TRUE;
    return FALSE;
}

b8 is_prime(u64 num) {
    if (num < N) return p[num];
    for (u64 i = 3; i < num / 2; i+= 2)
        if (num % i == 0)
            return FALSE;
    return TRUE;
}

b8 allcat(u64 *arr, u64 len, u64 catme) {
    for (u64 i=0; i<len; i++) {
        if (!is_prime(numcat(arr[i], catme))
         || !is_prime(numcat(catme, arr[i]))) {
            return FALSE;
        }
    }
    return TRUE;
}

b8 get_cat(u64 from, u64 *result, u64 wanted, u64 n) {
    if (wanted == n)
        return TRUE;

    for (u64 i=from; i<ceil(sqrt(N)); i++) {
        if (!is_prime(i)) continue;
        if (includes(result, n, i)) continue;
        if (n > 0 && !allcat(result, n, i)) continue;

        result[n]=i;

        if (!get_cat(i, result, wanted, n+1)) continue;


        return TRUE;
    }

    return FALSE;
}

u64 sum(u64 *a, u64 len) {
    u64 result=0;
    while (len--) result+=a[len];
    return result;
}

i32 main(void) { 
    p = sieve(N);
    u64 result[5] = {0};
    get_cat(3, result, 5, 0);

    printf("result[0] = %lld\n", result[0]);
    printf("result[1] = %lld\n", result[1]);
    printf("result[2] = %lld\n", result[2]);
    printf("result[3] = %lld\n", result[3]);
    printf("result[4] = %lld\n\n", result[4]);

    printf("sum = %lld\n", sum(result, 5));
    return 0;
}

