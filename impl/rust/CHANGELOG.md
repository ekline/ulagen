# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.0] - TBD

### Added
- Library API exposing `Ipv6Prefix`, `generate_ula_prefix`, and
  `generate_ula_prefix_with` (RNG-injectable).
- `FromStr` and `Display` impls for `Ipv6Prefix`, plus a `ParsePrefixError`.
- Public constants `ULA_PREFIX_LEN` and `ULA_FIRST_OCTET`.
- `ulagen` CLI with `--count`, `--help`, and `--version` flags.
- Crate-level documentation, doctests, and unit tests.

### Changed
- Project restructured into a library + binary layout (`src/lib.rs` +
  `src/bin/ulagen.rs`).
- `Ipv6Prefix` now derives `Debug`, `Clone`, `Copy`, `PartialEq`, `Eq`, `Hash`.
- Bumped `rand` dependency to `0.10`. The RNG-injectable function now uses
  the `rand::Rng` trait bound (the methods previously on `rand::RngCore` are
  required methods on `Rng` in `rand` 0.9+).
- Crate now uses Rust **edition 2024**; MSRV raised to **1.85**.

## [0.1.0] - 2024-08-31

### Added
- Initial release: `ulagen` binary that prints a single random ULA `/48`.
