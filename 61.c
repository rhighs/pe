#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 0x1
#define FALSE 0x0

typedef unsigned char b8;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long int u64;
typedef int i32;

#define NGON(k, n) ((n*((k-2)*n-(k-4)))/2)

b8 is_cyclic(u64 a, u64 b) {
    u64 aa = a - ((a/100)*100);
    u64 bb = b / 100;
    return aa == bb;
}

b8 find_cyclic_gon(u64 k, u64 *result, u64 wanted, u64 n) {
    if (wanted == n) return TRUE;

    u64 v = NGON(k, 0);
    u64 i = 0;
    for (;v<999; (i++, v=NGON(k, i)));
    for (;v<10000; (i++, v=NGON(k, i))) {
        // search here for (length = 4) cyclics
        if (n>0 && !is_cyclic(result[n-1], v)) continue;
        if (wanted-1 == n && !is_cyclic(result[n-1], v) && !is_cyclic(v, result[0])) continue;

        result[n] = v;
        if (!find_cyclic_gon(k+1, result, wanted, n+1)) continue;

        return TRUE;
    }

    return FALSE;
}

u64 sum(u64 *a, u64 len) {
    u64 result=0;
    while (len--) result+=a[len];
    return result;
}

i32 main( void ) {
    u64 result[6] = { 0 };
    find_cyclic_gon(3, result, 3, 0);
    printf("result[0] = %lld\n", result[0]);
    printf("result[1] = %lld\n", result[1]);
    printf("result[2] = %lld\n", result[2]);
    printf("result[3] = %lld\n", result[3]);
    printf("result[4] = %lld\n", result[4]);
    printf("result[5] = %lld\n", result[5]);

    printf("sum = %lld\n", sum(result, 6));
    return 0;
}

