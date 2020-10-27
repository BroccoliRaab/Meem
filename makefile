PREFIX ?= /usr/local
CC ?= gcc
CFLAGS ?= -pedantic -Wall -O2
DESTDIR ?= meem-search

fuzzycmp: fuzzycmp-src/fuzzycmp.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm fuzzycmp

install: fuzzycmp
	mkdir $(PREFIX)/bin/$(DESTDIR)
	cp fuzzycmp $(PREFIX)/bin/$(DESTDIR)
	cp meem $(PREFIX)/bin/$(DESTDIR)
	ln -s $(PREFIX)/bin/$(DESTDIR)/meem $(PREFIX)/bin/meem

uninstall:
	rm -r $(PREFIX)/bin/$(DESTDIR) $(PREFIX)/bin/meem

.PHONY: clean install uninstall
