// SPDX-License-Identifier: MIT
//
// Copyright (c) 2024 Erik Kline

//! CLI front-end for the `ulagen` library.
//!
//! Usage:
//! ```text
//! ulagen           # print one /48
//! ulagen -n 16     # print 16 /48s, one per line
//! ulagen --help
//! ```

use std::process::ExitCode;

use ulagen::generate_ula_prefix;

const USAGE: &str = "\
Usage: ulagen [-n COUNT] [-h|--help] [-V|--version]

Print one or more random IPv6 ULA /48 prefixes (RFC 4193).

Options:
  -n, --count N      Print N prefixes (default: 1)
  -h, --help         Show this help text
  -V, --version      Show version information
";

fn main() -> ExitCode {
    let mut args = std::env::args().skip(1);
    let mut count: u32 = 1;

    while let Some(arg) = args.next() {
        match arg.as_str() {
            "-h" | "--help" => {
                print!("{USAGE}");
                return ExitCode::SUCCESS;
            }
            "-V" | "--version" => {
                println!("{} {}", env!("CARGO_PKG_NAME"), env!("CARGO_PKG_VERSION"));
                return ExitCode::SUCCESS;
            }
            "-n" | "--count" => {
                let Some(val) = args.next() else {
                    eprintln!("error: {arg} requires a value");
                    eprint!("{USAGE}");
                    return ExitCode::FAILURE;
                };
                match val.parse::<u32>() {
                    Ok(n) => count = n,
                    Err(e) => {
                        eprintln!("error: invalid count {val:?}: {e}");
                        return ExitCode::FAILURE;
                    }
                }
            }
            other => {
                eprintln!("error: unrecognised argument: {other}");
                eprint!("{USAGE}");
                return ExitCode::FAILURE;
            }
        }
    }

    for _ in 0..count {
        println!("{}", generate_ula_prefix());
    }
    ExitCode::SUCCESS
}
