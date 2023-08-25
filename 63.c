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

b8 oflen(f64 n, u64 len) {
    if (len==0)         return FALSE;
    return    (pow(10, len-1)) <= n
        && n < pow(10, len);
}

i32 main( void ) {
    u64 result = 0;
    for (u64 i=0; i<10; i++) for (u64 j=0; j<23; j++)
        if (oflen(pow(i, j), j))
            result++;
    printf("result = %lld\n", result);
    return 0;
}

