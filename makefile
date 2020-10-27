PREFIX ?= /usr/local
CC ?= gcc

fuzzycmp: fuzzycmp-src/fuzzycmp.c
	$(CC) -pedantic -Wall -O2 fuzzycmp-src/fuzzycmp.c -o fuzzycmp

clean:
	rm fuzzycmp

install: fuzzycmp
	mkdir $(PREFIX)/bin/meem-search
	cp fuzzycmp $(PREFIX)/bin/meem-search
	cp meem $(PREFIX)/bin/meem-search
	ln -s $(PREFIX)/bin/meem-search/meem $(PREFIX)/bin/meem

uninstall:
	rm -r $(PREFIX)/bin/meem-search $(PREFIX)/bin/meem

.PHONY: clean uninstall
