//
// Created by caroline on 05.02.24.
//

#ifndef PROJECT_2_PRIMALITY_H

#define PROJECT_2_PRIMALITY_H

#include <cstdint>

uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus);
bool fermat_test(uint64_t p, int iterations = 10);
bool miller_rabin(uint64_t n, int k = 10);


#endif //PROJECT_2_PRIMALITY_H
