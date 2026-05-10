// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Erik Kline

#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

#include "ulagen.h"

int main(int, char**, char**) {
    const struct in6_addr ula{ulagen::make_random_ula_prefix()};

    char ula_str[INET6_ADDRSTRLEN+1]{};
    if (inet_ntop(AF_INET6, &ula, ula_str, sizeof(ula_str)) != ula_str) {
        return EXIT_FAILURE;
    }

    std::cout << ula_str <<  "/48\n";

    return EXIT_SUCCESS;
}
