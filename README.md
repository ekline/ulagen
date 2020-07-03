# ulagen
ULA generator C code

A very small C program to generate random ULA prefixes. This program reads from `/dev/urandom` to generate "ULA-D /48s" in compliance with the spirit of the randomness requirements in [4193#3.2.1](https://www.rfc-editor.org/rfc/rfc4193.html#section-3.2.1).

# About ULAs
Unique Local IPv6 Unicast Addresses (ULAs) are defined in [RFC 4193](https://www.rfc-editor.org/rfc/rfc4193.html).

This address space is sometimes described as "[RFC 1918](https://www.rfc-editor.org/rfc/rfc1918.html) space for IPv6", but this **false**! IPv6 is **not** just 128-bit IPv4, and ULAs are **not** 10.0.0.0/8 for IPv6.

One of the most [important differences](https://www.rfc-editor.org/rfc/rfc4193.html#section-6.1) is that ULAs are designed to be allocated such they have a very low probability of colliding with any other network's ULAs, should there ever be a need to interconnect or merge networks (think: establishing a VPN with a partner or integrating a company acquisition).

As long as ULA /48s are generated randomly the future cost of renumbering -- or worse, not renumbering and having to introduce NAT into one's IPv6 network -- can either be greatly minimized or avoided entirely.

This simple utility was designed to make generating these random ULAs quick and easy.

# Build
Hopefully `make` just works.  Hopefully `make clean` does too.

# Run
If it builds, the outputis a `ulagen` binary that ignores all arguments, reads from `/dev/urandom`, and emits on stdout a ULA /48 prefix from the `fd00::/8` block.

One way to generate a collection of prefixes it to run this in a loop, a la `for i in $(seq 1 100); do ./ulagen; done | sort`.
