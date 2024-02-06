#include "find_primes.h"
#include "primality.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>


/*
 * Returns true if all prime in primes is s.t. n % prime != 0, e.g. n is not divisible by prime.
 * */
bool trial_division(uint64_t n, const std::vector<uint64_t> &primes) {
    return std::ranges::all_of(primes.cbegin(), primes.cend(), [n](uint64_t prime) {
        return n % prime != 0;
    });
}

std::vector<uint64_t> sieve_of_eratosthenes(uint64_t n) {
    std::vector<uint64_t> result;
    std::vector<bool> A(n, true);
    uint64_t i_bound = std::floor(std::sqrt(n));
    for (uint64_t i = 2; i < i_bound; i++) {
        if (A[i]) {
            for (uint64_t j = mod_pow(i, 2, MAX_SIZE); j <= n; j += i) {
                A[j] = false;
            }
        }
    }
    for (uint64_t i = 2; i < n; i++) {
        if (A[i]) result.push_back(i);
    }
    return result;
}

/*
 * Finds ALL primes in Sn
 * */
std::vector<uint64_t> primes_in_Sn(uint64_t n) {
    size_t index;
    std::vector<uint64_t> result;
    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::vector<uint64_t> Sn;

    /*
     * Using the mod_pow function is in most cases not needed, but nice if n is very large
     * This will impact performance a bit and should have been optimized
     * But since my code can't handle integers bigger than 2^64-1 I feel like this is an ok-ish way to keep it in those bounds.
     * */
    for (uint64_t i = mod_pow(2ULL, n, MAX_SIZE); i <= (mod_pow(2ULL, n + 1, MAX_SIZE) - 1) % MAX_SIZE; i++) {
        Sn.push_back(i);
    }

    size_t size = Sn.size();

    for (size_t j = 0; j < size; j++) {
        std::uniform_int_distribution<uint64_t> distr(0, size);
        index = distr(gen);

        uint64_t selected = Sn[index];
        Sn[index] = Sn.back();
        Sn.pop_back();
        size = Sn.size();

        if (miller_rabin(selected)) result.push_back(selected);
    }
    return result;
}

std::vector<uint64_t> primes_in_Sn_with_preselected_primes(uint64_t n) {
    size_t index;
    std::vector<uint64_t> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
                                 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
                                 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
                                 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
                                 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
                                 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
                                 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
                                 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683,
                                 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
                                 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
                                 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::vector<uint64_t> result;

    std::vector<uint64_t> Sn;
    for (uint64_t i = mod_pow(2ULL, n, MAX_SIZE); i <= mod_pow(2ULL, n + 1, MAX_SIZE) - 1 % MAX_SIZE; i++) {
        if (trial_division(i, primes)) {
            Sn.push_back(i);
        }
    }

    size_t size = Sn.size();

    for (size_t j = 0; j < size; j++) {
        std::uniform_int_distribution<uint64_t> distr(0, size);
        index = distr(gen);

        uint64_t selected = Sn[index];
        Sn[index] = Sn.back();
        Sn.pop_back();
        size = Sn.size();

        if (miller_rabin(selected)) result.push_back(selected);
    }
    return result;
}

std::vector<uint64_t> primes_in_Sn_with_sieve(uint64_t n, uint64_t d) {
    size_t index;
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::vector<uint64_t> result;

    uint64_t min = mod_pow(2ULL, n, MAX_SIZE);
    uint64_t max = mod_pow(2ULL, n + 1, MAX_SIZE);
    d = d > 1 ? d : static_cast<uint64_t>(std::floor(std::sqrt((min + max) / 2)));
    std::vector<uint64_t> primes = sieve_of_eratosthenes(d);

    std::vector<uint64_t> Sn;
    for (uint64_t i = min; i < max; i++) {
        if (trial_division(i, primes)) {
            Sn.push_back(i);
        }
    }

    size_t size = Sn.size();

    for (size_t j = 0; j < size; j++) {
        std::uniform_int_distribution<uint64_t> distr(0, size);
        index = distr(gen);

        uint64_t selected = Sn[index];
        Sn[index] = Sn.back();
        Sn.pop_back();
        size = Sn.size();

        if (miller_rabin(selected)) result.push_back(selected);
    }
    return result;
}


int main() {
    std::vector<uint64_t> N = {3, 10, 15, 21};
    std::vector<std::tuple<std::vector<uint64_t>, std::chrono::microseconds, uint64_t>> results_1, results_2, results_3;
    std::vector<std::tuple<std::vector<uint64_t>, std::chrono::microseconds, std::string>> results_4;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::microseconds duration;
    std::vector<uint64_t> tmp;

    for (uint64_t n: N) {
        start = std::chrono::high_resolution_clock::now();
        tmp = primes_in_Sn(n);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        results_1.emplace_back(tmp, duration, n);

        start = std::chrono::high_resolution_clock::now();
        tmp = primes_in_Sn_with_preselected_primes(n);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        results_2.emplace_back(tmp, duration, n);

        start = std::chrono::high_resolution_clock::now();
        tmp = primes_in_Sn_with_sieve(n);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        results_3.emplace_back(tmp, duration, n);
    }

    uint64_t n = 15;
    uint64_t max_sieve = (mod_pow(2, n, MAX_SIZE) + mod_pow(2, n + 1, MAX_SIZE)) / 2;

    size_t ctr = 1;
    for (uint64_t d = 2; d <= max_sieve; d *= 2) {
        start = std::chrono::high_resolution_clock::now();
        tmp = primes_in_Sn_with_sieve(n, d);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::ostringstream ctr_stream;
        ctr_stream << "Time (diff d) (sieve [2^" << ctr << "]) [n=" << n << "]: ";
        results_4.emplace_back(tmp, duration, ctr_stream.str());
        ctr++;
    }

    // Printing the results
    for (const auto &result: results_1) {
        const auto &[primes, time, nn] = result;
        std::ostringstream stream;
        stream << "Time (naive) [n=" << nn << "]: ";
        std::cout << stream.str() << time.count() << " μs" << std::endl;
    }
    for (const auto &result: results_2) {
        const auto &[primes, time, nn] = result;
        std::ostringstream stream;
        stream << "Time (preselected primes) [n=" << nn << "]: ";
        std::cout << stream.str() << time.count() << " μs" << std::endl;
    }
    for (const auto &result: results_3) {
        const auto &[primes, time, nn] = result;
        std::ostringstream stream;
        stream << "Time (sieve [floor(sqrt((2^n + 2^(n+1))/2))]) [n=" << nn << "]: ";
        std::cout << stream.str() << time.count() << " μs" << std::endl;
    }
    for (const auto &result: results_4) {
        const auto &[primes, time, ctr_stream] = result;
        std::cout << ctr_stream << time.count() << " μs" << std::endl;
    }
    return 0;
}