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

#define HIGH_CARD       0x1
#define ONE_PAIR        0x2
#define TWO_PAIRS       0x3
#define THREE_OF_A_KIND 0x4
#define STRAIGHT        0x5
#define FLUSH           0x6
#define FULL_HOUSE      0x7
#define FOUR_OF_A_KIND  0x8
#define STRAIGHT_FLUSH  0x9
#define ROYAL_FLUSH     0xA

#define TEN     'T'
#define JACK    'J'
#define QUEEN   'Q'
#define KING    'K'
#define ACE     'A'

#define HAND_STRIDE 3
#define HAND_LEN 2 * 5 + 4

#define HAND_CHECK_ARGS const char *hand

i32 abs(i32 value) {
    if (value < 0) {
        return value * -1;
    }
    return value;
}

void to_values(const char *hand, u8 *values) { 
    for (u32 pos = 0; pos<HAND_LEN;) {
        switch (hand[pos]) {
            case TEN:   values[10]++; break;
            case JACK:  values[11]++; break;
            case QUEEN: values[12]++; break;
            case KING:  values[13]++; break;
            case ACE:   values[14]++; break;
            default:    values[(hand[pos]-'0')]++; break;
        }
        pos += HAND_STRIDE;
    }
}


u8 flush(HAND_CHECK_ARGS) {
    for (u32 pos = 4; pos<HAND_LEN;) {
        if (hand[pos] != hand[pos - HAND_STRIDE]) return 0;
        pos += HAND_STRIDE;
    }
    return 1;
}

u8 royal_flush(HAND_CHECK_ARGS) {
    char lookfor[5] = { TEN, JACK, QUEEN, KING, ACE };

    for (i32 i=4; i >= 0; i--) { 
        u32 pos = 0; u8 found = 0;
        for (;pos<HAND_LEN;) {
            if (hand[pos] == lookfor[i]) { found = 1; break; };
            pos += HAND_STRIDE;
        }
        if (!found) return 0;
    }

    return flush(hand);
}

u8 straight(HAND_CHECK_ARGS) {
    u8 values[15] = {0};
    to_values(hand, values);

    u32 starting = 0;
    while (values[starting] == 0) starting++;
    u8 result = values[starting++]
        && values[starting++]
        && values[starting++]
        && values[starting++]
        && values[starting++];

    return result;
}

u8 four_of_a_kind(HAND_CHECK_ARGS) {
    u8 values[15] = {0};
    to_values(hand, values);

    u8 found = 0;
    for (u32 i=0; i<15; i++)
        if (values[i] == 4) { found = 1; break; }
    return found;
}

u8 three_of_a_kind(HAND_CHECK_ARGS) {
    u8 values[15] = {0};
    to_values(hand, values);

    u8 found = 0;
    for (u32 i=0; i<15; i++)
        if (values[i] == 3) { values[i]=0; found = 1; break; }
    return found;
}

u8 two_pairs(HAND_CHECK_ARGS) {
    u8 values[15] = {0};
    to_values(hand, values);

    u8 pairs = 0;
    for (u32 i=0; i<15; i++) 
        if (values[i] == 2) pairs++;
    return pairs == 2;
}

u8 one_pair(HAND_CHECK_ARGS) {
    u8 values[15] = {0};
    to_values(hand, values);

    u8 found = 0;
    for (u32 i=0; i<15; i++) {
        if (values[i] == 2) {
            values[i] = 0;
            found = 1;
            break;
        }
    }

    return found;
}

u8 straight_flush(HAND_CHECK_ARGS) { return straight(hand) && flush(hand); }

u8 full_house(HAND_CHECK_ARGS) { return three_of_a_kind(hand) && one_pair(hand); }

u32 kind(const char *hand) {
    if (royal_flush(hand))      return ROYAL_FLUSH;
    if (straight_flush(hand))   return STRAIGHT_FLUSH;
    if (four_of_a_kind(hand))   return FOUR_OF_A_KIND;
    if (full_house(hand))       return FULL_HOUSE;
    if (flush(hand))            return FLUSH;
    if (straight(hand))         return STRAIGHT;
    if (three_of_a_kind(hand))  return THREE_OF_A_KIND;
    if (two_pairs(hand))        return TWO_PAIRS;
    if (one_pair(hand))         return ONE_PAIR;
    return HIGH_CARD;
}

