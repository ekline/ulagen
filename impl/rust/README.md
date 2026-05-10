# ulagen

[![crates.io](https://img.shields.io/crates/v/ulagen.svg)](https://crates.io/crates/ulagen)
[![docs.rs](https://docs.rs/ulagen/badge.svg)](https://docs.rs/ulagen)

Generate random IPv6 Unique Local Address (ULA) `/48` prefixes per
[RFC 4193](https://www.rfc-editor.org/rfc/rfc4193.html).

This crate provides:

* A small, dependency-light **library** for producing random ULA prefixes from
  any `rand::Rng`, and an `Ipv6Prefix` type with `Display` / `FromStr`.
* A **command-line tool** (`ulagen`) that prints one or more prefixes to
  stdout.

## Why ULAs?

Unique Local IPv6 Unicast Addresses are sometimes (incorrectly) described as
"[RFC 1918](https://www.rfc-editor.org/rfc/rfc1918.html) for IPv6". They are
not. A key design goal of ULAs is that two independently-generated `/48`s
have a vanishingly small probability of colliding, so networks can be merged
or interconnected (VPN, acquisition, etc.) without renumbering or NAT.

To preserve that property, ULAs **must** be generated with sufficient
randomness — not picked by hand, and not allocated sequentially. This crate
uses a CSPRNG seeded from the operating system (`rand::rng`) by
default.

## Library usage

```rust
use ulagen::{generate_ula_prefix, generate_ula_prefix_with};

// Use the default thread-local CSPRNG:
let prefix = generate_ula_prefix();
println!("{prefix}"); // e.g. "fdab:cd12:3456::/48"

// Or supply your own RNG (useful for tests / reproducibility):
let mut rng = rand::rng();
let prefix = generate_ula_prefix_with(&mut rng);
assert_eq!(prefix.prefix_len(), 48);
assert_eq!(prefix.addr().octets()[0], 0xfd);
```

## CLI usage

```text
$ ulagen
fd2a:9c41:7b6e::/48

$ ulagen -n 4 | sort
fd1c:bd44:0e51::/48
fd66:ef2a:9988::/48
fd9b:0203:7c4d::/48
fde0:1122:3344::/48
```

## Install

Library:

```toml
[dependencies]
ulagen = "0.2"
```

CLI:

```sh
cargo install ulagen
```

## RFC 4193 compliance notes

* The generated prefix is in `fd00::/8` (the locally-assigned half of
  `fc00::/7`). `fc00::/8` is reserved by RFC 4193 §3.1 for an as-yet-undefined
  centrally assigned scheme.
* The 40-bit Global ID is filled from the supplied RNG. RFC 4193 §3.2.1
  describes a SHA-1-based pseudo-random algorithm; this crate instead uses a
  CSPRNG, which satisfies the *spirit* of the requirement (a uniformly
  distributed, hard-to-predict 40-bit value). If strict §3.2.1 conformance
  matters for your use case, you should compute the Global ID separately.
* The bits below `/48` (subnet ID and interface ID) are zeroed.

## License

MIT — see the [LICENSE](https://github.com/ekline/ulagen/blob/main/impl/rust/LICENSE) file.
