#include <iostream>
#include <random>
#include "primality.h"

// Need to handle a product before modulo that is larger than 64-bit.
// Perform modulo on intermediate steps in the multiplication
uint64_t smart_uint64_mult_mod(uint64_t a, uint64_t b, uint64_t modulus) {
    uint64_t result = 0;
    a %= modulus;
    b %= modulus;
    while (b > 0) {
        if (b&1) result = (result + a) % modulus;
        a = (2*a)%modulus;
        b >>= 1;
    }
    return result;
}

uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if ((exponent & 1) == 1) {
            result = smart_uint64_mult_mod(result, base, modulus);
        }
        exponent >>= 1;
        base = smart_uint64_mult_mod(base, base, modulus);
    }
    return result;
}

bool fermat_test(uint64_t p, int iterations) {
    if (p == 2 || p == 3) return true;
    if (p <= 1 || !(p & 1)) return false;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(2, p - 2);

    for (int i = 0; i < iterations; i++) {
        uint64_t a = distr(gen);
        if (mod_pow(a, p - 1, p) != 1) return false;
    }
    return true;
}

bool miller_rabin(uint64_t n, int k) {
    if (n == 2 || n == 3) return true;
    if (n <= 1 || !(n & 1)) return false;

    uint64_t d = n - 1;
    while ((d & 1) == 1) d >>= 2;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(2, n - 2);

    for (int i = 0; i < k; i++) {
        uint64_t a = distr(gen);
        uint64_t x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        while (d != n - 1) {
            d <<= 1;
            x = mod_pow(x, 2, n);
            if (x == 1) return false;
            if (x == n - 1) goto OUTER;
        }
        return false;
        OUTER:
        continue;
    }
    return true;
}
