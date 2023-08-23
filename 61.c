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

b8 binds(u64 a, u64 b) {
    u64 aa = a - ((a/100)*100);
    u64 bb = b / 100;
    return aa == bb;
}

b8 find_cycles(u64 *result, u64 rlen, u64 *exclude, u64 elen, u64 n) {
    if (rlen == n) return TRUE;

    for (u64 try_k=3; try_k<elen; try_k++) {
        if (exclude[try_k]) continue;

        u64 i = 0;
        u64 v = NGON(try_k, 0);

        // reach above 1000 to get in range [1000..9999]
        for (;v<999; (i++, v=NGON(try_k, i)));

        // recursion area, restore exclude[try_k]
        exclude[try_k] = 1; // exclude try_k-gon for child calls as we are using it here
        for (;v<10000; (i++, v=NGON(try_k, i))) {
            if (n+1==rlen && !binds(v, result[0])) continue; // if last number does bind the first one, skip
            else if (n>0 && !binds(result[n-1], v)) continue; // if current does not bind the previous one, skip

            result[n] = v; // one of the above did actually bind, go on with the others
            if (!find_cycles(result, rlen, exclude, elen, n+1)) continue;
            else return TRUE;
        }
        exclude[try_k] = 0; // no good bind was found, backtrace try_k and let it free!
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
    u64 exclude[9] = { 0 };
    find_cycles(result, 6, exclude, 9, 0);

    printf("result[0] = %lld\n", result[0]);
    printf("result[1] = %lld\n", result[1]);
    printf("result[2] = %lld\n", result[2]);
    printf("result[3] = %lld\n", result[3]);
    printf("result[4] = %lld\n", result[4]);
    printf("result[5] = %lld\n", result[5]);

    printf("sum = %lld\n", sum(result, 6));
    return 0;
}

