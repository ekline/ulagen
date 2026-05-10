# SPDX-License-Identifier: MIT
# Copyright (c) 2020 Erik Kline

CPPFLAGS += -I.
CFLAGS += -std=c11 -Wall -Wextra -Wpedantic -Werror -MMD -MP

.PHONY: default
default: check ulas
	@echo
	@echo "Try 'make ula' or 'make ulas', or execute the ulagen binary"

ulagen: ulagen.o main.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: ula
ula: ulagen
	@./ulagen

COUNT ?= 16
.PHONY: ulas
ulas: ulagen
	@for i in $$(seq 1 $(COUNT)); do ./ulagen; done | sort

ulagen_test: ulagen.o test.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: check checks test tests
check checks test tests: ulagen_test
	@./ulagen_test

.PHONY: clean
clean:
	rm -f *.o *.d ulagen ulagen_test

-include $(wildcard *.d)
