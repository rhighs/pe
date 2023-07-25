import sys
sys.setrecursionlimit(1500)

class rational:
    def __init__(self, n, d):
        self.n = n
        self.d = d

def lcm(a, b):
    d =  a if a > b else b  
    while d % a != 0 or d % b != 0:
        d+=1
    return d

def rat_add(r1: rational, r2: rational) -> rational:
    d = lcm(r1.d, r2.d)
    n = ((d // r1.d) * r1.n) + ((d // r2.d) * r2.n)
    return rational(n, d)

def rat_mul(r1: rational, r2: rational) -> rational:
    n = r1.n * r2.n
    d = r1.d * r2.d
    return rational(n, d)

def rat_div(r1: rational, r2: rational) -> rational:
    return rational(r1.n, r1.d * r2.n) \
        if r2.d == 1 else rat_mul(r1, rational(r2.d, r2.n))

def __sqrt2_factor(depth) -> rational: 
    if depth == 0:
        return rational(0, 1)
    return rat_div(
        rational(1, 1),
        rat_add(
            rational(2, 1),
            __sqrt2_factor(depth - 1)
        )
    )

def sqrt2(precision_level) -> rational:
    return rat_add(rational(1, 1), __sqrt2_factor(precision_level))

def n_digits(n) -> int:
    return len(list(map(int, str(n))))

count = 0
for i in range(1, 1001):
    r = sqrt2(i)
    if n_digits(r.n) > n_digits(r.d):
        count += 1
print(f"count = {count}")
