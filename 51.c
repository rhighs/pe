#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * WARNING THIS CODE IS HORRIBLE.
 * IF YOU READ THIS, YOU WILL BECOME STUPID 100%
 * THERE IS NO COMING BACK!
 *
 * SAFETY CAT HERE TO SAVE YOUR EYES:
 *               ,_     _
 *               |\\_,-~/
 *               / _  _ |    ,--.
 *              (  @  @ )   / ,-'
 *               \  _T_/-._( (
 *               /         `. \
 *              |         _  \ |
 *               \ \ ,  /      |
 *                || |-_\__   /
 *               ((_/`(____,-'
 */

#define SCAN_START 100000
#define SCAN_END 1000000
#define PRIMES 10000000
#define FAM_SIZE 8
#define MASK_START 1
#define MASK_SIZE 256

unsigned char masks[MASK_SIZE][8];
int primesFound[8];

static
int* sieve(const size_t N)
{
    int* p = (int*)malloc(N*sizeof(int)); p[0] = 0; p[1] = 0;
    for (int i=0; i<N; p[i++]=1);
    int upto = (int) (ceil(sqrt(N)));
    for (int i=2; i<upto; i++) if (p[i]) for (int k = i*i; k<N; k+=i) p[k] = 0;
    return p;
}

static
int to_value(unsigned int* digits, size_t len)
{
    size_t i=8-len;
    int n=0;
    for (; i<len; ++i) {
        n += digits[i];
        if (i < len-1) {
            n *= 10;
        }
    }
#ifdef DEBUG
    printf("to_value(digits: ");
    for (size_t i=0; i<8; ++i)
        printf("%d", digits[i]);
    printf("): [%u]\n", n);
#endif
    return n;
}

static
void to_digits(unsigned int value, unsigned int* buf, size_t len)
{

    unsigned int i = len - 1, v=value;
    do {
        buf[i] = v % 10;
        i--;
        v /= 10;
    } while (v != 0);

#ifdef DEBUG
    printf("to_digits(value: %u): [", value);
    for (size_t i=0; i<8; ++i)
        printf("%d", buf[i]);
    printf("] (buf[0]: %d)\n", buf[0]);
#endif
}

static
void to_bits(unsigned char byte, unsigned char* buffer, size_t len)
{
    for (size_t i=0; i<len; ++i)
        buffer[len-i-1] = (byte >> i) & 1;
}

int main(void)
{
    int* primes = sieve(PRIMES);
    unsigned char mask = 0;
    for (size_t i=0; i<MASK_SIZE; ++i)
        to_bits(++mask, masks[i], 8);
    printf("wacky prime: %d\n", primes[1000880]);

    size_t mask_position = 0;
    unsigned int start = SCAN_START;
    unsigned int digits[8] = {0};

    int nfound=0, i=0, j=0, k=0, value=0;
    unsigned char* curmask = NULL;

    for (; start<SCAN_END; ++start) {
        int numberSize=0;
        int n=start;
        while (n!=0) {
            n=n/10;
            numberSize++;
        }

        for (i=0; i<MASK_SIZE; ++i) {
            curmask = masks[i];
            to_digits(start, digits, 8);

            for (k=curmask[8-numberSize]; k<10; ++k) {
                int anymask = 0;
                for (j=8-numberSize; j<8; ++j) {
                    if (curmask[j]) {
                        anymask = 1;
                        digits[j] = k;
                    }
                }
                if (!anymask) break;
                value = to_value(digits, 8);

                if (primes[value]) {
                    printf("prime found: %d\n", value);
                    primesFound[nfound++] = value;
                    if (nfound == FAM_SIZE) {
                        printf("Primes found:\n");
                        for(size_t p=0; p<8; ++p)
                            printf("\t- %d\n", primesFound[p]);
                        printf("\n");
                        return 0;
                    }
                }
            }

            // reset
            for(size_t p=0; p<8; ++p) primesFound[p] = 0;
            nfound = 0;
        }

    }

    return 0;
}

