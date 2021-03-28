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

#include "ulagen.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int make_ula_prefix(size_t (*rand_bytes)(uint8_t*, int num_bytes),
                    struct in6_addr *in6) {
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

int make_random_ula_prefix(struct in6_addr *in6) {
    return make_ula_prefix(&dev_urandom_bytes, in6);
}
