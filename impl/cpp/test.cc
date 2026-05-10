// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Erik Kline

#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <optional>
#include <vector>

#include "ulagen.h"

int test_injectable_random_works() {
    // clang-format off
    const char* const expectations[] = {
        "fd00:102:304::",
        "fd05:607:809::",
        "fd0a:b0c:d0e::",
        "fd0f:1011:1213::",
        "fd14:1516:1718::",
    };
    // clang-format on

    struct in6_addr in6{};
    char repr[INET6_ADDRSTRLEN + 1]{};
    const int runs =
            static_cast<int>(sizeof(expectations) / sizeof(expectations[0]));
    for (int i = 0; i < runs; i++) {
        in6 = ulagen::make_ula_prefix([]() -> std::optional<uint8_t> {
                  static uint8_t b{0};
                  return b++;
              }).value();

        memset(repr, 0, sizeof(repr));
        if (inet_ntop(AF_INET6, &in6, repr, sizeof(repr)) != repr) {
            return 10 * i + 1;
        }

        if (strncmp(repr, expectations[i], sizeof(repr)) != 0) {
            return 10 * i + 2;
        }
    }

    return 0;
}

int test_failing_injected_random_yields_error() {
    return ulagen::make_ula_prefix(
                   []() -> std::optional<uint8_t> { return std::nullopt; })
            .has_value();
}

int test_repeated_calls_with_std_random_device() {
    constexpr int kAddrBytes = 16;

    std::vector<struct in6_addr> ulas(9);

    for (size_t i = 0; i < ulas.size(); i++) {
        ulas[i] = ulagen::make_random_ula_prefix();

        if (ulas[i].s6_addr[0] != 0xfd) {
            return static_cast<int>(1000 * i + 0xfd);
        }

        for (int j = 6; j < kAddrBytes; j++) {
            if (ulas[i].s6_addr[j] != 0) {
                return static_cast<int>(1000 * i + j);
            }
        }
    }

    for (size_t i = 0; i < ulas.size(); i++) {
        for (size_t j = i + 1; j < ulas.size(); j++) {
            if (memcmp(ulas[i].s6_addr, ulas[j].s6_addr, kAddrBytes) == 0) {
                return static_cast<int>(10 * i + j);
            }
        }
    }

    return 0;
}

struct {
    const char* description;
    int (*test_function)();
} tests[] = {
        {"Injectable random functions work as expected",
         &test_injectable_random_works},

        {"Injecting random function that fails yields error",
         &test_failing_injected_random_yields_error},

        {"Repeated calls with std::random_device look sensible",
         &test_repeated_calls_with_std_random_device},
};

int main(int, char**, char**) {
    const int num_tests = static_cast<int>(sizeof(tests) / sizeof(tests[0]));

    printf("\nRunning %d tests:\n\n", num_tests);

    int num_failures = 0;
    for (int i = 0; i < num_tests; i++) {
        printf("[%d] %s ...", i, tests[i].description);
        const int rval = tests[i].test_function();
        if (rval == 0) {
            printf(" OK\n");
        } else {
            printf(" FAIL (%d)\n", rval);
            num_failures++;
        }
    }

    if (num_failures == 0) {
        printf("\nPASS\n");
    } else {
        printf("\nFAIL: %d/%d tests failed\n", num_failures, num_tests);
    }

    return num_failures;
}
