#include "robin_hood.h"

#include "benchmark.h"
#include "doctest.h"
#include "sfc64.h"

TEST_CASE("bench robin_hood::hash<std::string>" * doctest::test_suite("bench")) {
    size_t h = 0;
    sfc64 rng(123);
    robin_hood::hash<std::string> hasher;

    size_t len;
    size_t iterations;
    SUBCASE("7") {
        len = 7;
        iterations = 250058138u;
    }
    SUBCASE("8") {
        len = 8;
        iterations = 310857313u;
    }
    SUBCASE("13") {
        len = 13;
        iterations = 225620314u;
    }
    SUBCASE("100") {
        len = 100;
        iterations = 68319310u;
    }
    SUBCASE("1000") {
        len = 1000;
        iterations = 6458275u;
    }

    std::string str(len, 'x');
    for (size_t i = 0; i < str.size(); ++i) {
        str[i] = rng.uniform<char>();
    }
    BENCHMARK("std::string length " + std::to_string(len), len * iterations, "B") {
        for (size_t i = 0; i < iterations; ++i) {
            // modify string to prevent optimization
            ++*reinterpret_cast<uint64_t*>(&str[0]);
            h += hasher(str);
        }
    }

    // prevent optimization
    INFO(h);
    REQUIRE(h != 0);
}
