# ulagen
ULA generator C code

A very small C program to generate random ULA prefixes. This program reads from `/dev/urandom` to generate "ULA-D /48s" in compliance with the spirit of the randomness requirements in [4193#3.2.1](https://www.rfc-editor.org/rfc/rfc4193.html#section-3.2.1).

# About ULAs
Unique Local IPv6 Unicast Addresses (ULAs) are defined in [RFC 4193](https://www.rfc-editor.org/rfc/rfc4193.html).

This address space is sometimes described as "[RFC 1918](https://www.rfc-editor.org/rfc/rfc1918.html) space for IPv6", but this **false**! IPv6 is **not** just 128-bit IPv4, and ULAs are **not** 10.0.0.0/8 for IPv6.

One of the most [important differences](https://www.rfc-editor.org/rfc/rfc4193.html#section-6.1) is that ULAs are designed to be allocated such they have a very low probability of colliding with any other network's ULAs, should there ever be a need to interconnect or merge networks (think: establishing a VPN with a partner or integrating a company acquisition).

As long as ULA /48s are generated randomly the future cost of renumbering -- or worse, not renumbering and having to introduce NAT into one's IPv6 network -- can either be greatly minimized or avoided entirely.

This simple utility was designed to make generating these random ULAs quick and easy.

# Scope
Although ULAs are classified in the same addressing scope as Global Unicast Addresses (GUAs), they are not expected to be globally routable (no expectation of global reachability).  The documentation on this can be confusing, and [this draft](https://datatracker.ietf.org/doc/html/draft-carpenter-6man-whats-global-00) summarizes some of the issues.

# Build
Hopefully `make` just works.  Hopefully `make clean` does too.

# Run
If it builds, the output is a `ulagen` binary that ignores all arguments, reads from `/dev/urandom`, and emits on stdout a ULA /48 prefix from the `fd00::/8` block.

One way to generate a collection of prefixes it to run this in a loop, a la:

```
for i in $(seq 1 100); do ./ulagen; done | sort
```

# Tested
This has been tested on:
1) RedHat Linux Fedora 32, with clang
1) macOS Catalina (10.15.6) and Big Sur (11.0.1), with clang


# Alternatives
One fun alternative is to [get 5 random bytes from the Internet](https://random.org/cgi-bin/randbyte?nbytes=5&format=h), prefix it with `fd`, fix up the output with `:`s in the appropriate locations for an [IPv6 string literal](https://www.rfc-editor.org/rfc/rfc5952.html), and suffix it with `::/48`.

A fun bash shell command is:

```
curl -s -L 'https://random.org/cgi-bin/randbyte?nbytes=5&format=h' | \
echo $(read; set $REPLY; echo "fd$1:$2$3:$4$5::/48")
```

or:

```
dd if=/dev/urandom  bs=1 count=5 2>/dev/null | \
od -t x1 | \
sed -e 's/^[^[:space:]]*[[:space:]]//' -e '1q' | \
echo $(read; set $REPLY; echo "fd$1:$2$3:$4$5::/48")
```
