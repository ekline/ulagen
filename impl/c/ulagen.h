// SPDX-License-Identifier: MIT
// Copyright (c) 2020 Erik Kline

#ifndef ULAGEN_H__
#define ULAGEN_H__

#include <netinet/in.h>

/**
 * Generates a ULA /48 prefix in fd00::/8 using the injected rand_bytes
 * method to fill in the requisite 40 bits with random values.
 *
 * Returns 0 on success, non-zero otherwise.
 */
int make_ula_prefix(size_t (*rand_bytes)(uint8_t*, int num_bytes),
                    struct in6_addr *in6);


/**
 * Generates a ULA /48 prefix in fd00::/8 using an injected function
 * that fills in the requisite 40 bits with values from /dev/urandom.
 *
 * Returns 0 on success, non-zero otherwise.
 */
int make_random_ula_prefix(struct in6_addr *in6);

#endif   /* ULAGEN_H__ */
