//
// Created by caroline on 05.02.24.
//

#ifndef PROJECT_2_FIND_PRIMES_H
#define PROJECT_2_FIND_PRIMES_H

#include <cstdint>
#include <cstddef>
#include <vector>

uint64_t MAX_SIZE = 0xFFFFFFFFFFFFFFFFULL;

std::vector<uint64_t> primes_in_Sn(uint64_t n);
std::vector<uint64_t> primes_in_Sn_with_preselected_primes(uint64_t n);
std::vector<uint64_t> primes_in_Sn_with_sieve(uint64_t n, uint64_t d = 0);


#endif //PROJECT_2_FIND_PRIMES_H
