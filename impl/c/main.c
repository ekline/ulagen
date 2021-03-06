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

int main(int argc, char** argv, char** envp) {
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(envp);

    struct in6_addr ula;
    if (make_random_ula_prefix(&ula) != 0) {
        return EXIT_FAILURE;
    }

    char ula_str[INET6_ADDRSTRLEN+1];
    memset(ula_str, 0, sizeof(ula_str));
    if (inet_ntop(AF_INET6, &ula, ula_str, sizeof(ula_str)) != ula_str) {
        return EXIT_FAILURE;
    }

    printf("%s/48\n", ula_str);

    return EXIT_SUCCESS;
}
