// SPDX-License-Identifier: MIT
// Copyright (c) 2020 Erik Kline

#include "ulagen.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int make_ula_prefix(size_t (*rand_bytes)(uint8_t*, int num_bytes),
                    struct in6_addr* in6) {
    struct in6_addr ip6;

    if ((rand_bytes == NULL) || (in6 == NULL)) {
        return -1;
    }

    memset(ip6.s6_addr, 0, sizeof(ip6.s6_addr));
    ip6.s6_addr[0] = 0xfd;

    if (rand_bytes(&(ip6.s6_addr[1]), 5) == 5) {
        memcpy(in6->s6_addr, ip6.s6_addr, sizeof(ip6.s6_addr));
        return 0;
    }

    return -1;
}

static size_t dev_urandom_bytes(uint8_t* dst, int num_bytes) {
    FILE* fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        return 0;
    }

    const size_t read = fread(dst, 1, num_bytes, fp);
    fclose(fp);
    return read;
}

int make_random_ula_prefix(struct in6_addr* in6) {
    return make_ula_prefix(&dev_urandom_bytes, in6);
}
