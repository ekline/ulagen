/*

MIT License

Copyright (c) 2021 Erik Kline

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

#include <functional>
#include <optional>
#include <random>

namespace ulagen {

/**
 * Generates a ULA /48 prefix in fd00::/8 using the injected get_random_byte
 * callable to fill in the requisite 40 bits with random values.
 *
 * Returns a struct in6_addr on success, std::nullopt otherwise.
 */
inline std::optional<struct in6_addr> make_ula_prefix(
        std::function<std::optional<uint8_t>(void)> get_random_byte) {
    struct in6_addr ip6{};
    ip6.s6_addr[0] = 0xfd;

    for (int i = 1; i <= 5; i++) {
        auto byte_or{get_random_byte()};
        if (not byte_or.has_value()) {
            return std::nullopt;
        }
        ip6.s6_addr[i] = *(byte_or);
    }

    return ip6;
}


/**
 * Generates a ULA /48 prefix in fd00::/8 using an injected function
 * that fills in the requisite 40 bits with values from std::random_device.
 *
 * Returns a struct in6_addr.
 */
struct in6_addr make_random_ula_prefix() {
    return *(make_ula_prefix([]() -> std::optional<uint8_t> {
        static std::random_device rd{};
        static std::mt19937 engine{rd()};
        static std::uniform_int_distribution<short> dist(0, 255);

        return static_cast<uint8_t>(dist(engine) & 0xff);
    }));
}

}  // namespace ulagen

#endif   /* ULAGEN_H__ */
