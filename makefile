PREFIX ?= /usr/local
CC ?= gcc
CFLAGS ?= -pedantic -Wall -O2

fuzzycmp: fuzzycmp-src/fuzzycmp.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm fuzzycmp

install: fuzzycmp
	cp fuzzycmp $(PREFIX)/bin
	cp meem $(PREFIX)/bin
	chmod +x $(PREFIX)/bin/meem

uninstall:
	rm $(PREFIX)/bin/fuzzycmp $(PREFIX)/bin/meem
	
.PHONY: clean install uninstall
