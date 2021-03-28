###
#
# MIT License
#
# Copyright (c) 2021 Erik Kline
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
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
###

CXXFLAGS := --std=c++17

.PHONY: default
default: check ulas
	@echo
	@echo "Try 'make ula' or 'make ulas', or execute the ulagen binary"

ulagen: main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Wall -I. -o $@ $^

.PHONY: ula
ula: ulagen
	@./ulagen

COUNT ?= 16
.PHONY: ulas
ulas: ulagen
	@for i in $$(seq 1 $(COUNT)); do ./ulagen; done | sort

ulagen_test: test.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Wall -I. -o $@ $^

.PHONY: check checks test tests
check checks test tests: ulagen_test
	@./ulagen_test

.PHONY: clean
clean:
	rm -f *.o ulagen ulagen_test
