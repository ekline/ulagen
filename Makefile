# SPDX-License-Identifier: MIT
# Copyright (c) 2020 Erik Kline

implementations := $(patsubst %/Makefile, %, $(wildcard impl/*/Makefile))

.PHONY: default ula ulas check checks test tests clean
default ula ulas check checks test tests clean:
	@for impl in $(implementations); do \
	    echo ""; \
	    echo "##"; \
	    echo "# implementation: $${impl}"; \
	    echo "##"; \
	    $(MAKE) -C $${impl} $@; \
	done
