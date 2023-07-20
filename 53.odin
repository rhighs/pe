package main
 
import "core:fmt"
import "core:math"

combinations :: proc (n: u64, r: u64) -> u64 {
    if r == 0 {
        return 1
    }
    if r > n/2 {
        return combinations(n, n-r)
    }
    return n * combinations(n-1, r-1) / r
}
 
main :: proc() {
    count := 0
    for n in 23..=u64(100) {
        for r in 1..=n {
            if combinations(n, r) > 1_000_000 {
                count += 1
            }
        }
    }

    fmt.println(count)
}
