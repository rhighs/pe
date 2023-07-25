#include <stdio.h>
#include <stdint.h>
#include <assert.h> 
#include <stdlib.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

u64 n_digits(u64 n) {
    u64 result = 0; while (n/=10) result++;
    return result;
}

u64 lcm(u64 a, u64 b) {
    u64 d = (a > a) ? a : b;  
    while (d % a != 0 || d % b != 0) d++;
    return d;
}
 
typedef struct { u64 n, d; } rational;
rational rat_add(rational r1, rational r2) {
    u64 d = lcm(r1.d, r2.d);
    u64 n = ((d / r1.d) * r1.n) + ((d / r2.d) * r2.n);
    return (rational){ n, d };
}
rational rat_mul(rational r1, rational r2) {
    u64 n = r1.n * r2.n;
    u64 d = r1.d * r2.d;
    return (rational){ n, d };
}
rational rat_div(rational r1, rational r2) {
    if (r2.d == 1) return (rational){ r1.n, r1.d * r2.n };
    return rat_mul(r1, (rational){ r2.d, r2.n });
}
rational __sqrt2_den(u64 depth) {
    if (depth == 0) return (rational){ 0, 1 };
    return rat_div(
        (rational){ 1, 1 },
        rat_add(
            (rational){ 2, 1 },
            __sqrt2_den(depth - 1)
        )
    );
}

i32 main(void) {
    u64 count = 0;
    for (u64 i=0; i<1000; i++) {
        rational x = rat_add((rational){ 1, 1 }, __sqrt2_den(i+1));
        printf("isqrt2(%d) = %d/%d\n", i+1, x.n, x.d);
        if (n_digits(x.n) > n_digits(x.d))
            count++;
    }
    printf("count = %d\n", count);
    return EXIT_SUCCESS;
}
