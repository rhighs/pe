#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <fmt/printf.h>

template <size_t N>
constexpr bool* primes()
{
    bool* p = (bool*)malloc(N*sizeof(bool)); p[0] = 0; p[1] = 0;
    for (int i=0; i<N; p[i++]=1);
    int upto = (int) (ceil(sqrt(N)));
    for (int i=2; i<upto; i++) if (p[i]) for (int k = i*i; k<N; k+=i) p[k] = 0;
    return p;
}

static bool is_perm(int v, int t)
{
    int d[10] = {0};
    while (v!=0) { d[v%10] += 1; v/=10; }
    while (t!=0) { d[t%10] -= 1; t/=10; }
    for (int v: d) { if (v != 0) return false; }
    return true;
}

int main(void)
{
    constexpr int N = 10000;
    auto p = primes<N>();
    int start = 1000;
    int additive = 3330;

    std::vector<int> candidates;

    for (int i=0; i < N; i++) {
        if (p[i] && p[i + additive] && p[i + additive * 2]) {
            int ii = i + additive;
            int iii = ii + additive;
            if (is_perm(i, ii) && is_perm(i, iii)) fmt::print("{}{}{}\n", i, ii, iii);
        }
    }

    return 0;
}
