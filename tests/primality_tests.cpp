#include "primality.h"
#include "catch2/catch_all.hpp"

TEST_CASE("Fermat Primality Test", "[fermat]") {
    SECTION("Testing known primes") {
        REQUIRE(fermat_test(2));
        REQUIRE(fermat_test(3));
        REQUIRE(fermat_test(283));
        REQUIRE(fermat_test(617));
        REQUIRE(fermat_test(1031));
        REQUIRE(fermat_test(1367));
        REQUIRE(fermat_test(1697));
        REQUIRE(fermat_test(2063));
        REQUIRE(fermat_test(2383));
        REQUIRE(fermat_test(2711));
        REQUIRE(fermat_test(3061));
        REQUIRE(fermat_test(3373));
        REQUIRE(fermat_test(3709));
        REQUIRE(fermat_test(4027));
        REQUIRE(fermat_test(4391));
        REQUIRE(fermat_test(4729));
        REQUIRE(fermat_test(5077));
        REQUIRE(fermat_test(5399));
        REQUIRE(fermat_test(5741));
        REQUIRE(fermat_test(6089));
        REQUIRE(fermat_test(6449));
        REQUIRE(fermat_test(6793));
        REQUIRE(fermat_test(7103));
        REQUIRE(fermat_test(7457));
        REQUIRE(fermat_test(7793));
        REQUIRE(fermat_test(8117));
        REQUIRE(fermat_test(8461));
        REQUIRE(fermat_test(8803));
        REQUIRE(fermat_test(9133));
        REQUIRE(fermat_test(9479));
        REQUIRE(fermat_test(9829));
    }
    SECTION("Testing known large primes") {
        REQUIRE(fermat_test(2147483659)); // 32-bit prime
        REQUIRE(fermat_test(2305843009213693967)); // 62-bit prime
        REQUIRE(fermat_test(9223372036854775837ULL)); // 64-bit prime, code SHOULD be able to handle this.
    }
}

TEST_CASE("Miller-Rabin Primality Test", "[miller-rabin]") {
    SECTION("Testing known primes") {
        REQUIRE(miller_rabin(2));
        REQUIRE(miller_rabin(3));
        REQUIRE(miller_rabin(283));
        REQUIRE(miller_rabin(617));
        REQUIRE(miller_rabin(1031));
        REQUIRE(miller_rabin(1367));
        REQUIRE(miller_rabin(1697));
        REQUIRE(miller_rabin(2063));
        REQUIRE(miller_rabin(2383));
        REQUIRE(miller_rabin(2711));
        REQUIRE(miller_rabin(3061));
        REQUIRE(miller_rabin(3373));
        REQUIRE(miller_rabin(3709));
        REQUIRE(miller_rabin(4027));
        REQUIRE(miller_rabin(4391));
        REQUIRE(miller_rabin(4729));
        REQUIRE(miller_rabin(5077));
        REQUIRE(miller_rabin(5399));
        REQUIRE(miller_rabin(5741));
        REQUIRE(miller_rabin(6089));
        REQUIRE(miller_rabin(6449));
        REQUIRE(miller_rabin(6793));
        REQUIRE(miller_rabin(7103));
        REQUIRE(miller_rabin(7457));
        REQUIRE(miller_rabin(7793));
        REQUIRE(miller_rabin(8117));
        REQUIRE(miller_rabin(8461));
        REQUIRE(miller_rabin(8803));
        REQUIRE(miller_rabin(9133));
        REQUIRE(miller_rabin(9479));
        REQUIRE(miller_rabin(9829));
    }
    SECTION("Testing known large primes") {
        REQUIRE(miller_rabin(2147483659)); // 32-bit prime
        REQUIRE(miller_rabin(2305843009213693967)); // 62-bit prime
        REQUIRE(miller_rabin(9223372036854775837ULL)); // 64-bit prime, code SHOULD be able to handle this.
    }

    SECTION("Testing known non-primes") {
        REQUIRE(!miller_rabin(527));
        REQUIRE(!miller_rabin(920));  // Even
        REQUIRE(!miller_rabin(1075));
        REQUIRE(!miller_rabin(1149));
        REQUIRE(!miller_rabin(1339));
        REQUIRE(!miller_rabin(1841));
        REQUIRE(!miller_rabin(2619));
        REQUIRE(!miller_rabin(2800));  // Even
        REQUIRE(!miller_rabin(2985));
        REQUIRE(!miller_rabin(2995));
        REQUIRE(!miller_rabin(3125));
        REQUIRE(!miller_rabin(3189));
        REQUIRE(!miller_rabin(3665));
        REQUIRE(!miller_rabin(3835));
        REQUIRE(!miller_rabin(3925));
        REQUIRE(!miller_rabin(4347));
        REQUIRE(!miller_rabin(4377));
        REQUIRE(!miller_rabin(5603));
        REQUIRE(!miller_rabin(5929));
        REQUIRE(!miller_rabin(6283));
        REQUIRE(!miller_rabin(6825));
        REQUIRE(!miller_rabin(7897));
        REQUIRE(!miller_rabin(8463));
        REQUIRE(!miller_rabin(8763));
        REQUIRE(!miller_rabin(8947));
    }

    SECTION("Testing known large non-primes") {
        REQUIRE(!miller_rabin(2712937799));  // 32-bit
        REQUIRE(!miller_rabin(3854201392617981135));  // 62-bit
        REQUIRE(!miller_rabin(13904217910334545653ULL));  // 64-bit
    }
}