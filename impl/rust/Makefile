###
#
# MIT License
#
# Copyright (c) 2024 Erik Kline
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
###

CARGO ?= cargo

.PHONY: default
default: build ulas
	@echo
	@echo "Try 'make ula' or 'make ulas COUNT=N', or run target/release/ulagen"

.PHONY: build
build:
	@$(CARGO) build --release

# Force rebuild before running.
.PHONY: ula
ula: build
	@./target/release/ulagen

COUNT ?= 16
.PHONY: ulas
ulas: build
	@./target/release/ulagen -n $(COUNT) | sort

.PHONY: check checks test tests
check checks test tests:
	@$(CARGO) test

.PHONY: fmt
fmt:
	@$(CARGO) fmt --all

.PHONY: fmt-check
fmt-check:
	@$(CARGO) fmt --all -- --check

.PHONY: clippy
clippy:
	@$(CARGO) clippy --all-targets -- -D warnings

.PHONY: doc
doc:
	@$(CARGO) doc --no-deps

.PHONY: package
package:
	@$(CARGO) package --list

.PHONY: publish-dry-run
publish-dry-run:
	@$(CARGO) publish --dry-run

.PHONY: clean
clean:
	@$(CARGO) clean
