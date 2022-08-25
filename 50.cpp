#include <math.h>
#include <stdio.h>

template <size_t N>
constexpr bool* primes()
{
    bool* p = (bool*)malloc(N*sizeof(bool)); p[0] = 0; p[1] = 0;
    for (int i=0; i<N; p[i++]=1);
    int upto = (int) (ceil(sqrt(N)));
    for (int i=2; i<upto; i++) if (p[i]) for (int k = i*i; k<N; k+=i) p[k] = 0;
    return p;
}

int main(void)
{
    constexpr int N = 1000000;
    bool* p = primes<N>();
    int sum = 0;
    for (int i=0; i<N && sum+i < N; ++i) if (p[i]) sum+=i;
    for (int i=0; i<N && !p[sum]; ++i) if (p[i]) sum-=i;
    printf("%d\n", sum);
    return 0;
}
