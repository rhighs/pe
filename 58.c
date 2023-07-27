#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

#define UPTO 1000000000

typedef struct {
    u8 *data;
    u64 cap;
    u64 len;
} bit_array_t;

bit_array_t ba_init(u8 bit, u64 len) {
    bit_array_t result;
    result.cap = len/8 + (len%8>0);
    result.len = len;
    result.data = (u8 *)malloc(result.cap*sizeof(u8));
    memset(result.data,
            bit ? 0xFF : 0x00,
            result.cap*sizeof(u8));
    return result;
}

u8 ba_get(const bit_array_t *b, u64 at) {
    u64 at_cap = at/8;
    u8 at_bit = at%8;
    return (b->data[at_cap] >> (7 - at_bit)) & 0x1;
}

void ba_set(const bit_array_t *b, u64 at, u8 bit) {
    u64 at_cap = at/8;
    u8 at_bit = at%8;
    if (!(bit&0x1)){
        b->data[at_cap] &= ~(0x1 << (7 - at_bit));
        return;
    }
    b->data[at_cap] |= (0x1 << (7 - at_bit));
}

bit_array_t ba_sieve(const u64 N) {
    bit_array_t p = ba_init(1, N);
    ba_set(&p, 0, 0); 
    ba_set(&p, 1, 0); 
    u64 upto = (u64) (ceil(sqrt(N)));
    for (u64 i=2; i<upto; i++)
        if (ba_get(&p, i))
            for (u64 k = i*i; k<N; k+=i)
                ba_set(&p, k, 0);
    return p;
}

i32 main(void) {
    bit_array_t primes = ba_sieve(UPTO);

    u32 step = 1;
    u32 stride = 2;
    u32 iters = 0;
    double count = 0.0;
    double p_count = 0.0; 

    for (; step<UPTO; step += stride) {
        if (ba_get(&primes, step))
            p_count += 1.0;
        count += 1.0;

        iters++;
        if (iters == 5) {
            iters = 1;
            stride += 2;
        }

        if (p_count && p_count/count < 0.099999999) {
            break;
        }
    }

    printf("side length = %d (ratio = %f, rational = %.0f/%.0f)\n",
            stride - 1,
            p_count/count,
            p_count,
            count);

    return EXIT_SUCCESS;
}
