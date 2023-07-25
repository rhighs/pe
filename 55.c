#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

u64 reverse(u64 n) { 
    u64 reversed = 0;
    while (n > 0) { 
        reversed = (reversed * 10) + (n % 10);
        n /= 10;
    }
    return reversed;
}

u8 is_palindrome(u64 value) { return value == reverse(value); }

u8 is_lychrel(u64 value) {
    for (u32 i=0; i<50; i++) {
        u64 reversed = reverse(value);
        value += reversed;
        if (is_palindrome(value)) {
            return 1;
        }
    }

    return 0;
}

i32 main(void) {
    u32 lychrels = 0;
    for (u32 i=0; i<10000; i++)
        lychrels += is_lychrel(i);
    printf("lychrels = %d\n", lychrels);
    return EXIT_SUCCESS;
}