u8 highest_value(const char *hand, u8 *values, u8 must_be) {
    i8 i=14;
    for (; i>=0; i--) {
        if (must_be == 0) {
            if(values[i]) { values[i] = 0; return i; }
        } else {
            if (values[i] == must_be)  { values[i] = 0; return i; }
        }
    }
    return 0;
}

i32 main(void) {
    FILE *file;
    file = fopen("./assets/p54.txt", "rb");
    fseek(file, 0, SEEK_END);
    u32 file_size = ftell(file); rewind(file);
    if (!file_size)
        return EXIT_FAILURE;

    char *buffer = (char *)malloc(file_size+1);
    u32 nread = fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';
    if (!nread)
        return EXIT_FAILURE;

    char *first_hand_ptr = buffer;
    char *second_hand_ptr = buffer + (HAND_LEN + 1);

    u32 p1_score = 0;
    while (first_hand_ptr < buffer + (file_size)) {
        u32 p1 = kind(first_hand_ptr);
        u32 p2 = kind(second_hand_ptr);

        if (p1 > p2) {
            p1_score++;
        } else if (p1 == p2) {
            u8 p1_values[15] = {0};
            u8 p2_values[15] = {0};

            to_values(first_hand_ptr,  p1_values);
            to_values(second_hand_ptr, p2_values);

            u32 old_p1 = p1_score;

            u8 type = p1;
            switch (type) {
            case HIGH_CARD: 
            case ONE_PAIR: 
            case THREE_OF_A_KIND: {
                u8 s1 = highest_value(first_hand_ptr, p1_values, type);
                u8 s2 = highest_value(second_hand_ptr, p2_values, type);
                while (s1 == s2 && s1 != 0) {
                    s1 = highest_value(first_hand_ptr, p1_values, 1);
                    s2 = highest_value(second_hand_ptr, p2_values, 1);
                }
                if (s1 > s2) p1_score++;
                break;
            }

            case FLUSH:
            case STRAIGHT_FLUSH:
            case STRAIGHT: {
                u32 sum_1 = 0;
                u32 sum_2 = 0;
                for (u32 i=0; i<5; i++) {
                    sum_1 += highest_value(first_hand_ptr, p1_values, 1);
                    sum_2 += highest_value(second_hand_ptr, p2_values, 1);
                }
                if (sum_1 > sum_2) p1_score++;
                break;
            }

            case FULL_HOUSE: {
                u8 s1_1 = highest_value(first_hand_ptr, p1_values, 3);
                u8 s1_2 = highest_value(first_hand_ptr, p1_values, 2);
                u8 s2_1 = highest_value(second_hand_ptr, p2_values, 3);
                u8 s2_2 = highest_value(second_hand_ptr, p2_values, 2);
                if (s1_1 > s2_1 || (s1_1 == s2_1 && s1_2 > s2_2)) p1_score++;
                break;
            }

            case TWO_PAIRS: {
                u8 s1_1 = highest_value(first_hand_ptr, p1_values, 2);
                u8 s1_2 = highest_value(first_hand_ptr, p1_values, 2);
                u8 s2_1 = highest_value(second_hand_ptr, p2_values, 2);
                u8 s2_2 = highest_value(second_hand_ptr, p2_values, 2);
                if (s1_1 + s1_2 > s2_1 + s2_2
                        || (s1_1 + s1_2 == s2_1 + s2_2
                            && highest_value(first_hand_ptr, p1_values, 1)
                            > highest_value(second_hand_ptr, p2_values, 1)))
                    p1_score++;
                break;
            }

            case FOUR_OF_A_KIND: {
                u8 s1 = highest_value(first_hand_ptr,  p1_values, 4);
                u8 s2 = highest_value(second_hand_ptr, p2_values, 4);
                if (s1 > s2 || (s1 == s2 && highest_value(first_hand_ptr, p1_values, 1)
                            > highest_value(second_hand_ptr, p2_values, 1)))
                    p1_score++;
                break;
            }
            }
        }

        first_hand_ptr  += (HAND_LEN + 1) * 2;
        second_hand_ptr += (HAND_LEN + 1) * 2;
    }

    free(buffer);

    printf("score = %d\n", p1_score);
    return 0;
}
