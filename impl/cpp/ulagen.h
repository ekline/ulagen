// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Erik Kline

#ifndef ULAGEN_H_
#define ULAGEN_H_

#include <netinet/in.h>

#include <cstdint>
#include <cstdlib>
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
        const std::function<std::optional<uint8_t>(void)>& get_random_byte) {
    struct in6_addr ip6{};
    ip6.s6_addr[0] = 0xfd;

    for (int i = 1; i <= 5; i++) {
        auto byte_or{get_random_byte()};
        if (not byte_or.has_value()) {
            return std::nullopt;
        }
        ip6.s6_addr[i] = *byte_or;
    }

    return ip6;
}

/**
 * Generates a ULA /48 prefix in fd00::/8, drawing the requisite 40 bits
 * from std::random_device (the platform's CSPRNG on conforming
 * implementations).
 *
 * Note: this deliberately samples std::random_device directly rather than
 * seeding a deterministic PRNG (e.g. std::mt19937) from it. Seeding mt19937
 * from a single random_device draw provides only 32 bits of state entropy,
 * which is below the 40-bit ULA Global ID space and would meaningfully
 * raise the cross-network collision probability that RFC 4193 §3.2.1 is
 * trying to minimize.
 *
 * Returns a struct in6_addr.
 */
inline struct in6_addr make_random_ula_prefix() noexcept {
    auto opt = make_ula_prefix([]() -> std::optional<uint8_t> {
        static thread_local std::random_device rd{};
        static thread_local std::uniform_int_distribution<unsigned int> dist(
                0, 255);

        return static_cast<uint8_t>(dist(rd));
    });

    // The callback above always returns a value, so make_ula_prefix
    // never returns std::nullopt here. Abort defensively if that ever
    // changes; this keeps make_random_ula_prefix() noexcept-clean.
    if (!opt.has_value()) {
        std::abort();
    }
    return *opt;
}

}  // namespace ulagen

#endif /* ULAGEN_H_ */
