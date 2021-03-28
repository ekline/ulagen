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
