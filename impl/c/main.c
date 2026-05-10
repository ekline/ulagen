// SPDX-License-Identifier: MIT
// Copyright (c) 2020 Erik Kline

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ulagen.h"

#define UNUSED(x) ((void)(x))

int main(int argc, char** argv, char** envp) {
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);

    struct in6_addr ula;
    if (make_random_ula_prefix(&ula) != 0) {
        return EXIT_FAILURE;
    }

    char ula_str[INET6_ADDRSTRLEN + 1];
    memset(ula_str, 0, sizeof(ula_str));
    if (inet_ntop(AF_INET6, &ula, ula_str, sizeof(ula_str)) != ula_str) {
        return EXIT_FAILURE;
    }

    printf("%s/48\n", ula_str);

    return EXIT_SUCCESS;
}
