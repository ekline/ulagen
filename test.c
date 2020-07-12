/*

MIT License

Copyright (c) 2020 Erik Kline

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ulagen.h"

#define UNUSED(x) ((void) x)

static const int kAddrBytes = 16;

size_t monotonic_nonrandom(uint8_t* dst, int num_bytes) {
    static int monotonic = 0;

    if ((dst == NULL) || (num_bytes < 0)) {
        return 0;
    }

    for (int i = 0; i < num_bytes; i++) {
        dst[i] = monotonic++;
    }

    return num_bytes;
}

int test_injectable_random_works() {
    const char* const expectations[] = {
        "fd00:102:304::",
        "fd05:607:809::",
        "fd0a:b0c:d0e::",
        "fd0f:1011:1213::",
        "fd14:1516:1718::",
    };

    struct in6_addr in6;
    char repr[INET6_ADDRSTRLEN+1];
    const int runs = (int) (sizeof(expectations) / sizeof(expectations[0]));
    for (int i = 0; i < runs; i++) {
        const int rval = make_ula_prefix(&monotonic_nonrandom, &in6);
        if (rval != 0) {
            return 10*i + 1;
        }

        memset(repr, 0, sizeof(repr));
        if (inet_ntop(AF_INET6, &in6, repr, sizeof(repr)) != repr) {
            return 10*i + 2;
        }

        if (strncmp(repr, expectations[i], sizeof(repr)) != 0) {
            return 10*i + 3;
        }
    }

    return 0;
}

size_t failing_random(uint8_t* dst, int num_bytes) {
    UNUSED(dst);

    return ((num_bytes > 1) ? (num_bytes - 1) : 0);
}

int test_failing_injected_random_yields_error() {
    struct in6_addr in6;

    if (make_ula_prefix(&failing_random, &in6) != 0) {
        return 0;
    }
    return 1;
}

int test_repeated_calls_with_dev_urandom() {
    struct in6_addr ulas[9];

    const int num_ulas = (int) (sizeof(ulas) / sizeof(ulas[0]));

    for (int i = 0; i < num_ulas; i++) {
        const int rval = make_random_ula_prefix(&(ulas[i]));
        if (rval != 0) {
            return 1000*i + 1;
        }

        if (ulas[i].s6_addr[0] != 0xfd) {
            return 1000*i + 0xfd;
        }

        for (int j = 6; j < kAddrBytes; j++) {
            if (ulas[i].s6_addr[j] != 0) {
                return 1000*i + j;
            }
        }
    }

    for (int i = 0; i < num_ulas; i++) {
        for (int j = i + 1; j < num_ulas; j++) {
            if (memcmp(ulas[i].s6_addr, ulas[j].s6_addr, kAddrBytes) == 0) {
                return 10*i + j;
            }
        }
    }

    return 0;
}

struct {
    const char* description;
    int (*test_function)();
} tests[] = {
    { "Injectable random functions work as expected",
      &test_injectable_random_works },

    { "Injecting random function that fails yields error",
      &test_failing_injected_random_yields_error },

    { "Repeated calls with /dev/urandom look sensible",
      &test_repeated_calls_with_dev_urandom },
};


int main(int argc, char** argv, char** envp) {
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);

    const int num_tests = (int) (sizeof(tests) / sizeof(tests[0]));

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
